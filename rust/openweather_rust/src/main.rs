use std::env::args;
use std::path::Path;
use std::process::exit;
use std::time;
use std::fs;

use cache::write_cache;
use apidata::APIData;
use apidata::Geocoding;
use chrono::Duration;
use weather::Current;

pub mod http;
pub mod cli;
pub mod cache;
pub mod apidata;
pub mod weather;

fn print_i3_bar(c: &Current) -> String {
    format!("{} | {} | {}", c.name, c.weather[0].main, c.main.temp)
}

fn check_hour(c: &Current) -> bool {

    const HOUR_IN_SECONDS: u64 = 3600;
    let h: u64 = time::SystemTime::now()
        .duration_since(time::UNIX_EPOCH)
        .unwrap()
        .as_secs();

    if h - c.dt < HOUR_IN_SECONDS {
        println!("less than HOUR_IN_SECONDS");
        return false;
    } else {
        println!("greater than HOUR_IN_SECONDS");
        return true;
    }
} 

fn get_rid_of_arrays(json: serde_json::Value) -> String {

    match serde_json::to_string_pretty(&json[0]) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("ERROR main::get_rid_of_arrays > failed to convert JSON to to_string_pretty: {:#?}", e);
            exit(-1);
        }
    }
}

fn check_get_errors(response: &String) {
    let response: serde_json::Value = serde_json::from_str(&response).unwrap();
    if response.get("cod").unwrap() != 200 {
        eprintln!("main::check_get_errors > Server returned an error: {:#?}", response);
        exit(-1);
    }
}

fn get_geocoding(data: &APIData) -> Geocoding {

    let url = format!(
        "http://api.openweathermap.org/geo/1.0/direct?q={},{}&appid={}",
       data.geocoding.name, data.geocoding.country, data.appid 
    );

    let response: Geocoding = match serde_json::from_str(&http::get(&url)) {
        Ok(j) => {
            match serde_json::from_str(&get_rid_of_arrays(j)) {
                Ok(g) => g,
                Err(e) => {
                    eprintln!("ERROR main::get_geocoding > failed to serialize response to Geocoding: {:#?}", e);
                    exit(-1);
                }
            }
            
        },

        Err(e) => {
            eprintln!("ERROR main::get_geocoding > failed to serialize response to json: {:#?}", e);
            exit(-1);
        }
    }; 
    
    println!("{:#?}", response);
    return response;
}

fn get_weather(data: &APIData) -> Current {

    let url: String = format!(
        "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&units={}&appid={}",
        data.geocoding.lat, data.geocoding.lon, data.units, data.appid
    );

    
    let response: String = http::get(&url);
    check_get_errors(&response);

    let response: String = http::get(&url);
    let response: Current = match serde_json::from_str(&response) {
        Ok(w) => w,
        Err(e) => {
            eprintln!("ERROR main::get_weather > failed to serialize Weather: {:#?}", e);
            eprintln!("JSON response: {:#?}", response);
            exit(-1);
        }
    };

    return response;
}

fn cache_weather(weather: &Current) {
    let path: &Path = &Path::new("/home/dio/.config/weather/weather.json");
    
    if !path.exists() {
        match fs::File::create(path) {
            Ok(_) => println!("file created: $HOME/.config/weather/weather.json"),
            Err(e) => {
                eprintln!("main::cache_weather > failed to create weather.json: {:#?}", e);
                return;
            }
        };     
    }

    let cache: String = serde_json::to_string_pretty(&weather).unwrap();
    write_cache(path, &cache);
}

fn read_cache_weather() -> Current {
    let path: &Path = &Path::new("/home/dio/.config/weather/weather.json");

    if !path.exists() {
        eprintln!("main::read_cache_weather > weather.json does not exist.");
        exit(-1);
    }

    match serde_json::from_str(&cache::read_cache(path)) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("main::read_cache_weather > error while serializing Current: {:#?}", e);
            exit(-1);
        }
    }
}

fn cache_apidata(data: &APIData) {
    let path: &Path = &Path::new("/home/dio/.config/weather/config.json");   
    
    if !path.exists() {
        eprintln!("api cache file does not exist.");
        exit(-1);
    }

    let cache: String = serde_json::to_string_pretty(&data).unwrap();
    write_cache(path, &cache);
}

fn read_cache_apidata() -> APIData {
    let path: &Path = &Path::new("/home/dio/.config/weather/config.json");

    if !path.exists() {
        eprintln!("main::read_cache_weather > config.json does not exist.");
        exit(-1);
    }

    match serde_json::from_str(&cache::read_cache(path)) {
        Ok(c) => c,
        Err(e) => {
            eprintln!("main::read_cache_weather > error while serializing APIData: {:#?}", e);
            exit(-1);
        }
    }
}

fn main() {
    let apidata_cache: &Path = &Path::new("/home/dio/.config/weather/config.json");
    let mut data: APIData;
    
    if args().len() > 1 {
        data = cli::matches();
        data.geocoding = get_geocoding(&data);
        cache_apidata(&data);

    } else if apidata_cache.exists() { 
        data = read_cache_apidata(); 
    } else {
        eprintln!("none arguments were provided and neither cache to use.");
        exit(-1);
    }

    let weather: Current = {
        let cached_weather: Current = read_cache_weather();
        let weather: Current;

        if check_hour(&cached_weather) {
            println!("requesting weather...");
            weather = get_weather(&data);
            cache_weather(&weather);
        } else {
            println!("using cached weather...");
            weather = cached_weather;
        }

        weather
    };

    println!("{:#?}", weather);
}

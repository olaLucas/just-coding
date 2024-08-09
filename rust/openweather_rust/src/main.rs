use core::panic;
use std::env::args;
use std::path::Path;
use std::process::exit;

use cache::write_cache;
use apidata::APIData;
use apidata::Geocoding;
use weather::Current;

pub mod http;
pub mod cli;
pub mod cache;
pub mod apidata;
pub mod weather;

fn print_verbose(c: &Current) -> String {
    format!("City: {} | Weather: {}", c.name, c.weather[0].main)
}

fn print_i3_bar(c: &Current) -> String {
    format!("{} | {} | {}", c.name, c.weather[0].main, c.main.temp)
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
        "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
        data.geocoding.lat, data.geocoding.lon, data.appid
    );

    let response: Current = match serde_json::from_str(&http::get(&url)) {
        Ok(w) => w,
        Err(e) => {
            eprintln!("ERROR main::get_weather > failed to serialize Weather: {:#?}", e);
            exit(-1);
        }
    };

    return response;
}

fn cache_weather(weather: &Current) {
    let path: &Path = &Path::new("/home/dio/.config/weather/weather.json");
    
    if !path.exists() {
        eprintln!("weather cache file does not exist.");
        exit(-1);
    }

    let cache: String = serde_json::to_string_pretty(&weather).unwrap();
    write_cache(path, &cache);
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

fn use_args() {
    let mut data: APIData = cli::matches();
    data.geocoding = get_geocoding(&data);
        
    // need to make get
    
    // caching
    cache_apidata(&data);
    // cache_weather(&weather);
}

fn use_cache() {

    let apidata_cache: &Path = &Path::new("/home/dio/.config/weather/config.json");
    let c: APIData = match serde_json::from_str(&cache::read_cache(&apidata_cache)) {
        Ok(a) => a,
        Err(e) => {
            eprintln!("ERROR main > failed to serialize APIData: {:#?}", e);
            exit(-1)
        },
    };

    let weather: Current = get_weather(&c);

    println!("{:#?}", c);
    println!("{}", print_i3_bar(&weather));

    // caching weather
    cache_weather(&weather);
}

fn main() {
    let apidata_cache: &Path = &Path::new("/home/dio/.config/weather/config.json");

    if args().len() > 1 {
        use_args();

    } else if apidata_cache.exists() { 
        use_cache();

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

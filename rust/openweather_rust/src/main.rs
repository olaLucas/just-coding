use std::env::args;
use std::path::Path;
use geocoding::Geocoding;
use apidata::APIData;
use weather::Weather;
use std::process::exit;

pub mod geocoding;
pub mod http;
pub mod cli;
pub mod cache;
pub mod apidata;
pub mod weather;

fn get_geocoding(data: APIData, geo: Geocoding) -> Geocoding {

    let url = format!(
        "http://api.openweathermap.org/geo/1.0/direct?q={},{}&appid={}",
       geo.get_city(), geo.get_country(), data.get_appid() 
    );
    
    let response: Geocoding = match serde_json::from_str(&http::get(&url)) {
        Ok(a) => a,
        Err(e) => {
            eprintln!("ERROR main::get_geocoding > Error while serializing geocoding response: {:#?}", e);
            exit(-1);
        }
    }; 
    
    println!("{:#?}", response);
    return response;
}

fn get_weather(data: APIData, geo: Geocoding) -> Weather {

    let url: String = format!(
        "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
        geo.get_lat(), geo.get_lon(), data.get_appid()
    );

    // reminder: the geocoding data comes inside an array
    let response: Weather = match serde_json::from_str(&http::get(&url)) {
        Ok(w) => w,
        Err(e) => {
            eprintln!("ERROR main::get_weather > failed to serialize Weather. {:#?}", e);
            exit(-1);
        }
    };

    return response;
}


fn main() {
    let home_json_path: &Path = &Path::new("/home/dio/.config/weather/config.json");

    if args().len() > 1 {
        
        let (a, g) = cli::matches();
        let geo: Geocoding = get_geocoding(a,g);
        println!("{:#?}", geo);

    } else if home_json_path.exists() { 
        let c: APIData = serde_json::from_str(&cache::read_cache(&home_json_path)).unwrap();
        let g: Geocoding = serde_json::from_str(&cache::read_cache(&home_json_path)).unwrap();
        println!("{:#?}", get_weather(c, g));

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

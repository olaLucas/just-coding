use core::panic;
use std::collections::HashMap;
use std::env::args;
use std::path::Path;
use std::process::exit;
use apidata::APIData;

pub mod http;
pub mod cli;
pub mod cache;
pub mod apidata;
pub mod weather;

fn get_geocoding(h: Box<HashMap<String, String>>) -> APIData {

    if h.is_empty() {
        eprintln!("ERROR at get_geocoding > HashMap is empty.");
        exit(-1);
    }

    let city = h.get("city").expect("main > city not found.");
    let country = h.get("country").expect("main > country not found.");
    let appid = h.get("appid").expect("main > appid not found.");

    let url = format!(
        "http://api.openweathermap.org/geo/1.0/direct?q={},{}&appid={}",
       city, country, appid 
    );
    
    let geo: serde_json::Value = match http::get(&url) {
        Ok(g) => g,
        Err(e) => {
            eprintln!("failed to get geocoding: {:#?}", e);
            exit(-1);
        }
    };

    return APIData::parser_json(&geo[0]);
}

fn get_weather() {

    let home_json_path: &Path = Path::new("/home/dio/.config/weather/config.json");
    let cache: serde_json::Value = match cache::read_cache(home_json_path) {
        Ok(s) => serde_json::from_str(&s)
            .unwrap_or_else(|_| panic!("failed to convert from string to json.")),
        Err(e) => {
            eprintln!("error: {:#?}", e);
            panic!("failed to read cache. aborting...");
        },
    };

    let cache = APIData::parser_json(&cache);
    println!("{:#?}", cache);

    // reminder: the geocoding data comes inside an array
    
    //let geo = &cache.get("geocoding")
    //    .unwrap_or_else(|| panic!("geocoding not found in cache."));
    //let geo = &geo[0];
    //
    //let weather_url: String = format!(
    //    "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
    //    geo.get("lat").expect("lat not found."),
    //    geo.get("lon").expect("lon not found."),
    //    cache.get("appid")
    //        .expect("appid not found")
    //        .as_str().expect("failed to convert appid to string")
    //);
    
    //println!("{:#?}", http::get(&weather_url));
}

fn main() {
      
    
    if args().len() > 1 {
        let data: APIData = get_geocoding(cli::matches());
        println!("{:#?}", data);

    } else if home_json_path.exists() {
        

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

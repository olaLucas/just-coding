use core::panic;
use std::collections::HashMap;
use std::env::args;
use std::path::Path;

pub mod http;
pub mod cli;
pub mod cache;

struct APIData {
    appid: String,
    city: String,
    country: String,
    units: String
}

impl APIData {
    pub fn new(appid: String, city: String, country: String, units: String) -> APIData{
        APIData {
            appid,
            city,
            country,
            units,
        }
    }

    pub fn parse_json(json: serde_json::Value) -> APIData {
        
    }
}

fn main() {
    let home_json_path: &Path = Path::new("/home/dio/.config/weather/config.json");  
    
    if args().len() > 1 { 
        let m: Box<HashMap<String, String>> = cli::matches();
        
        println!("{:#?}", m);

        let url = format!(
            "http://api.openweathermap.org/geo/1.0/direct?q={},{}&appid={}",
            m.get("city").expect("main > city not found."),
            m.get("country").expect("main > country not found."),
            m.get("appid").expect("main > appid not found.")
        );
        
        let geo: serde_json::Value = match http::get(&url) {
            Ok(g) => g,
            Err(e) => {
                eprintln!("failed to get geocoding: {:#?}", e);
                panic!("Please, check the arguments and try again.");
            }
        };

        let geo = &geo[0];

        let url = format!(
            "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
            geo.get("lat").expect("lat not found in geocoding."),
            geo.get("lon").expect("lon not found in geocoding."),
            m.get("appid").expect("appid not found in matches.")
        );

        println!("{}", url);

    } else if home_json_path.exists() {
        let cache: serde_json::Value = match cache::read_cache(home_json_path) {
            Ok(s) => serde_json::from_str(&s)
                .unwrap_or_else(|_| panic!("failed to convert from string to json.")),
            Err(e) => {
                eprintln!("error: {:#?}", e);
                panic!("failed to read cache. aborting...");
            },
        };

        // reminder: the geocoding data comes inside an array
        
        let geo = &cache.get("geocoding")
            .unwrap_or_else(|| panic!("geocoding not found in cache."));
        let geo = &geo[0];

        let weather_url: String = format!(
            "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
            geo.get("lat").expect("lat not found."),
            geo.get("lon").expect("lon not found."),
            cache.get("appid")
                .expect("appid not found")
                .as_str().expect("failed to convert appid to string")
        );
        
        println!("{:#?}", http::get(&weather_url));

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

use core::panic;
use std::collections::HashMap;
use std::env::args;
use std::path::Path;

pub mod http;
pub mod cli;
pub mod cache;

#[derive(Debug)]
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

    pub fn parser_json(json: serde_json::Value) -> APIData {
        let appid: String = match json.get("appid") {
            Some(s) => s.to_string(),
            None => panic!("ERROR APIData::parse_json -> appid not found in json"),
        };    
        
        let city: String = match json.get("city") {
            Some(s) => s.to_string(),
            None => {
                match json.get("name") { // when reading from cache, name key holds the city
                    Some(s) => s.to_string(),
                    None => panic!("ERROR APIData::parse_json -> city not found in json")
                }
            },
        };

        let country: String = match json.get("country") {
            Some(s) => s.to_string(),
            None => panic!("ERROR APIData::parse_json -> country not found in json"),
        };

        let units: String = match json.get("units") {
            Some(s) => {
                if s != "metric" || s != "imperial" {
                    eprintln!("Invalid measurement units system: {s}");
                    panic!("Error APIData::parse_json -> invalid measurement units system.");
                } else {
                    s.to_string()
                }
            },

            None => String::from("metric"),
        };
        
        APIData::new(appid, city, country, units)
    }
}

fn get_args() {

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


}

fn main() {
    let home_json_path: &Path = Path::new("/home/dio/.config/weather/config.json");  
    
    if args().len() > 1 { 
            } else if home_json_path.exists() {
        let cache: serde_json::Value = match cache::read_cache(home_json_path) {
            Ok(s) => serde_json::from_str(&s)
                .unwrap_or_else(|_| panic!("failed to convert from string to json.")),
            Err(e) => {
                eprintln!("error: {:#?}", e);
                panic!("failed to read cache. aborting...");
            },
        };

        let cache = APIData::parser_json(cache);
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

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

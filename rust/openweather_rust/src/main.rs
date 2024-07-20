use core::panic;
use std::collections::HashMap;
use std::env::args;
use std::path::Path;
use std::process::exit;
use apidata::APIData;
use serde_json::Value;

pub mod http;
pub mod cli;
pub mod cache;
pub mod apidata;
pub mod weather;

fn get_geocoding(h: APIData) -> APIData {

    let url = format!(
        "http://api.openweathermap.org/geo/1.0/direct?q={},{}&appid={}",
       h.get_city(), h.get_country(), h.get_appid() 
    );
    
    let r: APIData match http::get(&url) {
        Ok(s) => match serde_json::from_str(&s) {
            Ok(s) => s,
            Err(e) => {
                eprintln!("ERROR main::get_geocoding > Error while serializing geocoding response: {:#?}", e);
                exit(-1);
            },
        },

        Err(e) => {
            eprintln!("ERROR main::get_geocoding > http::get returned error: {:#?}", e);
            exit(-1);
        }
    } 
    
    println!("{:#?}", r);
}

fn get_weather() {

    let home_json_path: &Path = Path::new("/home/dio/.config/weather/config.json");
    let cache: Value = match cache::read_cache(home_json_path) {
        Ok(s) => serde_json::from_str(&s)
            .expect("failed to convert from string to json."),
        Err(e) => {
            eprintln!("error: {:#?}", e);
            panic!("failed to read cache. aborting...");
        },
    };

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


    
    if args().len() > 1 {
        let data: APIData = get_geocoding(cli::matches());
        println!("{:#?}", data);

    } else if home_json_path.exists() {
        
        let c: String = match cache::read_cache(&home_json_path) {
            OK(s) => s,
            Err(e) => {
                eprintln!("");
                exit(-1)
            }
        };

        let data: APIData = ;
    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

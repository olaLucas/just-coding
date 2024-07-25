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
       data.get_city(), data.get_country(), data.get_appid() 
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

fn get_weather(data: APIData) -> Current {

    let url: String = format!(
        "https://api.openweathermap.org/data/2.5/weather?lat={}&lon={}&appid={}",
        data.get_lat(), data.get_lon(), data.get_appid()
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


fn main() {
    let home_json_path: &Path = &Path::new("/home/dio/.config/weather/config.json");

    if args().len() > 1 {
        
        let mut data: APIData = cli::matches();
        data.set_geo(&get_geocoding(&data));

        let new_cache: String = serde_json::to_string_pretty(&data).unwrap();
        write_cache(home_json_path, new_cache);

    } else if home_json_path.exists() { 
        let c: APIData = match serde_json::from_str(&cache::read_cache(&home_json_path)) {
            Ok(a) => a,
            Err(e) => {
                eprintln!("ERROR main > failed to serialize APIData: {:#?}", e);
                exit(-1)
            },
        };

        println!("{:#?}", c);
        println!("{}", get_weather(c));

    } else {
        panic!("none arguments were provided and neither cache to use.");
    }
}

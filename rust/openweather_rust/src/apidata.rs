use std::process::exit;

#[derive(Debug)]
pub struct APIData {
    appid: String,
    city: String,
    state: String,
    country: String,
    units: String
}

impl APIData {
    pub fn new(appid: String, city: String, state: String, country: String, units: String) -> APIData {
        APIData {
            appid,
            city,
            state,
            country,
            units,
        }
    }

    pub fn parser_json(json: &serde_json::Value) -> APIData {
        let appid: String = match json.get("appid") {
            Some(s) => s.to_string(),
            None => { 
                eprintln!("ERROR APIData::parse_json -> appid not found in json. \nJSON: {:#?}", json);
                exit(-1);
            },
        };    
        
        let city: String = match json.get("city") {
            Some(s) => s.to_string(),
            None => {
                match json.get("name") { // when reading from cache, name key holds the city
                    Some(s) => s.to_string(),
                    None => { 
                        eprintln!("ERROR APIData::parse_json -> city not found in json. \nJSON: {:#?}", json);
                        exit(-1);
                    },
                }
            },
        };

        let state: String = match json.get("state") {
            Some(s) => s.to_string(),
            None => {
                eprintln!("ERROR APIData::parse_json -> state not found in json. \nJSON: {:#?}", json);
                exit(-1)
            }
        };

        let country: String = match json.get("country") {
            Some(s) => s.to_string(),
            None => { 
                eprintln!("ERROR APIData::parse_json -> country not found in json. \nJSON: {:#?}", json);
                exit(-1);
            },
        };

        let units: String = match json.get("units") {
            Some(s) => {
                if s != "metric" || s != "imperial" {
                    eprintln!("Error APIData::parse_json -> invalid measurement units system.\nInvalid measurement units system: {s}");
                    panic!();
                } else {
                    s.to_string()
                }
            },

            None => String::from("metric"),
        };
        
        APIData::new(appid, city, state, country, units)
    }
}

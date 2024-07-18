use core::f64;
use std::{process::exit, str::FromStr};
use chrono::{NaiveTime, Timelike};

#[derive(Debug)]
pub struct Weather {
    date: String,
    weather: (String, String),
    sunset: String,
    sunrise: String,
        
    // max, curr, min
    temp: (f64, f64, f64),
    feels_like: f64,
    humidity: u64,
}

impl Weather {
    pub fn new(
        date: String,
        weather: (String, String),
        sunset: String, 
        sunrise: String,
            
        // max, curr, min
        temp: (f64, f64, f64), 
        feels_like: f64,
        humidity: u64,
    ) -> Weather {
        Weather {
            date,
            weather,
            sunset, 
            sunrise,

            temp, 
            feels_like,
            humidity,
        }
    }


    pub fn parse_json(json: &serde_json::Value) -> Weather {
       
        // decopondo o json
        let weather: &serde_json::Value = match json.get("weather") {
            Some(s) => &s[0], // weather vem dentro de um array
            None => {
                eprintln!("ERROR Weather::parse_json > weather object not found in json.");
                exit(-1);
            }
        };

        let main: &serde_json::Value = match json.get("main") {
            Some(s) => s,
            None => {
                eprintln!("ERROR Weather::parse_json > main object not found in json.");
                exit(-1);
            }
        };

        let sys: &serde_json::Value = match json.get("sys") {
            Some(s) => s,
            None => {
                eprintln!("ERROR Weather::parse_json > sys object not found in json.");
                exit(-1);
            }
        };

        let dt: String = match json.get("dt") {
            Some(s) => { 
                let s = match NaiveTime::from_str(&s.to_string()) {
                    Ok(s) => s,
                    Err(e) => {
                        eprintln!("ERROR Weather::parse_json > NaiveTime returned Err: {:#?}", e);
                        exit(-1);
                    }
                };

                let (period, hour) = s.hour12();
                let period: &str = match period {
                    false => "AM",
                    true => "PM",
                };

                format!("{}:{} {}", hour, s.minute(), period)
            },

            None => {
                eprintln!("ERROR Weather::parse_json > dt not found in json.");
                exit(-1);
            },
        };

        let weather: (String, String) = {

            let main: String = match weather.get("main") {
                Some(s) => s.to_string(),
                None => {
                    eprintln!("ERROR Weather::parse_json > weather.main not found.");
                    exit(-1);
                }
            };

            let description: String = match weather.get("description") {
                Some(s) => s.to_string(),
                None => {
                    eprintln!("ERROR Weather::parse_json > weather.description not found.");
                    exit(-1);
                },
            };

            (main, description)
        };

        let sunrise: String = match sys.get("sunrise") {
            Some(s) => s.to_string(),
            None => {
                eprintln!("");
                exit(-1);
            },
        };

        let sunset: String = match sys.get("sunset") {
            Some(s) => s.to_string(),
            None => {
                eprintln!();
                exit(-1);
            },
        };
                // min, curr, max 
        let temp: (f64, f64, f64) = {
            let min: f64 = match main.get("temp_min") {
                Some(s) => s.as_f64()
                    .expect("ERROR Weather::parse_json > failed to convert min temp value to f64."),
                None => {
                    eprintln!("ERROR Weather::parse_json > temp_min not found in json.");
                    exit(-1);
                }
            };

            let curr: f64 = match main.get("temp") {
                Some(s) => s.as_f64()
                    .expect("ERROR Weather::parse_json > failed to convert curr temp to f64."),
                None => {
                    eprintln!("ERROR Weather::parse_json > temp not found in json.");
                    exit(-1);
                }
            };

            let max: f64 = match main.get("temp_max") {
                Some(s) => s.as_f64()
                    .expect("ERROR Weather::parse_json > failed to convert max temp to f64."), 
                None => {
                    eprintln!("ERROR Weather::parse_json > temp_max not found in json.");
                    exit(-1);
                }
            };

            (min, curr, max)
        };

        let feels_like: f64 = match main.get("feels_like") {
            Some(s) => s.as_f64()
                .expect("ERROR Weather::parse_json > failed to convert feels like to f64."), 
            None => {
                eprintln!("ERROR Weather::parse_json > feels_like not found in json.");
                exit(-1);
            }
        };

        let humidity: u64 = match main.get("humidity") {
            Some(s) => s.as_u64()
                .expect("ERROR Weather::parse_json > failed to convert max temp to u64."),
            None => {
                eprintln!("ERROR Weather::parse_json > humidity not found in json.");
                exit(-1);
            },
        };

        Weather::new(
            dt,
            weather,
            sunset, 
            sunrise, 
            temp, 
            feels_like, 
            humidity
        )
    }
}

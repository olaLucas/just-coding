use chrono::{NaiveTime, Timelike};
use serde::{Deserialize, Serialize};

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
pub struct Weather {
    date: String,
    weather: (String, String),
    sunset: String,
    sunrise: String,
        
    // max, curr, min
    temp: (f32, f32, f32),
    feels_like: f32,
    humidity: u8,
}

impl Weather {
    pub fn new(date: String, weather: (String, String), sunset: String, sunrise: String, temp: (f32, f32, f32), feels_like: f32, humidity: u8) -> Weather {
        Weather {
            date, weather, sunset, 
            sunrise, temp, feels_like,
            humidity,
        }
    }
}

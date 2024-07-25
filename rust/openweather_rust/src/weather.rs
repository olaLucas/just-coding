use chrono::{NaiveTime, Timelike};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
struct Main {
    temp: f32,
    feels_like: f32,
    temp_min: f32,
    temp_max: f32,
    pressure: f32,
    humidity: u8,
    sea_level: i32,
    grnd_level: i32
}

#[derive(Debug, Serialize, Deserialize)]
struct Sys {
    r#type: u8,
    id: i32,
    country: String,
    sunrise: i32,
    sunset: i32
}

#[derive(Debug, Serialize, Deserialize)]
struct Weather {
    id: i32,
    main: String,
    description: String,
    icon: String,
}

#[derive(Debug, Serialize, Deserialize)]
struct Coord {
    lat: f32,
    lon: f32
}

#[derive(Debug, Serialize, Deserialize)]
struct Wind {
    speed: f32,
    deg: f32,
    gust: f32
}

#[derive(Debug, Serialize, Deserialize)]
struct Rain {
    _1h: f32,
}

#[derive(Debug, Serialize, Deserialize)]
struct Clouds {
    all: i32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Current {
    coord: Coord,
    
    base: String,
    
    weather: Vec<Weather>,
    main: Main,

    visibility: i32,
    
    // wind: Wind,
    //rain: Rain,
    clouds: Clouds,
    
    dt: i32,

    sys: Sys,
    
    timezone: i32,
    id: i32,
    name: String,
    cod: i32,
}

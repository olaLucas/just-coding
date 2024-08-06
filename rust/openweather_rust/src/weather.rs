use chrono::{NaiveTime, Timelike};
use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct Main {
   pub temp: f32,
   pub feels_like: f32,
   pub temp_min: f32,
   pub temp_max: f32,
   pub pressure: f32,
   pub humidity: u8,
   pub sea_level: i32,
   pub grnd_level: i32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Sys {
   pub r#type: u8,
   pub id: i32,
   pub country: String,
   pub sunrise: i32,
   pub sunset: i32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Weather {
   pub id: i32,
   pub main: String,
   pub description: String,
   pub icon: String,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Coord {
   pub lat: f32,
   pub lon: f32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Wind {
   pub speed: f32,
   pub deg: f32,
   pub gust: f32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Rain {
   pub _1h: f32,
}


#[derive(Debug, Serialize, Deserialize)]
pub struct Clouds {
   pub all: i32
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Current {
   pub coord: Coord,
   pub weather: Vec<Weather>,
   pub main: Main,
   // pub wind: Wind,
   // pub rain: Rain,
   pub clouds: Clouds,
   pub sys: Sys,

   pub base: String,
   pub dt: i32,
   pub visibility: i32,
   pub timezone: i32,
   pub id: i32,
   pub name: String,
   pub cod: i32,
}

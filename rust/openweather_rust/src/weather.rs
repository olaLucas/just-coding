use chrono::{NaiveTime, Timelike};
use serde::{Deserialize, Serialize};

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
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

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
struct Sys {
    r#type: u8,
    id: i32,
    country: String,
    sunrise: i32,
    sunset: i32
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
struct Weather {
    id: i32,
    main: String,
    description: String,
    icon: String,
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
struct Coord {
    lat: f32,
    lon: f32
}

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
pub struct Current {
    main: Main,
    sys: Sys,
    coord: Coord,
    weather: Vec<Weather>,
    base: String,
    visibility: String,
    id: String,
    timezone: i32,
    cod: u8,


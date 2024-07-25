use core::fmt;
use std::fmt::{Display, Formatter};

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

impl Display for Main {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Temperatures: (Min: {0}, Curr: {1}, Max: {2})\n
            Feels like: {3}\n
            Pressure: {4}\n
            Humidity: {5}\n
            Sea level: {6}\n
            Ground level: {7}",  
            self.temp_min, 
            self.temp, 
            self.temp_max, 
            self.feels_like, 
            self.pressure, 
            self.humidity, 
            self.sea_level, 
            self.grnd_level
        )
    }
}

#[derive(Debug, Serialize, Deserialize)]
struct Sys {
    r#type: u8,
    id: i32,
    country: String,
    sunrise: i32,
    sunset: i32
}

impl Display for Sys {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "<< Sys >>\n
            Type: {0}\n
            ID: {1}\n
            Country: {2}\n
            Sunrise: {3}\n
            Sunset: {4}\n",
            self.r#type,
            self.id,
            self.country,
            self.sunrise,
            self.sunrise
        )
    }
}

#[derive(Debug, Serialize, Deserialize)]
struct Weather {
    id: i32,
    main: String,
    description: String,
    icon: String,
}

impl Display for Weather {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "<< Weather >>\n
            ID: {0}\n
            Main: {1}\n
            Description: {2}\n
            Icon: {3}",
            self.id,
            self.main,
            self.description,
            self.icon
        )
    }
}

#[derive(Debug, Serialize, Deserialize)]
struct Coord {
    lat: f32,
    lon: f32
}

impl Display for Coord {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "latitude: {0}, longitude: {1}\n", self.lat, self.lon)
    }
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

impl Display for Rain {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Rain: {}", self._1h)
    }
}

#[derive(Debug, Serialize, Deserialize)]
struct Clouds {
    all: i32
}

impl Display for Clouds {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Clouds: all {}", self.all)
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Current {
    coord: Coord,
    weather: Vec<Weather>,
    main: Main,
    //wind: Wind,
    //rain: Rain,
    clouds: Clouds,
    sys: Sys,

    base: String,
    dt: i32,
    visibility: i32,
    timezone: i32,
    id: i32,
    name: String,
    cod: i32,
}

impl Display for Current {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "Coord: {}\n
            Weather: {}\n
            Main: {}\n
            Clouds: {}\n
            Sys: {}\n
            Base: {}\n
            Date & Time: {}\n
            Visibility: {}\n
            Timezone: {}\n
            ID: {}\n
            Name: {}\n
            cod: {}",
            self.coord,
            self.weather[0],
            self.main,
            self.clouds,
            self.sys,
            self.base,
            self.dt,
            self.visibility,
            self.timezone,
            self.id,
            self.name,
            self.cod
            
        )    
    }
}

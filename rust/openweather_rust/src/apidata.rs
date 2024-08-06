use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct APIData {
    pub appid: String,
    pub geocoding: Geocoding,
    pub units: String
}

impl APIData {
    pub fn new(appid: String, geocoding: Geocoding, units: String) -> APIData {
        APIData {
            appid,
            geocoding,
            units,
        }
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Geocoding {
   pub name: String,
   pub lat: f32,
   pub lon: f32,
   pub country: String,
   pub state: String
}

impl Geocoding {
    pub fn new(country: String, lat: f32, lon: f32, name: String, state: String) -> Geocoding {
        Geocoding {
            name,
            lat,
            lon,
            country,
            state
        }
    }

    pub fn from(g: &Geocoding) -> Geocoding {
        Geocoding {
            name: String::from(&g.name),
            lat: g.lat,
            lon: g.lon,
            country: String::from(&g.country),
            state: String::from(&g.state),
        }
    }
}

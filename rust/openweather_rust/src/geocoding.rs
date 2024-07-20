use serde::{Deserialize, Serialize};

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
pub struct Geocoding {
    country: String,
    lat: f32,
    lon: f32,
    name: String,
    state: String
}

impl Geocoding {
    pub fn new(country: String, lat: f32, lon: f32, name: String, state: String) -> Geocoding {
        Geocoding {
            country,
            lat,
            lon,
            name,
            state
        }
    }

    pub fn get_country(&self) -> &str {
        &self.country
    }

    pub fn get_lat(&self) -> f32 {
        self.lat
    }

    pub fn get_lon(&self) -> f32 {
         self.lon
    }

    pub fn get_city(&self) -> &str {
        &self.name
    }

    pub fn get_state(&self) -> &str {
         &self.state
    }
}

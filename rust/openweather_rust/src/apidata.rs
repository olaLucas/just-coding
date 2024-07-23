use serde::{Deserialize, Serialize};

#[derive(Debug, Serialize, Deserialize)]
pub struct APIData {
    appid: String,
    geocoding: Geocoding,
    units: String
}

impl APIData {
    pub fn new(appid: String, geocoding: Geocoding, units: String) -> APIData {
        APIData {
            appid,
            geocoding,
            units,
        }
    }
    pub fn get_appid(&self) -> &str {
        &self.appid
    }    

    pub fn get_units(&self) -> &str {
        &self.units
    }

    pub fn get_country(&self) -> &str {
        &self.geocoding.country
    }

    pub fn get_lat(&self) -> f32 {
        self.geocoding.lat
    }

    pub fn get_lon(&self) -> f32 {
         self.geocoding.lon
    }

    pub fn get_city(&self) -> &str {
        &self.geocoding.name
    }

    pub fn get_state(&self) -> &str {
         &self.geocoding.state
    }

    pub fn set_geo(&mut self, g: &Geocoding) {
       self.geocoding = Geocoding::from(g); 
    }
}

#[derive(Debug, Serialize, Deserialize)]
pub struct Geocoding {
    name: String,
    lat: f32,
    lon: f32,
    country: String,
    state: String
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

    //pub fn get_country(&self) -> &str {
    //    &self.country
    //}
    //
    //pub fn get_lat(&self) -> f32 {
    //    self.lat
    //}
    //
    //pub fn get_lon(&self) -> f32 {
    //     self.lon
    //}
    //
    //pub fn get_city(&self) -> &str {
    //    &self.name
    //}
    //
    //pub fn get_state(&self) -> &str {
    //     &self.state
    //}
}

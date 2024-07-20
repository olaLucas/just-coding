use serde::{Deserialize, Serialize};

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
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
    pub fn get_appid(&self) -> &str {
        &self.appid
    }

    pub fn get_city(&self) -> &str {
        &self.city
    }

    pub fn get_country(&self) -> &str {
        &self.country
    }

    pub fn get_units(&self) -> &str {
        &self.units
    }
}

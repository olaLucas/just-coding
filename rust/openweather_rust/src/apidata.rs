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
}

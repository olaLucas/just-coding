use serde::{Deserialize, Serialize};

#[derive(Debug)]
#[derive(Serialize, Deserialize)]
pub struct APIData {
    appid: String,
    units: String
}

impl APIData {
    pub fn new(appid: String, units: String) -> APIData {
        APIData {
            appid,
            units,
        }
    }
    pub fn get_appid(&self) -> &str {
        &self.appid
    }    

    pub fn get_units(&self) -> &str {
        &self.units
    }
}

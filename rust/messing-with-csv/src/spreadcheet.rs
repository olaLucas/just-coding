use std::path::Path;

#[derive(Debug, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "PascalCase")]
pub struct Customer {
    pub index: i32,

    #[serde(rename = "Customer Id")]
    pub customer_id: String,

    #[serde(rename = "First Name")]
    pub first_name: String,

    #[serde(rename = "Last Name")]
    pub last_name: String,
    pub company: String,
    pub city: String,
    pub country: String,

    #[serde(rename = "Phone 1")]
    pub phone1: String,

    #[serde(rename = "Phone 2")]
    pub phone2: String,
    pub email: String,

    #[serde(rename = "Subscription Date")]
    pub subscription_date: String,
    pub website: String
}

pub struct SpreadSheet {
    content: Vec<Customer>,
    len: i32,
}

impl SpreadSheet {
    pub fn new() -> SpreadSheet {
       SpreadSheet {
            content: Vec::new(),
            len: 0
        }
    }
    
    pub fn content(&self) -> &Vec<Customer> {
        &self.content
    }

    pub fn load(&mut self, path: &str) {
        if !Path::new(path).exists() {
            eprintln!("SpreadSheet::load() > {} does not exist.", path);
            std::process::exit(-1);
        }

        let mut r = match csv::Reader::from_path(path) {
            Ok(r) => r,
            Err(e) => {
                eprintln!("SpreadSheet::load() > failed to read {path}: {e:#?}");
                std::process::exit(-1);
            }
        };

        for record in r.deserialize().filter_map(|c| c.ok()) {
            self.content.push(record); self.len += 1;
        }
    }
}

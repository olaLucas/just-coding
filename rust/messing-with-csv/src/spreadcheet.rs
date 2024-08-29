use std::{fmt::Display, path::Path};

enum CustomerFields {
    Index,
    Id,
    FirstName,
    LastName,
    Company,
    City,
    Country,
    Phone1,
    Phone2,
    Email,
    SubscriptionDate,
    Website
}

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

impl Display for Customer {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Index: {}\n", self.index)?;
        write!(f, "Customer ID: {}\n", self.customer_id)?;
        write!(f, "Subscription Date: {}\n", self.subscription_date)?;
        write!(f, "Name: {} {}\n", self.first_name, self.last_name)?;
        write!(f, "City: {}, Country: {}\n", self.city, self.country)?;
        write!(f, "Phones: {} and {}\n", self.phone1, self.phone2)?;
        write!(f, "Email: {}\n\n", self.email)?;

        Ok(())
    }
}

impl Display for SpreadSheet {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        for i in self.content.iter() {
            write!(f, "{}", i)?
        }

        Ok(())
    }
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

    pub fn sort_by_index(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.index.cmp(&b.index));
        &self.content
    }

    pub fn sort_by_first_name(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.first_name.cmp(&b.first_name));
        &self.content
    }

    pub fn sort_by_last_name(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.last_name.cmp(&b.last_name));
        &self.content
    }

    pub fn sort_by_company(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.company.cmp(&b.company));
        &self.content
    }

    pub fn sort_by_country(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.country.cmp(&b.country));
        &self.content
    }

    pub fn sort_by_city(&mut self) -> &Vec<Customer> {
        self.content.sort_by(|a, b| a.city.cmp(&b.city));
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

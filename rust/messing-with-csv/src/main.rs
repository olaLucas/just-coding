
#[derive(Debug, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "PascalCase")]
struct Customer {
    index: i32,
    
    #[serde(rename = "Customer Id")]
    customer_id: String,
    
    #[serde(rename = "First Name")]
    first_name: String,

    #[serde(rename = "Last Name")]
    last_name: String,
    company: String,
    city: String,
    country: String,

    #[serde(rename = "Phone 1")]
    phone1: String,
    
    #[serde(rename = "Phone 2")]
    phone2: String,
    email: String,

    #[serde(rename = "Subscription Date")]
    subscription_date: String,
    website: String
}

fn read_csv(path: &str) -> Box<Vec<Customer>> {
    let mut array: Box<Vec<Customer>> = Box::new(Vec::new());
    let mut reader = match csv::Reader::from_path(path) {
        Ok(r) => r,
        Err(e) => {
            eprintln!("Error while trying to initilize reader: {}", e);
            std::process::exit(-1);
        }
    };

    for record in reader.deserialize() {
        match record {
            Ok(r) => array.push(r),
            Err(e) => {
                eprintln!("error while trying to Serialize: {e}");
            }
        }
    }

   return array;
}

fn main() {
    println!("Records: {:#?}", read_csv("customers-100.csv"));
}

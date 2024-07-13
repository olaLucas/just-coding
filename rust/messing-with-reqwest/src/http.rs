use core::panic;
use reqwest::blocking::Client;

pub fn get(url: &str) -> serde_json::Value {
    let http_client = Client::new(); 
    let http_response = match http_client.get(url).send() {
        Ok(r) => match r.text() {
            Ok(s) => String::from(s),
            Err(e) => {
                eprintln!("http::get > Error in get resquest text: {:#?}", e);
                String::new()
            }
        }

        Err(e) => { 
            eprintln!("http::get > Error in get request: {:#?}", e); 
            String::new() 
        },
    };
    
    serde_json::from_str(&http_response)
        .unwrap_or_else(|_| panic!("http::http_get > error while trying to serialize http_response"))
}


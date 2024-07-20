use reqwest::blocking::Client;
use std::process::exit;

pub fn get(url: &str) -> String {
    let http = Client::new();
    match http.get(url).send() {
        Ok(res) => {
            match res.text() {
                Ok(s) => s,

                Err(e) => {
                    eprintln!("http::get > Error while trying to extract text from response: {:#?}", e);
                    exit(-1);
                }
            }
        },

        Err(e) => {
            eprintln!("http::get > Error while sending the get request: {:#?}", e);
            exit(-1);
        },
    } 
}

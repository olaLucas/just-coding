use reqwest::blocking::Client;
use serde_json::Value;

pub fn get(url: &str) -> Result<Value, reqwest::Error> {
    let http = Client::new();
    match http.get(url).send() {
        Ok(res) => {
            match res.text() {
                Ok(s) => {
                    return Ok(serde_json::from_str(&s)
                        .expect("http::get > Error while serializing the response;")); 
                },

                Err(e) => {
                    eprintln!("http::get > Error while trying to extract text from response: {:#?}", e);
                    return Err(e);
                }
            }
        },

        Err(e) => {
            eprintln!("http::get > Error while sending the get request: {:#?}", e);
            return Err(e);
        },
    } 
}

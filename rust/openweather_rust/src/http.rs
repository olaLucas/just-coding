use reqwest::blocking::Client;

pub fn get(url: &str) -> Result<String, reqwest::Error> {
    let http = Client::new();
    match http.get(url).send() {
        Ok(res) => {
            match res.text() {
                Ok(s) => {
                    return Ok(s); 
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

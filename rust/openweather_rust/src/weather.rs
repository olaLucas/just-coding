use std::process::exit;

#[derive(Debug)]
pub struct Weather {
    date: String,
    name: String,
    country: String,
    weather: (String, String),
    sunset: String,
    sunrise: String,
        
    // max, curr, min
    temp: (f32, f32, f32),
    feels_like: f32,
    humidity: f32,
}

impl Weather {
    pub fn new(
        date: String, name: String,
        country: String, weather: (String, String),
        sunset: String, sunrise: String,
            
        // max, curr, min
        temp: (f32, f32, f32), feels_like: f32,
        humidity: f32,
    ) -> Weather {
        Weather {
            date, name,
            country, weather,
            sunset, sunrise,

            temp, feels_like,
            humidity,
        }
    }


    pub fn parse_json(json: &serde_json::Value) -> Weather {
        
        let date: String = match json.get("date") {
            Some(s) => s.to_string(),
            None => String::new(), // TODO: get the system time
        };

        let country: String = match json.get("date") {
            Some(s) => s.to_string(),
            None => {
                eprintln!("WARNING Weather::parse_json > contry not found.");
                String::new()
            },
        };

        let weather: (String, String) = {
            let main: String = String::new();
            let description: String = String::new();

            main = match json.get("weather_main") {
                Some(s) => s.to_string(),
                None => {
                    eprintln!("ERROR Weather::parse_json > weather_main not found.");
                    exit(-1);
                }
            };

            (main, description)
        };

    }



}

use clap::arg;
use clap::value_parser;
use clap::Command;
use clap::Arg;
use std::process::exit;
use crate::apidata::{APIData, Geocoding};

pub fn matches() -> APIData {

    let arguments: &[Arg] = &[
        arg!(appid: -a --appid <STRING> "Openweather API Key")
            .num_args(1)
            .required(true)
            .value_parser(value_parser!(String)),
        
        arg!(city: -c --city <STRING> "City name")
            .num_args(1)
            .required(true)
            .value_parser(value_parser!(String)),
        
        arg!(country: -C --country <STRING> "Country name")
            .num_args(1)
            .required(true)
            .value_parser(value_parser!(String)),

        arg!(units: -u --units <STRING> "metric or imperial (default: metric)")
            .num_args(1)
            .required(false)
            .value_parser(value_parser!(String)),
    ];     

    let matches = Command::new("Weather")
                        .author("Dio")
                        .args(arguments)
                        .get_matches();
    
    let appid: String = match matches.get_one::<String>("appid") {
        Some(s) => s.to_string(),
        None => {
            eprintln!("ERROR cli::matches > appid not found.");
            exit(-1);
        }
    };

    let city: String = match matches.get_one::<String>("city") {
        Some(s) => s.to_string(),
        None => {
            eprintln!("ERROR cli::matches > city not found.");
            exit(-1);
        }
    };

    let country: String = match matches.get_one::<String>("country") {
        Some(s) => s.to_string(),
        None => {
            eprintln!("ERROR cli::matches > country not found.");
            exit(-1);
        }
    };

    let units: String = match matches.get_one::<String>("units") {
        Some(s) => s.to_string(),
        None => "metric".to_string() 
    };

    return APIData::new(appid, Geocoding::new(country, 0.0, 0.0, city, String::default()), units);
} 

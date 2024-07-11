use std::collections::HashMap;
use clap::arg;
use clap::value_parser;
use clap::Command;
use clap::Arg;

pub fn matches() -> (String, String, String, String) {
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

    let appid = matches.get_one::<String>("appid")
        .unwrap()
        .to_string();
    
    let city = matches.get_one::<String>("city")
        .unwrap()
        .to_string();
    
    let country = matches.get_one::<String>("country")
        .unwrap()
        .to_string();

    let units = match matches.get_one::<String>("units") {
        Some(u) => u.to_string(),
        None => "metric".to_string(), // sets metric as default
    };

    return (appid, city, country, units);
} 

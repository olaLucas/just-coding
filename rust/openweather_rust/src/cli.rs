use std::collections::HashMap;
use clap::arg;
use clap::value_parser;
use clap::Command;
use clap::Arg;

pub fn matches() -> Box<HashMap<String, String>> {

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
    

    let mut hash: Box<HashMap<String, String>> = Box::new(HashMap::new());

    let args_array = [
        "appid",
        "city",
        "country",
        "units",
    ];

    for item in args_array.iter() {
        hash.insert(
            item.to_string(), 
            match matches.get_one::<String>(item) {
                Some(s) => s.to_string(),
                None => String::from("metric"),
            }
        );
    }

    return hash;
} 

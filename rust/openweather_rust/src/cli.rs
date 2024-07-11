pub mod cli {
    use clap::arg;
    use clap::value_parser;
    use clap::Command;
    use clap::Arg;
   
    
    pub fn matches() -> (Option<String>, Option<String>, Option<String>, Option<String>) {
        let arguments: &[Arg] = &[
            arg!(appid: -a --appid <STRING> "Openweather API Key")
                .num_args(1)
                .value_parser(value_parser!(String)),
            
            arg!(city: -c --city <STRING> "City name")
                .num_args(1)
                .value_parser(value_parser!(String)),
            
            arg!(country: -C --country <STRING> "Country name")
                .num_args(1)
                .value_parser(value_parser!(String)),

            arg!(units: -u --units <STRING> "metric or imperial (default: metric)")
                .num_args(1)
                .value_parser(value_parser!(String)),
        ];     

        let matches = Command::new("Weather")
                            .author("Dio")
                            .args(arguments)
                            .get_matches();

        if let Some(appid) {

        }
    }    
}

use std::path::Path;

pub mod http;
pub mod cache;


fn main() { 
    let home_cache = Path::new("/home/dio/.config/weather/config.json");
    let cache = cache::read(home_cache).unwrap();
    let cache_geo = &cache["geocoding"][0];

    let url: String = format!(
        "http://api.openweathermap.org/geo/1.0/direct?q={}&appid={}",
        cache_geo["name"].as_str().expect("main > city not found."),
        cache["appid"].as_str().expect("main > appid not found in cache") 
    );
   
    println!("{:#?}", &url);
    let _ = cache::write_geocoding(home_cache, http::get(&url));
}

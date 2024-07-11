pub mod api;
pub mod cli;
pub mod cache;


use api::{
    api::data,
    weather::Weather,
    geocoding::Geocoding,
};


fn main() {
    println!("Hello, world!");
}

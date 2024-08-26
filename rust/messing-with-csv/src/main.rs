mod spreadcheet;
use spreadcheet::{Customer, SpreadSheet};

fn main() {
    let mut s = SpreadSheet::new();
    s.load("customers-100000.csv");
    
}

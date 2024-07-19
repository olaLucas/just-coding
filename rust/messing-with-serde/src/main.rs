use serde::Serialize;
use serde::Deserialize;

#[derive(Serialize, Deserialize)]
struct User {
    name: String,
    age: u8,
    address: String,
    gender: String
}

fn main() {
    let p = User {
        name: "Lucas".to_string(),
        age: 20,
        address: "Santa Ines".to_string(),
        gender: "Masc".to_string(),
    };
    
    println!("{}", serde_json::to_string_pretty(&p).unwrap());
}

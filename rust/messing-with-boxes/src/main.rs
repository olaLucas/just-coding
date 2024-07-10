pub mod structs;
use structs::{person::Person};

fn main() {
    let p: Box<Person> = Box::new(Person::default());
    println!("{:#?}", p);
}

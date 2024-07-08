pub mod data_structure;
use data_structure::{person::Person, stack::Stack};

fn main() {

    let mut owners = Stack::new();
    owners.insert(
        Person::new(
            "Lucas".to_string(),
            20,
            "Supra".to_string(),
        )
    );

    println!("{:#?}", owners);

    let element: Person = owners.remove();

    println!("stack: {:#?}", owners);
    println!("name: {}", element.name());
    println!("age: {}", element.age());
    println!("car: {}", element.car());
}

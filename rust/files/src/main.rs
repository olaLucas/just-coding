use std::env;

pub mod dir;

#[derive(Debug)]
struct dog {
  name: String,
  age: u8,
}

fn parse_terminal_args() -> (String, u8) {
  let term_arg = env::args();
  if term_arg.len() > 1 {
    let name: String = term_arg.first().unwrap()
      .expect("Error while trying to retrieve dogs name");
    let age: u8 = term_arg.first().unwrap()
      .expect("Error while trying to retrieve dogs age").parse::<u8>().ok().unwrap(); 

      return (name, age);
  }
}

fn main() {
  let bob: dog = parse_terminal_args();
  println!("{:?}", bob);
}
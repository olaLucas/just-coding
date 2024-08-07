use clap::{Arg, ArgMatches, Command, arg, value_parser};

fn sub(vec_numbers: &Vec<i32>) -> i32 {
  let mut result: i32 = 0;
  for i in vec_numbers {
    result += i;
  }

  result
}

fn add(vec_numbers: &Vec<i32>) -> i32 {
  let mut result: i32 = 0;
  for i in vec_numbers {
    result += i;
  }
  
  result
}

fn parse_terminal_args(arguments: &[Arg]) -> ArgMatches {

  Command::new("TESTING CLAP")
    .author("me, myself and I")
    .about("testing how to handle cli args with clap")
    .args(arguments)
    .get_matches()
}


fn main() {
  let arguments = &[
    arg!(sum: -a --sum <NUMBERS> "sum two numbers")
      .value_parser(value_parser!(i32))
      .num_args(1..),
    arg!(sub: -s --sub <NUMBERS> "subtract two numbers")
      .value_parser(value_parser!(i32))
      .num_args(1..),
  ];

  let matches = parse_terminal_args(arguments);
  if let Some(args) = matches.get_many::<i32>("sum") {
    let numbers = args.copied().collect();
    println!("sum: {}", add(&numbers));
  } 
  else if let Some(args) = matches.get_many::<i32>("sub") {
    let numbers = args.copied().collect();
    println!("subtraction: {}", sub(&numbers));
  }
}

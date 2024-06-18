use std::env;

fn read_term_args() -> Vec<String> {
    let mut vec_args: Vec<String> = Vec::new();
    let args = env::args();
    if args.len() > 1 {
       let args = args.skip(1);
       for arg in args {
            vec_args.push(arg);
       }
    }

    return vec_args;
}

fn main() {
    let vec: Vec<String> = read_term_args();
    println!("{:?}", vec);
}

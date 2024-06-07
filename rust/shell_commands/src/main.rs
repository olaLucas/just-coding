// use std::env;
use std::process::Command;

fn main() 
{   
    // let args : Vec<String> = env::args().collect();
    // dbg!(args);
    
    let proc = Command::new("ls")
                            .arg("-l").arg("-a").arg("-h")
                            .output().expect("error");
    println!("{}", String::from_utf8(proc.stdout).unwrap());
}

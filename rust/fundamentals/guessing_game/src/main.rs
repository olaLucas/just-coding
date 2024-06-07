use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    println!("Advinhe o número!");
    let num = rand::thread_rng().gen_range(1..=100);
    
    loop {
        let mut chute =  String::new();
        println!("Insira seu chute: ");

        io::stdin()
            .read_line(&mut chute)
            .expect("Falha ao ler a linha!");
        
        let chute: u32 = match chute.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };

        match chute.cmp(&num) {
            Ordering::Less => println!("Muito pequeno..."),
            Ordering::Greater => println!("Muito grande..."),
            Ordering::Equal => {
                println!("Você ganhou!");
                break;
            }
        }
    }
}

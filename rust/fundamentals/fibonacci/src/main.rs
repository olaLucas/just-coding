use std::io;

fn main() {
    let mut n: u32 = 1;
    let mut x: u32 = 0;
    let mut y: u32 = 0;

    let mut rep = String::new();

    println!("Insira a quantidade de repetições: ");
    io::stdin()
        .read_line(&mut rep)
        .expect("Erro ao ler sua entrada. Digite apenas números.");

    let rep : u32 = rep
                .trim()
                .parse()
                .expect("Erro ao converter entrada para números.");

    if rep > 0 {
        for i in (0..rep).rev() {
            y = x + n;
            x = n;
            n = y;
        }

        println!("valor final: {y}");
    }
    else
    {
        println!("Finalizando programa...");
    }
}

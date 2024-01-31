use std::io;

fn main() {
    println!("Bem vindo ao conversor de temperatura!");
    println!("Insira a temperatura em celsius para ser convertida em fahrenheit:");
    
    let mut celsius = String::new();

    io::stdin()
        .read_line(&mut celsius)
        .expect("Falha ao ler sua entrada.");

    let celsius: f32 = celsius
                        .trim()
                        .parse()
                        .expect("Não foi possível converter a sua entrada em número, certifique-se de que digitou um número válido.");

    println!("Celsius: {celsius}, Fahrenheit: {}", converter(celsius));
}

fn converter(celsius: f32) -> f32 {
    (celsius * 1.8) + 32.0
}

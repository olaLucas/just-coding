fn main() {
    let nome = "Lucas dos Santos Silva";
    let array = nome.as_bytes();
    for (i, &letter) in array.iter().enumerate() {
        println!("{}, {}", i, letter);
    }
}
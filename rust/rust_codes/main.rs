fn f(x: u8) -> Option<u8> {
    if x % 2 == 0 {
        return Some(x);
    } else {
        return None;
    }
}

fn main() {
    let n: u8 = 10;
    match f(n) {
        Some(n) => println!("{n} é par"),
        None => println!("{n} não é par")
    }
}

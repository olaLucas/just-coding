fn main() {
    let str_stack = "Hello, World!"; // string literal (immutable)
    let mut str_heap = String::from("Hello"); // string on heap

    println!("{str_stack}");
    change_string(&mut str_heap, ", World!");
    print_string(str_heap); // agora a string pertence à função 
                            // e será dropada quando a mesma encerrar

    let mut nome : String = String::from("Lucas dos Santos");
    
    // inumeras immutable ref são permitidas 
    let ref1 = &nome;
    let ref2 = &nome;

    // let mut refmut = &nome; // não permitido pois ref1 e 2 dependem dos dados

    println!("ref1: {ref1}, ref2: {ref2}");

    let mut refmut = &nome; // permitido pois ref1 e 2 já utilizaram os dados
    println!("refmut: {refmut}");

    let mut n : String = String::from("Lucas Santos");
    let s1 = slicing(&n);

    println!("s1: {s1}");
}

fn slicing(s: &str) -> &str {
    let bytes = s.as_bytes();
    for (i, &ch) in bytes.iter().enumerate() {
        if ch == b' ' {
            return &s[0..i];
        }
    }

    return &s[..];
}

fn change_string(s: &mut String, x: &str) {
    s.push_str(&x);
}

fn print_string(s: String) {
    println!("{s}");
}

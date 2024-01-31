fn main() {
    println!("Hello, world!");
    _printsomething("Ola, mundo!".to_string(), 10);

    let x = {
        let y = 10;
        y + 10 // expression, return the value of addtion
               // DO NOT USE SEMICOLON
    };

    println!("x: {x}");
    println!("sum: {}", _superfunctions(32, 80));
    println!("impar ou par: {}", _impar_ou_par(55));
    println!("raizQ: {}", _raiz_q(25));
    println!("labeledLoops: {}", _labeled_loops());


    let nome: [char; 5] = ['l', 'u', 'c', 'a', 's'];
    for i in nome { 
        println!("{i}");
    }

    for number in (0..4).rev() {
        println!("number: {number}");
    }
}

fn _printsomething(str: String, x: i32) {
    println!("{str}, {x}");
}

// return type é passado usando essa flecha
fn _superfunctions(x: i32, y: i32) -> i32 {
    // Rust retorna implicitamente a ultima expressão da função
    // assim, basta passar uma linha de codigo sem ponto e virgula.
    // (é possivel retornar com return _value também)
    x + y
}

fn _impar_ou_par(x: i32) -> String {
    let result = x / 2;
    
    // if é uma expression, então você pode usá-lo pra atribui valores
    // os valores dos dois braços do if DEVEM ser do mesmo tipo
    // note que os valores em cada braço do if são expressions,
    // pois assim o valor é retornado pra variavel
    let string = if result > 0 {"impar".to_string()} else {"par".to_string()};

    return string;
}

fn _raiz_q(x: i32) -> i32 {
    let mut counter = 0;
    loop {
        counter += 1;
        if counter * counter == x {
            break counter
        }
    }
}

// é possivel nomear loops para usar o break e o continue
// somente nos loops que você especificar
fn _labeled_loops() -> i32 {
    let mut result: i32 = 0;
    'loopExterno: loop {
        result += 1;
        'loopInterno: loop {
            result += 1;
            if result > 8 {
                break 'loopInterno;
            }
        }

        if result > 20 {
            break 'loopExterno;
        }
    } 

    return result;
}

fn main() {
    let x = 10;
    let x = x + 10;

    {
        let x = x * 2;
        println!("x value: {x}");
    }

    println!("x value: {x}");
    
    // variables declaration


    // Scalar types
    let _integer: i32   = 100; 
    let _float: f32   = 3.14;

    // Compoud types
    let _tuple: (i32, f64, u8) = (500, 3.14, 1);        
    let (_a, _b, _c) = _tuple; // descontruindo a tuple (extraindo valores)
   
    // descontruindo também
    let user = ("Lucas Santos", 20, 1.94);
    let _nome = user.0;
    let _idade = user.1;
    let _altura = user.2;

    let _dias = ["Segunta", "Terça", "Quarta", "Quinta", "Sexta", "Sábado", "Domingo"];

    let _meses: [String, 12] = ["January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"];

    let _num = [3; 5]; // cria um array de 5 elementos, todos com o valor 3.
    

}

fn maioridade(age: u8, gender: &str) -> bool {
	match age {
		0..=17 if gender == "masculino" => {println!("homem, menor de idade"); return false;},
		0..=17 if gender == "feminino" => {println!("mulher, menor de idade"); return false;},
		0..=17 => {println!("nao binario, menor de idade"); return false;},

		18.. if gender == "masculino" => {println!("homem, maior de idade"); return true;},
		18.. if gender == "feminino" => {println!("mulher, maior de idade"); return true;},
		18.. => {println!("nao binario, maior de idade"); return true;},
		// _ => println!("default!"), // default brach
	}
}

fn match_array() {
	let arr: [u32; 4] = [10, 20, 30, 40];
	match arr[0..=3] {
		[10, 20] => println!("10, 20"),
		[10, ..] => println!("10, .."),
		_ => println!("default"),
	};
}

fn main() {
    let age: u8 = 18;
    let gender = "masculino";

		match_array();
    println!("{}", maioridade(age, gender));
}

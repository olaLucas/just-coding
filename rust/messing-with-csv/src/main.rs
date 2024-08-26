mod csv;    

fn main() {
    let array: Box<Vec<csv::Aluno>> = csv::read_csv("inscricoes.csv"); 
    println!("{:#?}", array); 
}

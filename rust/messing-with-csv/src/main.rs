// where to get the datasets:
// https://www.datablist.com/learn/csv/download-sample-csv-files


mod cli;
mod tui;
mod spreadcheet;
use spreadcheet::SpreadSheet;

fn main() {
    let mut s = SpreadSheet::new();
    s.load("customers-100.csv");
    s.sort_by_first_name();
    println!("{}", s);
}

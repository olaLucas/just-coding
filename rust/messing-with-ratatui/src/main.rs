use ratatui as rat;

mod tui;

fn main() {
    tui::init().unwrap();
    let mut a = tui::App::new();
    let mut term = rat::Terminal::new(rat::backend::CrosstermBackend::new(std::io::stdout())).unwrap();
    let _ = a.run(&mut term);

    tui::restore().unwrap();
}

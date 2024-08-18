use std::io::stdout;
use std::time::Duration;

use ratatui::{
    backend::CrosstermBackend,
    crossterm::{
        terminal::{
            enable_raw_mode,
            disable_raw_mode,
            EnterAlternateScreen,
            LeaveAlternateScreen,
        },
        ExecutableCommand,
        event::{
            self,
            KeyCode,
            KeyEventKind,
        },
    },


    widgets::Paragraph,
    Terminal,
};

fn main() {
    stdout().execute(EnterAlternateScreen).unwrap();
    enable_raw_mode().unwrap();

    let mut term = Terminal::new(
        CrosstermBackend::new(stdout())
    ).unwrap();

    term.clear().unwrap();

    loop {
        term.draw(|frame| {
            frame.render_widget(
                Paragraph::new("Hello, world! (presss 'q' to quit)."),
                frame.area()
            )
        }).unwrap();

        if event::poll(Duration::from_millis(16)).unwrap() {
            if let event::Event::Key(key) = event::read().unwrap() {
                if key.kind == KeyEventKind::Press && key.code == KeyCode::Char('q') {
                    break;
                }
            }
        }
    }

    disable_raw_mode().unwrap();
    stdout().execute(LeaveAlternateScreen).unwrap();
}

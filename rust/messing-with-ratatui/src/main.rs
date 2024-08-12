use ratatui::{self as rat, widgets::Borders};
use rat::prelude::CrosstermBackend;

fn main() {
    let back = CrosstermBackend::new(std::io::stdout());
    let mut term = rat::Terminal::new(back).unwrap();
    
    let header = "First ratatui program";
    let text = "Hello, world!";

    let p = rat::widgets::Paragraph::new(text)
        .style(rat::style::Style::default().fg(rat::style::Color::Red))
        .block(rat::widgets::Block::default()
            .borders(Borders::all())
            .title(header)
            .border_type(ratatui::widgets::BorderType::Rounded)
        );

    let _ = term.draw(|f| f.render_widget(p, rat::layout::Rect::new(2, 2, header.len().try_into().unwrap(), header.len().try_into().unwrap())));
}

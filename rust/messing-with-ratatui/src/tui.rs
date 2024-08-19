use std::io;
use ratatui::{self as rat, style::Stylize};

pub struct App {
    counter: i8,
    exit: bool
}

impl App {
    
    pub fn new() -> App {
        App::default()
    }

    pub fn default() -> App {
        App { counter: 0, exit: false }
    }

    fn decrement_counter(&mut self) {
        self.counter = self.counter - 1;
    }

    fn increment_counter(&mut self) {
        self.counter = self.counter + 1;
    }

    fn exit(&mut self) {
        self.exit = true;
    }

    pub fn run(&mut self, terminal: &mut Tui) -> io::Result<()> {
        while !self.exit {
            terminal.draw(|frame| self.render_frame(frame))?;
            self.handle_events()?;
        }

        Ok(())
    }

    fn render_frame(&self, frame: &mut rat::Frame) {
        frame.render_widget(self, frame.area());
    }

    fn handle_events(&mut self) -> io::Result<()> {
        match rat::crossterm::event::read()? {
            rat::crossterm::event::Event::Key(k) if k.kind == rat::crossterm::event::KeyEventKind::Press => {
                self.handle_key_events(k)
            },

            _ => {}
        }

        Ok(()) 
    }

    fn handle_key_events(&mut self, k: rat::crossterm::event::KeyEvent) {
        match k.code {
            rat::crossterm::event::KeyCode::Char('q') => self.exit(),
            rat::crossterm::event::KeyCode::Left => self.decrement_counter(),
            rat::crossterm::event::KeyCode::Right => self.increment_counter(),
            _ => {},
        }
    }
}

impl rat::widgets::Widget for &App {
    fn render(self, area: ratatui::prelude::Rect, buf: &mut ratatui::prelude::Buffer) {
        let title = rat::widgets::block::Title::from(" Counting App ".bold());
        let instructions = rat::widgets::block::Title::from(rat::text::Line::from(vec![
            " Decrement ".into(),
            "<Left>".blue().bold(),
            " Increment ".into(),
            "<Right>".blue().bold(),
            " Quit ".into(),
            "<Q> ".blue().bold(),
        ]));

        let block = rat::widgets::Block::bordered()
            .title(title.alignment(rat::layout::Alignment::Center))
            .title(
                instructions
                    .alignment(rat::layout::Alignment::Center)
                    .position(rat::widgets::block::Position::Bottom))
            .border_set(rat::symbols::border::THICK);

        let center_text = rat::text::Text::from(vec![rat::text::Line::from(vec![
            "Value: ".into(),
            self.counter.to_string().yellow(),
        ])]);

        rat::widgets::Paragraph::new(center_text)
            .centered()
            .block(block)
            .render(area, buf);
    } 
}

pub type Tui = rat::Terminal<rat::backend::CrosstermBackend<io::Stdout>>;

pub fn init() -> io::Result<Tui> {
    rat::crossterm::execute!(io::stdout(), rat::crossterm::terminal::EnterAlternateScreen)?;
    rat::crossterm::terminal::enable_raw_mode()?;
    rat::Terminal::new(rat::backend::CrosstermBackend::new(io::stdout()))
}

pub fn restore() -> io::Result<()> {
    rat::crossterm::execute!(io::stdout(), rat::crossterm::terminal::LeaveAlternateScreen)?;
    rat::crossterm::terminal::disable_raw_mode()?;
    Ok(())
}

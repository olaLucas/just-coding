pub module song {
  struct song {
    title: String,
    album: String,
    album_number: u8,
    release_date: String,
    duration: String,
  }
  
  impl song {
    fn get_title(&Self) -> &str {
      &self.title[..]
    }
  }
}
use std::collections::HashMap;
use std::io::{ Error, ErrorKind };
use std::path::Path;
use std::fs::{ File, read_dir };

fn craw_directory(src: &Path) -> Result<(), Error> {
  if src.exists() {
    let mut stack: Vec<String> = Vec::new();
    let mut visited: Vec<String> = Vec::new(); // TODO

    let src = src.to_str().unwrap();
    stack.push(src.to_string());

    // TODO: add identation (like tree)
    // TODO return a hasmap with the directories
    // and its files

    while let Some(dir) = stack.pop() {
      for entry in read_dir(dir)? {
        
        let entry = entry?;
        let entry_path = entry.path();
        let entry_str = match entry_path.to_str() {
          Some(s) => s,
          None => continue,
        };


        if entry.path().is_dir() {
          
          stack.push(entry_str.to_string());
          println!("dir: {}", entry_str);

        } else {
          // println!("file: {}", entry_str);
        }
      }
    }  
  } else {
    return Err(Error::from(ErrorKind::NotFound));
  }

  Ok(())
}


fn main() {
  craw_directory(Path::new("/home/dio/git_repos/")).unwrap();
}
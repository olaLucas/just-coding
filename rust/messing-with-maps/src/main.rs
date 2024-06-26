use walkdir::WalkDir;
use std::path::Path;
use std::collections::HashMap;
use std::env;
use std::fs;
use std::io;

fn scan_dir_filename(path: &Path) -> Result <Option <Vec<String>>, io::Error> {
  let mut vec: Vec <String> = Vec::new();
  let entries = fs::read_dir(path)?;
  for entry in entries {
    vec.push( match entry {
      Ok(f) => match f.path().file_name() {
        Some(s) => s
          .to_str()
          .unwrap_or(&String::new())
          .to_string(),
        None => String::new(),
      },

      Err(e) => { eprintln!("error: {:#?}", e); String::new() },
    });
  }

  Ok(Some(vec))
}

fn scan_dir(path: &Path) -> Result <Option <Vec<String>>, io::Error> {
  let mut vec: Vec <String> = Vec::new();
  let entries = fs::read_dir(path)?;
  for entry in entries {
    vec.push(match entry {
      Ok(f) => match f.path().to_str() {
        Some(s) => String::from(s),
        None => String::new(),
      },

      Err(e) => { eprintln!("error: {:#?}", e); String::new() },
    });
  }

  Ok(Some(vec))
}

fn craw_dir(path: &Path) -> Result< Option <HashMap <String, Vec<String>>>, walkdir::Error> {
  let mut map: HashMap <String, Vec<String>> = HashMap::new();

  if path.exists() {
    for entry in WalkDir::new(path).into_iter().filter_map(|e| e.ok()) {
      
      if entry.path().is_dir() {
        let mut path: Vec<&Path> = entry
          .path()
          .ancestors()
          .collect();
        path.reverse();

        for dir in path {
          let path_str: &str = match dir.to_str() {
            Some(s) => s,
            None => &String::new(),
          };

          if !map.contains_key(path_str) {
            map.insert(path_str.to_string(), match scan_dir(&Path::new(path_str)) {
              Ok(s) => match s {
                Some(vec) => vec,
                None => Vec::new()
              },

              Err(e) => { eprintln!("error: {:#?}", e); Vec::new()}, 
            });

          } else {
            continue;
          }
        }
      }
    }
  }

  Ok(Some(map))
}

fn main() {
  let path = env::args().last().unwrap();
  match craw_dir(Path::new(&path)) {
    Ok(Some(map)) => println!("{:#?}", map),
    Ok(None) => println!("craw_dir returned None."),
    Err(e) => eprintln!("vish, deu erro: {:#?}", e),
  }
}
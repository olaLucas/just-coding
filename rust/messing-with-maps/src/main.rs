use walkdir::WalkDir;
use std::path::Path;
use std::collections::HashMap;
use std::env;
use std::fs;
use std::io;
use serde_json;

fn scan_dir_filename(path: &Path) -> Result <Option <Vec<String>>, io::Error> {
  let mut vec: Vec <String> = Vec::new();
  let entries = fs::read_dir(path)?;
  for entry in entries {
    vec.push( match entry {
      Ok(f) => f.path()
        .file_name()
        .map_or_else(String::new, 
          |s| s.to_str()
          .unwrap_or("")
          .to_string()),

      Err(e) => { eprintln!("error: {e:#?}"); String::new() },
    });
  }

  Ok(Some(vec))
}

fn scan_dir(path: &Path) -> Result <Option <Vec<String>>, io::Error> {
  let mut vec: Vec <String> = Vec::new();
  let entries = fs::read_dir(path)?;
  for entry in entries {
    vec.push(match entry {
      Ok(f) => f.path()
        .to_str()
        .map_or_else(String::new, String::from),

      Err(e) => { eprintln!("error: {e:#?}"); String::new() },
    });
  }

  Ok(Some(vec))
}

fn craw_dir(path: &Path) -> Result< Option <HashMap <String, Vec<String>>>, walkdir::Error> {
  let mut map: HashMap <String, Vec<String>> = HashMap::new();

  if path.exists() {
    for entry in WalkDir::new(path).into_iter().flatten() {
      if entry.path().is_dir() {
        let path: &Path = entry.path();
        let path_str: &str = path
          .to_str()
          .unwrap_or("");

        if !map.contains_key(path_str) {
          map.insert(path_str.to_string(), match scan_dir(Path::new(path_str)) {
            Ok(s) => s.unwrap_or_else(Vec::new),
            Err(e) => { eprintln!("error: {e:#?}"); Vec::new()}, 
          });
          
        } else {
          continue;
        }
      }
    }
  }

  Ok(Some(map))
}

fn write_file(file_path: &Path, map: &HashMap<String, Vec<String>>) -> Result<(), serde_json::Error> {

  let content = serde_json::to_string_pretty(&map).unwrap();
  fs::write(file_path, content.as_bytes())
    .expect("Error while trying to write content to output file.");

  Ok(())
}


fn main() {
  let arg = env::args().last().unwrap();
  match craw_dir(Path::new(&arg)) {
    Ok(Some(map)) => write_file(Path::new("output.json"), &map).unwrap(),
    Ok(None) => println!("craw_dir returned None."),
    Err(e) => eprintln!("vish, deu erro: {e:#?}"),
  }
}

use std::fs;
use std::io::{ Read, Error };
use std::path::Path;

fn open_file(_path: &str) -> Result<(fs::File, String), Error> {
  match fs::File::open(_path) {
    Ok(mut f) => {
      let mut content = String::new();
      match f.read_to_string(&mut content) {
        Ok(_) => return Ok((f, content)),
        Err(e) => return Err(e),
      };
    },

    Err(e) => return Err(e),
  };
}

fn scan_dir(_path: &Path) {
  let mut visited: Vec<String> = Vec::new();
  if _path.is_dir() {
    
    match fs::read_dir(_path) { // ReadDir
      
      Ok(entries) => {
        
        for entry in entries {
          
          match entry { // DirEntry
          

            Ok(dir) => {
                  
              let dir = dir.path();
              if dir.is_dir() {
                
                let entry_path = match dir.to_str() {
                  Some(s) => String::from(s),
                  None => panic!("scan_dir: empty entry.to_str()."),
                };

                if visited.contains(&entry_path) {
                  continue;
                
                } else {
   
                  visited.push(String::from(&entry_path));
                  println!("{:?}", entry_path);
                  scan_dir(&dir);
                }

              } else {
   
                continue;
              }
            },

            Err(e) => eprintln!("scan_dir: Result<DirEntry> unwrap error: {:?}", e),
            // TODO: Handle other errors with ErrorKind
          }
        }
      },

      Err(e) => eprintln!("scan_dir: Result<ReadDir> unwrap error: {:?}", e),
      // TODO: Handle other errors with ErrorKind
    };
  }
}

fn main() {
  let path = "/home/dio/git_repos/";
  scan_dir(Path::new(path));
}
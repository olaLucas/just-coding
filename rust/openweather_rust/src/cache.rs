use std::fs;
use std::path::Path; 
use std::process::exit;

pub fn read_cache(path: &Path) -> String {

    if !path.exists() { 
        eprintln!("error > cache file not found in {:#?}", path);
        exit(-1)
    }
    
    let content: String = match fs::read_to_string(path) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("ERROR cache::read_cache > failed to read cache file: {:#?}", e);
            exit(-1);
        }
    };

    return content;
}

pub fn write_cache(path: &Path, new_cache: String) {
    
    if !path.exists() {
        match fs::File::create(path) {
            Ok(_) => println!("Opening file: {}", path.to_str().unwrap()),
            Err(e) => {
                eprintln!("ERROR cache::write_cache > cache file does not exit {:#?}.", e);
                exit(-1);
            }
        };
    } 
    
    match fs::write(path, new_cache) {
        Ok(_) => println!("New cache wrote succefully."),
        Err(e) => {
            eprintln!("ERROR cache::write_cache > failed to write to file {:#?}", e);
            exit(-1);
        }
    };
}

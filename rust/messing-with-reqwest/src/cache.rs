use std::fs;
use std::path::Path;
use std::io::{Error, ErrorKind};

pub fn read(path: &Path) -> Result<serde_json::Value, Error> {
    let content = fs::read_to_string(path)?;

    return Ok(serde_json::from_str(&content)
        .expect("cache::read > Error while serializing JSON"));
}

pub fn write_geocoding(path: &Path, geo: serde_json::Value) -> Result<(), Error> {
   
    let home_file = Path::new("/home/dio/.config/weather/config.json");
    if !path.exists() { 
        eprintln!("file not found: {}", path.to_str().unwrap());
        return Err(Error::from(ErrorKind::NotFound));
    }
   
    match read(home_file) {
        Ok(mut cache) => {
            let cache = cache.as_object_mut()
                .expect("error while trying to map cache as mut object");
            
            cache.insert("geocoding".to_string(), geo)
                .expect("error while trying to insert geocoding in cache file.");
            
            let cache = serde_json::to_string_pretty(cache)?;
            fs::write(path, cache)?;
        },

        Err(e) => {
            eprintln!("error while trying to read cache: path -> {}  error -> {}", path.to_str().unwrap(), e);
            return Err(e);
        }
    }
    
    Ok(())
}

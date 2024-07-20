use std::{fs, io};
use std::path::Path; 

pub fn read_cache(path: &Path) -> Result<String, io::Error> {

    if !path.exists() { 
        eprintln!("error > cache file not found in {:#?}", path);
        return Err(io::Error::from(io::ErrorKind::NotFound));
    }
    
    let content: String = fs::read_to_string(path)?;
    

    Ok(content)
}

pub fn write_cache(path: &Path, new_cache: serde_json::Value) -> Result<(), io::Error> {
    
    if !path.exists() {
        _ = fs::File::create(path)?;
    } 
    
    let content: String = match serde_json::to_string_pretty(&new_cache) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("Error while trying to serialize new cache values: {:#?}", e);
            return Err(e.into());
        }
    };
    
    fs::write(path, content)?;
    Ok(())
}

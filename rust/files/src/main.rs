use std::fs::File;

fn open_file(_path: &str) -> File {
  let file = File::open(_path);
  let file = match file {
    Ok(file) => file,
    Err(error) => panic!("Error ({error}) while trying to open {_path} file."), 
  };

  return file;
}

fn main() {
    println!("{:?}", open_file("foo.rs"));
}

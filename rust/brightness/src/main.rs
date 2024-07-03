use std::fs;
use std::io::{ ErrorKind, Write, Result, Error };
use std::path::Path;
use clap::{ arg, value_parser, Arg, Command };

fn parse_terminal_args(arguments: &[Arg]) -> clap::ArgMatches {
    Command::new("chbacklight")
        .args(arguments)
        .about("Changes the brightness notebooks displays")
        .author("dio")
        .get_matches()
}

fn read_file(path: &Path) {
    if !path.exists() {
        eprintln!(
            "ERROR: NotFound\n{} dont exists.", 
            path.to_str().expect("failed to convert path to string")
        );
    } 
   
    match fs::read_to_string(path) {
        Ok(s) => println!("brightness value: {}", s),
        Err(e) => eprintln!(
            "ERROR:{}\nfailed to read the content of {}.", 
            e, path.to_str().expect("failed to convert path to string")
        ),
    }
}

fn write_file(path: &Path, new_value: u8) -> Result<()> {
    
    if !path.exists() {
        eprintln!("ERROR: {} does not exists.", path.to_str().expect("write_file: failed to conver Path to string."));
        return Err(Error::from(ErrorKind::NotFound));
    }

    let mut file = fs::OpenOptions::new()
        .read(true)
        .write(true)
        .create(true)
        .open(path)?;

    let new_value: [u8; 1] = [new_value];
    file.write_all(&new_value)?;

    Ok(())
}

fn main() {
   
    // the file that actually changes the brightness
    let sys_path = Path::new("/sys/class/backlight/amdgpu_bl1/brightness");

    // the file that i3status will see
    let home_path = Path::new("/home/dio/.config/i3status_brightness/brightness"); 

    let arguments: &[Arg] = &[
        arg!(set: -s --set <VALUE> "change the brightness to <VALUE>.")
            .value_parser(value_parser!(u8))
            .num_args(1),
        arg!(info: -i --info "return the brightness value.")
            .action(clap::ArgAction::SetTrue),
    ];

    let matches = parse_terminal_args(arguments);
    if let Some(arg) = matches.get_one::<u8>("set") {
        let new_value:u8 = *arg;
        
       match write_file(sys_path, new_value) {
            Ok(()) => match write_file(home_path, new_value) {
                Ok(()) => println!("brightness succefully changed."),
                Err(e) => eprintln!("an error ocurred while trying to write to {} file: {:#?}", 
                    home_path.to_str().expect("main: error while trying to convert Path to string."),
                    e, 
                ),
            },

            Err(e) => eprintln!("an error ocurred while trying to write to {} file: {:#?}", 
                sys_path.to_str().expect("main: error while trying to convert Path to string."),
                e, 
            ),
        } 
    }

    if matches.get_flag("info") {
        read_file(sys_path);
    }
} 

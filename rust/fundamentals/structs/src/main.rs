#[derive(Debug)] //let us print debug information
struct User {
    active  : bool,
    name    : String,
    email   : String,
    age     : u8,
}

#[derive(Debug)]
struct Rectangle {
    height  : u32,
    width   : u32
}

// defining an struct method
impl Rectangle { 
    fn area(&self) -> u32 { // first arg must be the struct caller instance
        self.height * self.width
    }
}

// tuple structs declaration
struct Color (i32, i32, i32);
struct AlwaysEqual; //unit structs (?)

fn main() {
    let lucas = build_user(
        String::from("Lucas Santos"),
        String::from("lsantos2003silva@gmail.com"),
        20
    );
    
    // an way to copy data from an structs instance to another
    let pietro = User {
        name : String::from("Pietro"),
        ..lucas
    };

    // print_user(&lucas); // strings from lucas was moved to pietro
    // print_user(&pietro);
    
    println!("{:?}", pietro);
    println!("{:#?}", pietro); // printing in debug mode, otherwise we'll have to provide an 
    // funtion to print it.

    // tuple structs variable declaration
    let _blue = Color(0, 0, 255);
    let _subject = AlwaysEqual;

    let scale = 100;
    let rec = Rectangle {
        width   : dbg!(30 * scale), // can also be used here, since it returns the ownership
        height  : 50
    };

    dbg!(&rec); // another way of printing debugging useful information

    print!("area: {}", rec.area());
}

fn print_user(user: &User) {
    println!("Active:   {}", user.active);
    println!("Name:     {}", user.name);
    println!("Email:    {}", user.email);
    println!("Age:      {}", user.age);
}

fn build_user(name: String, email: String, age: u8) -> User {
    User {
        active: true,
        name,
        email,
        age,
    }
}

struct Geocoding {
	city: String,
	country: String,
	state: String,
	lat: f32,
	lon: f32
}

struct User {
	appid: String,
	units: String,
}

// defining methods
impl Geocoding {

}

// defining methods
impl User {

}

fn build_geocoding(city: String, country: String, state: String, lat: f32, lon: f32) -> Geocoding {
	Geocoding {
		city,
		country,
		state,
		lat,
		lon, 
	}
}

fn build_user(appid: String, units: String) -> User {
	User {
		appid,
		units
	}
}

fn main() {

	let x = Some("Lucas");
	println!("{:?}", x);
}
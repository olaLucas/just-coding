// struct GeocodingData_t
// {
//     char * city;
//     char * country; /* ISO code */
//     char * state;
//     char * lon;
//     char * lat;
// };
// 
// struct APIData_t
// {   
//     struct GeocodingData_t geo;
//     char * appid;
//     char * units;
// };
// 
// struct currentWeather_t
// {
//     char * date;
//     char * name;
//     char * country;
//     char * weather_main;
//     char * weather_description;
//     char * sunset;
//     char * sunrise;
// 
//     float temp;
//     float feels_like;
//     float temp_min;
//     float temp_max;
//     float humidity;
// };

pub mod geocoding {
    pub struct Geocoding {
        city:       String,
        country:    String,
        state:      String,
        lon:        f32,
        lat:        f32,
    }
}

pub mod api {
    pub struct data {
        appid:  String,
        units:  String,
    } 
}

pub mod weather {
    pub struct Weather {
        date:                   String,
        name:                   String,
        country:                String,
        weather_main:           String,
        weather_description:    String,

        temp:                   f32,
        feels_like:             f32,
        temp_min:               f32,
        temp_max:               f32,
        humidity:               f32,
    }
}

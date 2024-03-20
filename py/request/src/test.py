user = {
        "appid":"ola",
        "units" : "metric",
        "geocoding" : {
            "city" : "São Paulo",
            "country" : "Brazil",
            "state" : "São Paulo",
            "lat" : 10.0000,
            "lon" : 20.0000
        }
    }

GEOCODING_API_ENDPOINT = "http://api.openweathermap.org/geo/1.0/direct?"
l = f'{GEOCODING_API_ENDPOINT}appid={user["appid"]}&'

print(l)
print(user)

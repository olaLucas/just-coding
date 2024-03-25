class geocodingClass:
    def __init__(self, city, country, lat=0.0, lon=0.0):
        self.city = city
        self.country = country
        self.lat = lat
        self.lon = lon

    def __str__(self):
        return f'city: {self.city}\n country: {self.country}\n lat: {self.lat}\n lon: {self.lon}\n'
    
    # SET Methods
    def setCity(self, city):
        self.city = city

    def setCountry(self, country):
        self.country = country

    def setLat(self, lat):
        self.lat = lat

    def setLon(self, lon):
        self.lon = lon

    # GET Methods
    def getCity(self):
        return self.city

    def getCountry(self):
        return self.country

    def getLat(self):
        return self.lat

    def getLon(self):
        return self.lon
    
    def extract(self):
        return {
            "name" : self.city,
            "country" : self.country,
            "lat" : self.lat,
            "lon" : self.lon
        }


class userClass:
    def __init__(self, appid, units="metric"):
        self.appid = appid
        self.units = units

    def __str__(self):
        return f'appid: {self.appid}\n units: {self.units}\n'

    # Set methods
    def setAppid(self, appid):
        self.appid = appid

    def setUnits(self, units):
        self.units = units


    # Get methods
    def getAppid(self):
        return self.appid

    def getUnits(self):
        return self.units
    
    def extract(self):
        return {
            "appid" : self.appid,
            "units" : self.units
        }     
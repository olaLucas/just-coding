class geocoding:
    def __init__(self, city, country, lat=0.0, lon=0.0):
        self.city = city
        self.country = country
        self.lat = lat
        self.lon = lon

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


class user:
    def __init__(self, appid, units="metric"):
        self.appid = appid
        self.units = units

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


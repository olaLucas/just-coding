from requests import get
import json
import sys
from datetime import datetime
import classes

FILE_PATH = "info.json"

def checkReponse(res):

    if res.get("cod") == 200:
        return 0
    
    elif res.get("cod") == 401:
        print("API Error!", end='\n')
        print(res.get("message"))
        return -1


def print_current_weather(info):

    weather = info.get("weather")[0]
    main = info.get("main")
    t = datetime.fromtimestamp(info.get("dt"))

    print(f'{info.get("name")}, {info.get("sys").get("country")}, {t}')
    print(f'Temp: {main.get("temp")}     | Feels: {main.get("feels_like")}')
    print(f'Temp Max: {main.get("temp_max")} | Temp Min: {main.get("temp_min")}')
    print(f'Weather: {weather.get("main")}, {weather.get("description")}')


def get_current_weather(appid, lat, lon, units):
    r = get(
        f'https://api.openweathermap.org/data/2.5/weather?appid={appid}&lat={lat}&lon={lon}&units={units}'
    )
    
    if checkReponse(eval(r.text)) == -1:
        print("Closing program...", end='\n')

    return dict(eval(r.text))


def get_geocoding(city, country, appid):
    r = get(
        f'http://api.openweathermap.org/geo/1.0/direct?q={city},{country}&appid={appid}'
    )
    
    if checkReponse(eval(r.text)[0]) == -1:
        print("Closing program...", end='\n')
    
    geo = dict(eval(r.text)[0])
    
    return classes.geocodingClass(
        geo.get("name"),
        geo.get("country"),
        geo.get("lat"),
        geo.get("lon")
    ) 
    

def check_terminal_args():
    args = dict()
    sys_len = len(sys.argv)

    if sys_len > 1:
        for i in range(1, sys_len):
            if sys.argv[i] == "--appid":
                args["appid"]= sys.argv[i+1]
                i += 1
            
            elif sys.argv[i] == "--city":
                args["city"] = sys.argv[i+1]
                i += 1

            elif sys.argv[i] == "--country":
                args["country"] = sys.argv[i+1]
                i += 1

            elif sys.argv[i] == "--units":
                args["units"] = sys.argv[i+1]
                i += 1

        user = classes.userClass(
            args.get("appid"),
            args.get("units")
        )

        geo = classes.geocodingClass(
            args.get ("city"),
            args.get("country")
        )

        return (user, geo)
    else:
        return (-1, -1)


def save_data(user, geo):
    file = open(FILE_PATH, 'w')
    if file.closed:
        return -1
    else: 
        file.write(json.dumps({
                        "appid" : user.getAppid(),
                        "units" : user.getUnits(),
                        "geocoding" : geo.extract()
                    }, indent=4)
                )

        file.close()

def read_data():
    file = open(FILE_PATH, 'r')
    if file.closed:
        print("Was not possible to find the file.", end='\n')

    dataUser = dict(json.load(file))
    dataGeo = dict(dataUser.get("geocoding"))

    args = classes.userClass(
        dataUser.get("appid"),
        dataUser.get("units")
    )

    geo = classes.geocodingClass(
        dataGeo.get("name"),
        dataGeo.get("country"),
        dataGeo.get("lat"),
        dataGeo.get("lon")
    )
    
    file.close()

    return (args, geo)

user, geo = check_terminal_args()
if user == -1 or geo == -1:
    user, geo = read_data()
    if user.getAppid() == "":
        print("No appid (API Key) was passed to the program. Impossible to continue.", end='\n')
    else:    
        weather = get_current_weather(
            user.getAppid(), 
            geo.getLat(), 
            geo.getLon(),
            user.getUnits()
        )

        print_current_weather(weather)

else:
    geo = get_geocoding(
        geo.getCity(),
        geo.getCountry(),
        user.getAppid()
    )

    weather = get_current_weather(
        user.getAppid(), 
        geo.getLat(), 
        geo.getLon(),
        user.getUnits()
    )

    print_current_weather(weather)
    save_data(user, geo)
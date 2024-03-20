import requests
import json
import sys

FILE_PATH = "info.json"


def get_current_weather(user):
    r = requests.get(
        "https://api.openweathermap.org/data/2.5/weather?"
    )
    
    # checar se não há erros

    print(r.text.strip())

    return dict(eval(r.text))


def get_geocoding(city, country, appid):
    r = requests.get(
        f'http://api.openweathermap.org/geo/1.0/direct?q={city},{country}&appid={appid}'
    )
    
    # checar se não há erros


    print(r.text, end='\n')
    return dict(eval(r.text)[0])
    


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

        return args
    else:
        print("none arguments were passed to the program.")
        return -1


def save_data(args, geo):
    file = open(FILE_PATH, 'w')
    if file.closed:
        return -1
    else: 
        file.write(json.dumps({
                        "appid" : args.get("appid"),
                        "units" : args.get("units"),
                        "geocoding" : geo
                    }, indent=4)
                )

        file.close()

def read_data():
    file = open(FILE_PATH, 'r')
    data = json.load(file)
    geo = dict(data.get("geocoding"))
    
    file.close()

    return (data, geo)


args = check_terminal_args()
if args == -1:
    args, geo = read_data()
else:
    geo = get_geocoding(
                args.get("city"),
                args.get("country"),
                args.get("appid")
            )

print(args, end='\n')
print(geo, end='\n')

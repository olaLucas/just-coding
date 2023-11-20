#if !defined(INCLUDES)
    #define INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <cjson/cJSON.h>

    #define STRING_SIZE 100
    #define BUFFER_SIZE 1024

#endif // INCLUDES

#include <time.h>
#include "../libs/request.h"

struct getData
{
    char * lon;
    char * lat;
    char * appid;
    char * units;
};

struct currentWeather
{
    char * date;
    char * name;
    char * country;
    char * weather_main;
    char * weather_description;

    float temp;
    float feels_like;
    float temp_min;
    float temp_max;
    float humidity;

    time_t sunset;
    time_t sunrise;
    time_t dt;
};


struct getData initGetData()
{
    struct getData gtD;
    gtD.appid = (char *)calloc(STRING_SIZE, sizeof(char));
    gtD.units = (char *)calloc(STRING_SIZE, sizeof(char));
    gtD.lat = 0;
    gtD.lon = 0;

    return gtD;
}


void print_getData(struct getData * gtD)
{
    printf("lon: %s\n", gtD->lon);
    printf("lat: %s\n", gtD->lat);
    printf("appid: %s\n", gtD->appid);
    printf("units: %s\n", gtD->units);
}

void print_CurrentWeather(struct currentWeather * cW)
{
    printf("date: %s", cW->date);
    printf("name: %s\n", cW->name);
    printf("weather_main: %s\n", cW->weather_main);
    printf("weather_description: %s\n", cW->weather_description);
    printf("temp: %f\n", cW->temp);
    printf("feels_like: %f\n", cW->feels_like);
    printf("temp_min: %f\n", cW->temp_min);
    printf("temp_max: %f\n", cW->temp_max);
    printf("humidity: %f\n", cW->humidity);
    printf("sunset: %ld\n", cW->sunset);
    printf("sunrise: %ld\n", cW->sunrise);
    printf("dt: %ld\n", cW->dt);
}


void deleteGetData(struct getData * gtD)
{
    if (gtD->appid != NULL)
        free(gtD->appid);
    if (gtD->units != NULL)
        free(gtD->units);
    gtD->lat = 0;
    gtD->lon = 0;
}


enum {info, response};
const char * JSON_FILE[] = {
    "info.json",
    "response.json"
};

const char * WEATHER_URI = "https://api.openweathermap.org/data/2.5/weather?";

enum {lat, lon, appid, units};
const char * json_keys[] = {
    "lat",
    "lon",
    "appid",
    "units"
};

const char * url_keys[] = {
    "lat=",
    "&lon=",
    "&appid=",
    "&units="
};

void getCurrentWeather()
{
    cJSON * json;
    struct getData gtD = initGetData();
    struct getRequest gtR = initGetRequest();    

    FILE * arq = fopen(JSON_FILE[info], "r");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening file.\n");
        deleteGetRequest(&gtR);
        deleteGetData(&gtD);

        exit(-1);
    }
    
    size_t buffer_size = file_size(arq);
    char * buffer = (char *)calloc(buffer_size, sizeof(char));

    fread(buffer, 1, sizeof(buffer), arq);
    json = cJSON_Parse(buffer);

    gtD.appid = getDynamicJSONString(json_keys[appid], buffer);
    gtD.units = getDynamicJSONString(json_keys[units], buffer);
    gtD.lat = getDynamicJSONString(json_keys[lat], buffer);
    gtD.lon = getDynamicJSONString(json_keys[lon], buffer);
    print_getData(&gtD);

    strcpy(gtR.body, WEATHER_URI);
    addKeyValueURL(&gtR, url_keys[lat], gtD.lat);
    addKeyValueURL(&gtR, url_keys[lon], gtD.lon);
    addKeyValueURL(&gtR, url_keys[appid], gtD.appid);
    addKeyValueURL(&gtR, url_keys[units], gtD.units);

    fclose(arq);

    getToJSON(gtR.body, JSON_FILE[response]);

    free(buffer);
    deleteGetRequest(&gtR);
    deleteGetData(&gtD);
    cJSON_Delete(json);
}

struct currentWeather readCurrentWeather()
{
    // interpreting the data
    cJSON * json; 
    cJSON * main;
    cJSON * weather;
    cJSON * sys;

    struct currentWeather cW;
    char * buffer;
    FILE * arq = fopen(JSON_FILE[response], "r");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening file.");
        return cW;
    }

    size_t buffer_size = file_size();
    if (buffer_size > 0)
    {
        buffer = (char *)calloc(buffer_size, sizeof(char));
    }
    else
    {
        fprintf(stderr, "buffer_size <= 0");
        exit(-1);
    }
    

    fread(buffer, 1, sizeof(buffer), arq);
    json = cJSON_Parse(buffer);

    main = cJSON_GetObjectItem(json, "main");
    sys = cJSON_GetObjectItem(json, "sys");
    
    // weather info comes into an array, so we need to get the first element
    // first to have access to the data
    weather = cJSON_GetObjectItem(json, "weather");
    weather = cJSON_GetArrayItem(weather, 0);    

    cW.name = cJSON_Print(cJSON_GetObjectItem(json, "name"));
    cW.country = cJSON_Print(cJSON_GetObjectItem(sys, "country"));
    cW.weather_main = cJSON_Print(cJSON_GetObjectItem(weather, "main"));
    cW.weather_description = cJSON_Print(cJSON_GetObjectItem(weather, "description"));

    cW.temp = atof(
        cJSON_Print(cJSON_GetObjectItem(main, "temp"))
    );

    cW.feels_like = atof(
        cJSON_Print(cJSON_GetObjectItem(main, "feels_like"))
    );

    cW.temp_min = atof(
        cJSON_Print(cJSON_GetObjectItem(main, "temp_min"))
    );

    cW.temp_max = atof(
        cJSON_Print(cJSON_GetObjectItem(main, "temp_max"))
    );


    cW.dt = atoll(
        cJSON_Print(cJSON_GetObjectItem(json, "dt"))
    );

    cW.sunset = atoll(
        cJSON_Print(cJSON_GetObjectItem(sys, "sunset"))
    );

    cW.sunrise = atoll(
        cJSON_Print(cJSON_GetObjectItem(sys, "sunrise"))
    );
    

    cW.date = ctime(&cW.dt);

    free(buffer);
    cJSON_Delete(json);
    fclose(arq);
    return cW;
}

int main(void)
{  
    


    return 0;
}
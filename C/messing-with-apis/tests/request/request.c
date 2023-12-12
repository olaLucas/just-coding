#if !defined(INCLUDES)
    #define INCLUDES

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <curl/curl.h>
    #include <cjson/cJSON.h>

#endif // INCLUDES

/*
    to compile: 
    gcc request.c -o request -g -Wall $(curl-config --libs --cflags) $(pkg-config libcjson --libs --cflags)
*/

#define BUFFER_SIZE 1024

const int FILE_FLAG = 0;
const int JSON_FLAG = 1;
const int STRING_FLAG = 2;
const int STRING_SIZE = 200;
// const int BUFFER_SIZE = 1024;
const char * TOKEN_CHAR = "\"";


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


struct getData
{
    char * lon;
    char * lat;
    char * appid;
    char * units;
};

struct getRequest
{
    char * body;
    size_t bodySize;
};

struct fileStruct
{
    FILE * fp;
    char * fileName;
    char * mode;
};

struct response
{
    char * data;
    size_t size;
};

typedef struct fileStruct fileStruct;
typedef struct getRequest getRequest;
typedef struct getData getData;
typedef struct response responseStruct;

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

void deleteGetData(struct getData * gtD)
{
    if (gtD->appid != NULL)
        free(gtD->appid);
    if (gtD->units != NULL)
        free(gtD->units);
    gtD->lat = 0;
    gtD->lon = 0;
}


struct getRequest initGetRequest()
{
    struct getRequest x;
    x.body = (char *)calloc(STRING_SIZE, sizeof(char));
    x.bodySize = STRING_SIZE * sizeof(char);
    return x;
}

void deleteGetRequest(struct getRequest * x)
{
    if (x->body != NULL)
        free(x->body);
    x->bodySize = 0;
}

void print_getRequest(struct getRequest * x)
{
    printf("body: %s\n", x->body);
    printf("body size: %ld\n", x->bodySize);
}


fileStruct initFileStruct(const char * FILE_NAME, const char * mode)
{
    fileStruct fl = {NULL, "", ""};
    if ((fl.fp = fopen(FILE_NAME, mode)) == NULL)
    {
        fprintf(stderr, "Error while opening the file.");
        exit(-1);
    }

    fl.fileName = (char *)calloc(strlen(FILE_NAME) + 1, sizeof(char));
    memcpy(fl.fileName, FILE_NAME, strlen(FILE_NAME) + 1);

    fl.mode = mode;
    return fl;
}

void deleteFileStruct(const fileStruct * fl)
{
    if (fl->fp != NULL) 
    {
        fclose(fl->fp);
    } 

    if (fl->fileName != NULL)
    {
        free(fl->fileName);
    }
}


struct response initResponse()
{
    struct response res;
    res.data = (char *)calloc(STRING_SIZE, sizeof(char));
    res.size = STRING_SIZE * sizeof(char);
    return res;
}

void print_response(struct response * res)
{
    printf("data: %s\n", res->data);
    printf("data size: %ld\n", res->size);
}

void deleteResponse(struct response * res)
{
    if (res->data != NULL)
        free(res->data);

    res->size = 0;
} 

/* 
    get the data from API response to a string
*/
size_t getResponseToString(void * data, size_t size, size_t nmeb, void * clientp)
{
    struct response * res = (struct response *)clientp;
    size_t realsize = size * nmeb;

    printf("realsize = %ld\n", realsize);
    printf("res.size = %ld\n\n", res->size);

    // alocando espaço para os novos caracteres
    char * string = (char *)realloc(res->data, res->size + realsize + 1);
    if (string == NULL)
    {
        puts("Out of memory!\n");
        return 0;
    }

    // atualizando o ponteiro para a nova string
    res->data = string;

    // copiando os dados recebidos em data para a response string
    strcat(res->data, data);

    // atualizando o tamanho da response string
    res->size += realsize;

    return realsize;
}

// get the data from API response to an file
size_t getResponseToFile(void * data, size_t size, size_t nmeb, void * clientp)
{
    size_t realsize = (size * nmeb);
    FILE * arq = (FILE *)clientp;

    if (arq == NULL)
    {   

        fprintf(stderr, "Error while opening file.");
        return 0;
    }
    else
    {
        puts("Writing data...");
        fwrite(data, size, realsize, arq);
    }
    
    return realsize;
}


/* 
    Extract an dynamic allocate an string from an JSON
*/
char * getDynamicJSONString(const char key[], const char * json_input)
{
    cJSON * json;
    char * valueFormated;
    char STRING_BUFFER[BUFFER_SIZE] = "";

    json = cJSON_Parse(json_input);
    
    printf("%s\n", cJSON_Print(cJSON_GetObjectItem(json, key)));
    strcpy(STRING_BUFFER, cJSON_Print(cJSON_GetObjectItem(json, key)));
    valueFormated = strtok(STRING_BUFFER, TOKEN_CHAR);

    if (valueFormated == NULL)
    {
        printf("%s: NULL\n", key);
        return NULL;
    }
    else
    {
        char * newString = (char *)calloc(strlen(valueFormated), sizeof(char));
        if (newString == NULL)
        {
            fprintf(stderr, "Out of memory!");
            return NULL;
        }
        else
        {
            strcpy(newString, valueFormated);
            return newString;
        }
    }
}


void getToFile(const char URL[], const fileStruct * fl)
{
    CURL * handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, URL);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getResponseToFile);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, fl->fp);

    CURLcode result = curl_easy_perform(handle);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return;
    }

    fflush(fl->fp);
    curl_easy_cleanup(handle);
}

void getToJSONFile(const char URL[], const fileStruct * fl)
{
    cJSON * json;
    struct response res = initResponse();

    CURL * handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, URL);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getResponseToString);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&res);

    CURLcode result = curl_easy_perform(handle);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return;
    }

    json = cJSON_Parse(res.data);
    fprintf(fl->fp, cJSON_Print(json));

    deleteResponse(&res);
    cJSON_Delete(json);
    curl_easy_cleanup(handle);
    fflush(fl->fp);
}

void getToString(const char URL[], struct response * res)
{
    CURL * handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, URL);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getResponseToString);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, res);

    CURLcode result = curl_easy_perform(handle);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return;
    }

    curl_easy_cleanup(handle);
}


void addKeyValueURL(struct getRequest * gt, const char key[], const char value[])
{
    size_t newSize = (strlen(key) + strlen(value) + 1);
    char buffer[newSize];
    strcpy(buffer, "");

    char * newDest = (char *)realloc(gt->body, (gt->bodySize + newSize));
    if (newDest == NULL)
    {
        fprintf(stderr, "Out of memory!");
        return;
    }

    gt->bodySize += newSize;
    gt->body = newDest;    
    strcat(buffer, key);
    strcat(buffer, value);
    strcat(gt->body, buffer);
}


size_t file_size(FILE * arq)
{
    if (arq == NULL)
    {
        fprintf(stderr, "File pointer == NULL");
        return -1;
    }

    size_t size = 0;
    fseek(arq, SEEK_SET, SEEK_END);
    size = ftell(arq); rewind(arq);

    return size;
}


void GETRequest(const char URL[], void * output, const int flag)
{
    if (FILE_FLAG == flag || JSON_FLAG == flag || STRING_FLAG == flag)
    {
        CURL * handle = curl_easy_init();
        curl_easy_setopt(handle, CURLOPT_URL, URL);

        if (FILE_FLAG == flag || JSON_FLAG == flag) // checking for files
        {
            fileStruct * fl = (fileStruct *)output;
            if (fl->fp == NULL)
            {
                fprintf(stderr, "File was not initialized.\n\n");
                if (fl->fileName != NULL)
                {
                    printf("Trying to open the file.\n\n");
                    FILE * fileTemp = fopen(fl->fileName, fl->mode);
                    if (fileTemp == NULL)
                    {
                        fprintf(stderr, "Was not possible to open the file.\n\n");
                        exit(-1);
                    }
                }
                else
                {
                    fprintf(stderr, "None file name was provided.\n\n");
                    exit(-1);
                }
            }
            else if (strcmp(fl->mode, "w") == 0 || strcmp(fl->mode, "a") == 0)
            {
                if (FILE_FLAG == flag) {
                    getToFile(URL, fl);
                }
                else if (JSON_FLAG == flag) {
                    getToJSONFile(URL, fl);
                }               
            }
            else
            {
                fprintf(stderr, "Could not write in the file (might be opened in readmode)\n\n.");
                fprintf(stderr, "fl->mode value: %s\n\n", fl->mode);
                return;
            }
        }
        else if (STRING_FLAG == flag) {
            getToString(URL, (struct response *)output);
        }
    }
    else // wrong flag
    {
        fprintf(stderr, "Invalid flag was passed to the function: %d \n\n", flag);
        exit(-1);
    }
}


void getCurrentWeather()
{
    cJSON * json;
    struct getData gtD = initGetData();
    struct getRequest gtR = initGetRequest();    

    fileStruct jsonRESPONSE = initFileStruct(JSON_FILE[response], "w");
    fileStruct jsonINFO = initFileStruct(JSON_FILE[info], "r");
    if (jsonINFO.fp == NULL || jsonRESPONSE.fp == NULL)
    {
        if (!jsonINFO.fp)
        {
            fprintf(stderr, "Error while opening file: %s\n", JSON_FILE[info]);
        }
        else if (!jsonRESPONSE.fp)
        {
            fprintf(stderr, "Error while opening file: %s\n", JSON_FILE[response]);
        }
        
        deleteGetRequest(&gtR);
        deleteGetData(&gtD);

        exit(-1);
    }
    
    size_t buffer_size = file_size(jsonINFO.fp);
    char * buffer = (char *)calloc(buffer_size, sizeof(char));

    fread(buffer, 1, buffer_size, jsonINFO.fp);
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

    deleteFileStruct(&jsonINFO);

    GETRequest(gtR.body, (void *)&jsonRESPONSE, JSON_FLAG);

    free(buffer);
    deleteFileStruct(&jsonRESPONSE);
    deleteGetRequest(&gtR);
    deleteGetData(&gtD);
    cJSON_Delete(json);
}


int main(void)
{
    // fileStruct fl = initFileStruct("response.json", "w");
    // GETRequest("www.google.com", (void *)&fl, FILE_FLAG);

    // responseStruct res = initResponse();
    // GETRequest("https://www.google.com/", (void *)&res, STRING_FLAG);

    getCurrentWeather();

    // deleteResponse(&res);
    return 0;
}
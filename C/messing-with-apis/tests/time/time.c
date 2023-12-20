#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

// gcc time.c -o time -I/usr/include/cjson -lcjson

struct city
{
    double lat;
    double lon;
    char * name;
    char * country;
    char * state;
};

// determines the size of the file
size_t file_size(FILE *arq)
{
    if (arq == NULL)
    {
        fprintf(stderr, "File pointer == NULL");
        return -1;
    }

    size_t size = 0;
    fseek(arq, SEEK_SET, SEEK_END);
    size = ftell(arq);
    rewind(arq);

    return size;
}

int checkJSON()
{
    cJSON *json;
    struct city ct;

    FILE *arq = fopen("city.json", "r");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening the file.");
        return -1;
    }

    size_t buffer_size = file_size(arq);
    char * buffer = (char *)calloc(buffer_size, sizeof(char));

    fread(buffer, 1, buffer_size, arq);
    json = cJSON_Parse(buffer);

    // the data comes inside an array
    cJSON *object = cJSON_GetArrayItem(json, 0);
    
    ct.name = strtok(
        cJSON_Print(cJSON_GetObjectItem(object, "name")), "\""
    );

    ct.country = strtok(
        cJSON_Print(cJSON_GetObjectItem(object, "country")), "\""
    );

    ct.state = strtok(
        cJSON_Print(cJSON_GetObjectItem(object, "state")), "\""
    );

    ct.lat = atof(
        cJSON_Print(cJSON_GetObjectItem(object, "lat"))
    );

    ct.lon = atof(
        cJSON_Print(cJSON_GetObjectItem(object, "lon"))
    );

    printf("name: %s\n", ct.name);
    printf("state: %s\n", ct.state);
    printf("country: %s\n", ct.country);
    printf("lat: %lf\n", ct.lat);
    printf("lon: %lf\n", ct.lon);

    free(buffer);
    cJSON_Delete(json);
    fclose(arq);
}

int main(void)
{
    checkJSON();
    return 0;
}

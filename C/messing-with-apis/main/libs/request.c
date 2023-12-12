#if !defined(INCLUDES)
#define INCLUDES

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    #include <cjson/cJSON.h>

    #define STRING_SIZE 200
    #define BUFFER_SIZE 1024
    #define TOKEN_CHAR "\""

#endif // INCLUDES

struct postRequest
{
    size_t header_size;
    size_t body_size;
    char * headers;
    char * body;
};

struct response
{
    char * data;
    size_t size;
};

struct getRequest
{
    char * body;
    size_t bodySize;
};


struct response initResponse()
{
    struct response res;
    res.data = (char *)calloc(STRING_SIZE, sizeof(char));
    res.size = STRING_SIZE * sizeof(char);
    return res;
}

struct postRequest initPOST()
{
    struct postRequest x;
    x.body = (char *)calloc(STRING_SIZE, sizeof(char));
    x.body_size = STRING_SIZE;
    x.headers = (char *)calloc(STRING_SIZE, sizeof(char));
    x.header_size = STRING_SIZE;
    return x;
}

struct getRequest initGetRequest()
{
    struct getRequest x;
    x.body = (char *)calloc(STRING_SIZE, sizeof(char));
    x.bodySize = STRING_SIZE * sizeof(char);
    return x;
}


void print_response(struct response * res)
{
    printf("data: %s\n", res->data);
    printf("data size: %ld\n", res->size);
}

void print_getRequest(struct getRequest * x)
{
    printf("body: %s\n", x->body);
    printf("body size: %ld\n", x->bodySize);
}


void deleteResponse(struct response * res)
{
    if (res->data != NULL)
        free(res->data);

    res->size = 0;
}

void deleteGetRequest(struct getRequest * x)
{
    if (x->body != NULL)
        free(x->body);
    x->bodySize = 0;
}


// get the data from API response to string
size_t getResponseToString(void * data, size_t size, size_t nmeb, void * clientp)
{
    struct response * res = (struct response *)clientp;
    size_t realsize = size * nmeb;

    // alocando espaço para os novos caracteres
    char * string = realloc(res->data, res->size + realsize + 1);
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

// extract, format and dynamic allocate an string from an JSON file 
char * getDynamicJSONString(const char key[], const char * json_input)
{
    cJSON * json;
    char * valueFormated;
    char STRING_BUFFER[BUFFER_SIZE] = "";

    json = cJSON_Parse(json_input);
    
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

// make an post request
char * postToString(const char URL[], const char body[], const char headers[])
{
    struct response res = initResponse();

    CURL * handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, URL);
    curl_easy_setopt(handle, CURLOPT_POST, 1L); // 1L == x-www-form-urlencoded
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, body);

    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getResponseToString);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)&res);

    CURLcode result = curl_easy_perform(handle);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return NULL;
    }
    else
    {
        printf("Token obtained: %s\n", res.data);
        return res.data;
    }
}

// make an get request


void getToFile(const char URL[], const char FILE_NAME[])
{
    FILE * arq = fopen(FILE_NAME, "w");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening the file.");
        return;
    }

    CURL * handle = curl_easy_init();
    curl_easy_setopt(handle, CURLOPT_URL, URL);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, getResponseToFile);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, arq);

    CURLcode result = curl_easy_perform(handle);
    if (result != CURLE_OK)
    {
        fprintf(stderr, "Error: %s\n", curl_easy_strerror(result));
        return;
    }

    fclose(arq);
    curl_easy_cleanup(handle);
}

void getToJSON(const char URL[], const char FILE_NAME[])
{
    cJSON * json;
    struct response res = initResponse();
    FILE * arq = fopen(FILE_NAME, "w");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening the file.");
        return;
    }

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
    fprintf(arq, cJSON_Print(json));

    deleteResponse(&res);
    cJSON_Delete(json);
    curl_easy_cleanup(handle);
    fclose(arq);
}

// add key value to an get URL
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

void addKeyValuePairToHTTPBody(struct postRequest * pos, const char * key, const char * value)
{
    size_t newSize = (strlen(key) + strlen(value) + 1);
    char buffer[newSize];
    strcpy(buffer, "");

    char * newDest = (char *)realloc(pos->body, (pos->body_size + newSize));
    if (newDest == NULL)
    {
        fprintf(stderr, "Out of memory!");
        return;
    }

    pos->body_size += newSize;
    pos->body = newDest;
    strcat(buffer, key);
    strcat(buffer, value);
    strcat(pos->body, buffer);
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
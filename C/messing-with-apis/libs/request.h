#if !defined(INCLUDES)
#define INCLUDES

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <curl/curl.h>
    #include <cjson/cJSON.h>

    #define STRING_SIZE 200
    #define BUFFER_SIZE 1024

#endif // INCLUDES

struct client_credentials
{
    char * content_type;
    char * grant_type;
    char * client_id;
    char * client_secret;
};

struct response
{
    char * data;
    size_t size;
};

struct postRequest
{
    size_t header_size;
    size_t body_size;
    char * headers;
    char * body;
};

struct token
{
    char * access_token;
    char * token_type;
    size_t expires_in;
};

struct getRequest
{
    char * body;
    size_t bodySize;
};

struct client_credentials initClient();
struct post initPOST();
struct response initResponse();
struct token initToken();
struct getRequest initGetRequest();

void print_credentials(struct client_credentials * clt);
void print_token(struct token * tk);
void print_post(struct post * pos);
void print_response(struct response * res);
void print_getRequest(struct getRequest * gt);

void deleteClient(struct client_credentials * clt);
void deletePOST(struct post * htp);
void deleteResponse(struct response * res);
void deleteToken(struct token * tk);
void deleteGetRequest(struct getRequest * gt);

size_t getResponse(void *data, size_t size, size_t nmeb, void *clientp);
char * getDynamicJSONString(const char key[], const char * json_input);
char * postToString(const char URL[], const char body[], const char headers[]);
void postToFile(const char URL[], const char body[], const char headers[], const char FILE_NAME[]);
char * getToString(const char URL[]);
void getToFile(const char URL[], const char FILE_NAME[]);
void getToJSON(const char URL[], const char FILE_NAME[]);
void addKeyValueURL(struct getRequest * gt, const char key[], const char value[]);
void addKeyValuePairToHTTPBody(struct post * pos, const char * key, const char * value);
size_t file_size(FILE * arq);
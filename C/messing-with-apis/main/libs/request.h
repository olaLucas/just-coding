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

struct fileStruct
{
    FILE * fp;
    char * fileName;
    char * mode;
};


typedef struct fileStruct fileStruct;
typedef struct getRequest getRequest;
typedef struct getData getData;
typedef struct response responseStruct;


extern struct client_credentials initClient();
extern struct post initPOST();
extern struct response initResponse();
extern struct token initToken();
extern struct getRequest initGetRequest();

extern void print_credentials(struct client_credentials * clt);
extern void print_token(struct token * tk);
extern void print_post(struct post * pos);
extern void print_response(struct response * res);
extern void print_getRequest(struct getRequest * gt);

extern void deleteClient(struct client_credentials * clt);
extern void deletePOST(struct post * htp);
extern void deleteResponse(struct response * res);
extern void deleteToken(struct token * tk);
extern void deleteGetRequest(struct getRequest * gt);


extern char * getDynamicJSONString(const char key[], const char * json_input);
extern char * postToString(const char URL[], const char body[], const char headers[]);
extern void postToFile(const char URL[], const char body[], const char headers[], const char FILE_NAME[]);
extern void getToString(const char URL[], struct response * res);
extern void getToFile(const char URL[], const fileStruct * fl);
extern void getToJSONFile(const char URL[], const char FILE_NAME[]);
extern char * makeURL(const char strArg[], ...);
extern void GETRequest(const char URL[], void * output, const int flag);
extern size_t file_size(FILE * arq);
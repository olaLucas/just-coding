#if !defined(STD_INCLUDES)
    #define STD_INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define STRING_SIZE 300
    #define BUFFER_SIZE 1024
    #define TOKEN_CHAR "\""

#endif // STD_INCLUDES

#if !defined(CJSON_INCLUDE)
#define CJSON_INCLUDE

    #include <cjson/cJSON.h>

#endif // CJSON_INCLUDE

extern const int FILE_FLAG;
extern const int JSON_FLAG;
extern const int STRING_FLAG;

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

struct string
{
    char * str;
    size_t length;
    size_t max_size;
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


/*  
    INIT Functions
*/
extern struct fileStruct initFileStruct(const char * FILE_NAME, const char * mode);
extern struct postRequest initPOST();
extern struct response initResponse();
extern struct string initSTRING(const size_t size);
extern struct getRequest initGetRequest();


/* 
    PRINT Functions
*/
extern void print_response(struct response * res);
extern void print_getRequest(struct getRequest * gt);


/*
    DELETE Functions
*/
extern void deletePOST(struct postRequest * htp);
extern void deleteResponse(struct response * res);
extern void deleteGetRequest(struct getRequest * gt);
extern void deleteSTRING(struct string * buf);
extern void deleteFileStruct(const struct fileStruct * fl);


/* 
    POST methods
*/
extern char * postToString(const char URL[], const char body[], const char headers[]);


/* 
    Like printf(), you pass the basic url with the type identifiers where it should be replaced by the respective variable passed to the function.
*/
extern char * makeURL(const char strArg[], ...);

/* 
    wrapper of the GET methods. Pass the URL, the type of output ((void *)&fileStruct, (void *)&response) and the flag (JSON, FILE, STRING) 
*/
extern void GETRequest(const char URL[], void * output, const int flag);

/* 
    str functions
*/

extern void strcln(char str[]);

/* 
    get the size of an file
*/
extern size_t file_size(FILE * arq);
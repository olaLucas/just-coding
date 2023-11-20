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

#include "../libs/request.h"

// https://developer.spotify.com/documentation/web-api/concepts/authorization
// https://developer.spotify.com/documentation/web-api/tutorials/code-flow

struct client_credentials
{
    char * content_type;
    char * grant_type;
    char * client_id;
    char * client_secret;
};

struct token
{
    char * access_token;
    char * token_type;
    size_t expires_in;
};


const char * CLIENT_FILE_NAME = "client.json";

enum {GRANT, ID, SECRET};
const char * json_keys[] = {
    "grant_type",
    "client_id",
    "client_secret"
};

const char * post_keys[] = {
    "grant_type=",
    "&client_id=",
    "&client_secret="
};

enum {TK_ACCESS, TK_TYPE, TK_EXPIRE};
const char * token_keys[] = {
    "access_token",
    "token_type",
    "expires_in"
};

enum {TOKEN_URL};
const char * urls[] = {
    "https://accounts.spotify.com/api/token"
};


struct client_credentials initClient()
{
    struct client_credentials clt;
    clt.grant_type = (char *)calloc(STRING_SIZE, sizeof(char));
    clt.client_id = (char *)calloc(STRING_SIZE, sizeof(char));
    clt.client_secret = (char *)calloc(STRING_SIZE, sizeof(char));
    // clt.content_type = (char *)calloc(STRING_SIZE, sizeof(char)); // not used by now
    return clt;
}

struct token initToken()
{
    struct token tk;
    tk.access_token = (char *)calloc(STRING_SIZE, sizeof(char));
    tk.token_type = (char *)calloc(STRING_SIZE, sizeof(char));
    tk.expires_in = -1;
    return tk;
}


void print_credentials(struct client_credentials * clt)
{
    printf("grant_type: %s\n", clt->grant_type);
    printf("client_id: %s\n", clt->client_id);
    printf("client_secret: %s\n", clt->client_secret);
}

void print_token(struct token * tk)
{
    printf("access_token: %s\n", tk->access_token);
    printf("token_type: %s\n", tk->token_type);
    printf("expires_in: %ld\n", tk->expires_in);
}


void deleteClient(struct client_credentials * clt)
{
    if (clt->grant_type != NULL)
        free(clt->grant_type);
    
    if (clt->client_id != NULL)
        free(clt->client_id);

    if (clt->client_secret != NULL)
        free(clt->client_secret);
}

void deleteToken(struct token * tk)
{
    if (tk->access_token != NULL)
        free(tk->access_token);
    if (tk->token_type != NULL)
        free(tk->token_type);
    tk->expires_in = 0;
}


int main(void)
{   
    cJSON * client_json;
    char file_buffer[BUFFER_SIZE] = "";
    FILE * arq = fopen(CLIENT_FILE_NAME, "r");
    if (arq == NULL)
    {
        fprintf(stderr, "Error while opening json file.");
        exit(-1);
    }
    
    fread(file_buffer, 1, sizeof(file_buffer), arq);

    client_json = cJSON_Parse(file_buffer);

    struct client_credentials clt = initClient();
    struct post pos = initPOST();
    struct token tk = initToken();

    // get the data from client.json into the client
    clt.grant_type = getDynamicJSONString(json_keys[GRANT], client_json);
    clt.client_id = getDynamicJSONString(json_keys[ID], client_json);
    clt.client_secret = getDynamicJSONString(json_keys[SECRET], client_json);
    print_credentials(&clt);

    // adding the pairs to make the body of the
    addKeyValuePairToHTTPBody(&pos, post_keys[GRANT], clt.grant_type);
    addKeyValuePairToHTTPBody(&pos, post_keys[ID], clt.client_id);
    addKeyValuePairToHTTPBody(&pos, post_keys[SECRET], clt.client_secret);
    print_post(&pos);

    char * response = post(urls[TOKEN_URL], pos.body, pos.headers);

    tk.access_token = getDynamicJSONString(token_keys[TK_ACCESS], response);
    tk.token_type = getDynamicJSONString(token_keys[TK_TYPE], response);

    // for size_t values doenst need dynamic allocation
    tk.expires_in = atol(cJSON_Print(cJSON_GetObjectItem(response, token_keys[TK_EXPIRE])));
    print_token(&tk);

    deleteToken(&tk);
    deletePOST(&pos);
    deleteClient(&clt);
    return 0;
}
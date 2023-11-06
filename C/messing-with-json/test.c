#include <stdio.h>
#include <stdlib.h>
#include <cjson/cJSON.h>

#define FILE_NAME "fileTest.json"

typedef struct pessoa
{
    char * nome;
    unsigned int idade;
    float altura;
} pessoa;

void print_pessoa(pessoa * p)
{
    printf("Nome: %s\n", p->nome);
    printf("Idade: %d\n", p->idade);
    printf("Altura: %f\n", p->altura);
}

void create_JSON(pessoa x[], unsigned int array_size)
{
    FILE * arq = fopen(FILE_NAME, "w");
    if (arq == NULL)
    {
        puts("File opening failure.");
        exit(-1);
    }

    cJSON * JSON = NULL;
    cJSON * JSONarray = NULL;
    cJSON * JSONpessoa = NULL;
    
    JSON = cJSON_CreateObject();
    if (JSON == NULL)
    {
        puts("Error while creating JSON.");
        exit(-1);
    }

    JSONarray = cJSON_CreateArray();
    if (JSONarray == NULL)
    {
        puts("Error while creating array.");
        exit(-1);
    }

    cJSON_AddItemToObject(JSON, "pessoas", JSONarray);

    for (int i = 0; i < array_size; i++)
    {
        JSONpessoa = cJSON_CreateObject();
        if (JSONpessoa == NULL)
        {
            puts("Error while creating array.");
            exit(-1);
        }

        if (cJSON_AddStringToObject(JSONpessoa, "nome", x[i].nome) == NULL) {goto end;}
        if (cJSON_AddNumberToObject(JSONpessoa, "idade", x[i].idade) == NULL) {goto end;}
        if (cJSON_AddNumberToObject(JSONpessoa, "altura", x[i].altura) == NULL) {goto end;}
        
        cJSON_AddItemToArray(JSONarray, JSONpessoa);
    }

    char * string = cJSON_Print(JSON);
    fputs(string, arq);
    
    end:
    cJSON_Delete(JSON);
    // cJSON_Delete(JSONarray);
    // cJSON_Delete(JSONpessoa);

    fclose(arq);
}

pessoa * reading_json(unsigned int array_size)
{
    pessoa * x = (pessoa *)malloc(sizeof(pessoa) * array_size);
    FILE * arq = fopen(FILE_NAME, "r");
    if (arq == NULL)
    {
        puts("File opening failure.");
        exit(-1);
    }

    char buffer[1024];
    fread(buffer, 1, sizeof(buffer), arq);
    
    cJSON * JSON = cJSON_Parse(buffer);
    cJSON * JSONPessoa = cJSON_GetObjectItem(JSON, "pessoas");
    
    unsigned int i = 0;
    cJSON * object = NULL;
    cJSON_ArrayForEach(object, JSONPessoa)
    {
        cJSON * JSONnome = cJSON_GetObjectItem(object, "nome");
        cJSON * JSONidade = cJSON_GetObjectItem(object, "idade");
        cJSON * JSONaltura = cJSON_GetObjectItem(object, "altura");
        
        char * idade = cJSON_Print(JSONidade);
        char * altura = cJSON_Print(JSONaltura);
        x[i].nome = cJSON_Print(JSONnome);
        x[i].idade = atoi(idade);
        x[i].altura = atof(altura);
        i++;
    }

    fclose(arq);
    cJSON_Delete(JSON);
    return x;
}

int main(void)
{
    pessoa * x;
    pessoa p[] = {
        {"Leonardo Peixoto", 20, 1.90},
        {"Lucas Santos", 20, 1.94}
    };

    unsigned int array_size = (sizeof(p) / sizeof(pessoa));

    create_JSON(p, array_size);   
    x = reading_json(array_size);

    for (int i = 0; i < array_size; i++)
    {
        print_pessoa(&x[i]);
    }
    
    free(x);
    return 0;
}
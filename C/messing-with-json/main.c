#include <cjson/cJSON.h>
#include <stdio.h>
#include <stdlib.h>

#define NOME_SIZE 150
#define BUFFER_SIZE 1024
#define FILE_NAME "file.json"

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

void create_JSON(pessoa p[], unsigned int arraySize)
{
    FILE * arq = fopen(FILE_NAME, "w");
    if (arq == NULL) {
        puts("File opening failure");
        exit(0);
    }

    // adicionando elementos ao JSON
    cJSON * json = cJSON_CreateObject();
    cJSON * pessoa = cJSON_CreateObject();

    char * pessoa_str;



    // convertendo os elementos do objeto para uma string
    // char * json_str = cJSON_Print(json);

    // fputs(json_str, arq);
    fclose(arq);

    cJSON_free(pessoa_str);
    // cJSON_free(json_str);
    cJSON_Delete(json);
    cJSON_Delete(pessoa);
}

pessoa read_JSON()
{
    char buffer[sizeof(pessoa)];
    FILE * arq = fopen(FILE_NAME, "r");
    if (arq == NULL)
    {
        puts("File opening failure.");
        exit(0);
    }

    fread(buffer, sizeof(pessoa), sizeof(buffer), arq);
    cJSON * json = cJSON_Parse(buffer);

    char * json_string = cJSON_Print(json);
    printf("JSON Values: \n %s \n", json_string);

    pessoa x = {"", 0, 0.0f};

    // retirando os dados do objeto json original e segmantando eles
    cJSON * JSONnome = cJSON_DetachItemFromObject(json, "nome");
    cJSON * JSONidade = cJSON_DetachItemFromObject(json, "idade");
    cJSON * JSONaltura = cJSON_DetachItemFromObject(json, "altura");
    
    // passando eles para string
    char * nome = cJSON_Print(JSONnome);
    char * idade = cJSON_Print(JSONidade);
    char * altura = cJSON_Print(JSONaltura);

    // convertendo em seus respectivos tipos de dados
    x.nome = nome;
    x.idade = atoi(idade);
    x.altura = atof(altura);

    cJSON_Delete(json);
    cJSON_Delete(JSONnome);
    cJSON_Delete(JSONidade);
    cJSON_Delete(JSONaltura);

    fclose(arq);

    return x;
}

int main(void)
{
    pessoa p[] = {
        {"Leonardo Peixoto", 20, 1.90},
        {"Lucas Santos", 20, 1.94}
    };

    unsigned int arraySize = sizeof(p) / sizeof(pessoa);

    printf("Size: %d", arraySize);

    create_JSON(p, arraySize);

    // pessoa x = read_JSON();

    // print_pessoa(&x);

    return 0;
}
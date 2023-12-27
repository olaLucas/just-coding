#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

typedef struct string
{
    char * str;
    size_t length;
    size_t max_size;

} string;

string initSTRING(const size_t size)
{
    string buf;

    if (size <= 0)
    {
        fprintf(stderr, "initBUFFER: size <= 0\n\n");
        exit(-1);
    }

    buf.str = (char *)calloc(size, sizeof(char));
    buf.length = 0;
    buf.max_size = size;

    if (buf.str == NULL)
    {
        fprintf(stderr, "initBUFFER: Out of memory!\n\n");
        exit(-1);
    }

    return buf;
}

void deleteSTRING(string * buf)
{
    if (buf->str != NULL)
        free(buf->str);
    buf->max_size = 0;
}

int multiplica(const int num_args, ...)
{
    // armazena os valores passados como argumentos na função em que for declarado
    va_list lista;

    int resultado = 1;

    // inicializa os n termos passados como parâmetros para a função
    va_start(lista, num_args);
    for (int i = 0; i < num_args; i++)
    {
        resultado = resultado * va_arg(lista, int);
    }

    va_end(lista);

    return resultado;
}

// realloc the str to fit new amount of data
char * resize(char * str, const size_t length)
{
    if (str != NULL && length > 0)
    {
        char * tempPtr = (char *)realloc(str, length);
        if (tempPtr != NULL)
            return tempPtr;
        else
        {
            fprintf(stderr, "resize(): tempPtr == NULL");
            exit(-1);
        }

    }
    else if (str == NULL)
    {
        fprintf(stderr, "resize(): str == NULL");
        return str;
    }
    else
    {
        fprintf(stderr, "resize(): length <= 0");
        return str;
    }
}

void copystr(string * fstr, const char * str, const size_t str_length)
{
    if ((fstr->length + str_length) >= fstr->max_size)
    {
        fstr->str = resize(fstr->str, fstr->max_size + str_length + 1);
        fstr->max_size += str_length;
    }

    strcat(fstr->str, str);
    fstr->length += str_length;
}

char * makestr(const char strArg[], ...)
{
    size_t ARG_Size = strlen(strArg);
    string fstr = initSTRING(ARG_Size);
    char * buffer = (char *)calloc(BUFFER_SIZE, sizeof(char));

    if (buffer == NULL) {
        fprintf(stderr, "makestr(): buffer == NULL");
        exit(-1);
    }

    va_list list;
    va_start(list, strArg);

    char * ch;
    int Findex = 0;
    for (size_t i = 0; i < ARG_Size; i++)
    {
        ch = &strArg[i];
        if (*ch != '%')
        {
            fstr.str[Findex] = *ch;
            fstr.length++;
            Findex++;
            continue;
        }

        ch++; i++;
        switch (*ch)
        {
        case 'd':
            snprintf(buffer, BUFFER_SIZE, "%d", va_arg(list, int));
            copystr(&fstr, buffer, strlen(buffer));
            Findex = fstr.length; // updating the index
            break;

        case 'f':
            snprintf(buffer, BUFFER_SIZE, "%f", va_arg(list, double));
            copystr(&fstr, buffer, strlen(buffer));
            Findex = fstr.length; // updating the index
            break;

        case 's':

            char * tempStr = va_arg(list, char *);
            if (strlen(tempStr) > 0)
            {
                copystr(&fstr, tempStr, strlen(tempStr));
                Findex = fstr.length; // updating the index
            }
            break;

        case 'c':
            snprintf(buffer, BUFFER_SIZE, "%c", va_arg(list, int));
            copystr(&fstr, buffer, strlen(buffer));
            Findex = fstr.length; // updating the index
            break;

        case 'l':

            switch (*(ch + 1))
            {
            case 'd':
                snprintf(buffer, BUFFER_SIZE, "%ld", va_arg(list, long int));
                copystr(&fstr, buffer, strlen(buffer));
                Findex = fstr.length; // updating the index
                break;

            case 'f':
                snprintf(buffer, BUFFER_SIZE, "%lf", va_arg(list, double));
                copystr(&fstr, buffer, strlen(buffer));
                Findex = fstr.length; // updating the index
                break;

            default:
                fprintf(stderr, "makestr(): invalid indentifier: %c%c%c\n\n", *(ch - 2), *(ch - 1), *ch);
                break;
            }

            ch++;
            break;

        default:
            fprintf(stderr, "makestr(): invalid indentifier: %c%c\n\n", *(ch - 1), *ch);
            break;
        }

        // cleaning buffer
        strcpy(buffer, "");
    }

    free(buffer);
    va_end(list);
    return fstr.str;
}


int main(void)
{
    char * test = makestr("abc %s %d %f", "Lucas", 20, 1.90f);

    printf("test: %s\n\n", test);

    return 0;
}

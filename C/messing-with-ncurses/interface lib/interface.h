#if !defined(STD_INCLUDES)
    #define STD_INCLUDES
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define STRING_SIZE 300
    #define BUFFER_SIZE 1024
    #define TOKEN_CHAR "\""

#endif // STD_INCLUDES

#include <stdarg.h>
#include <ncurses.h>
#include <form.h>

struct option {
    char * text;
    int row, column;
};

extern const unsigned int STD_COLUMN_OFFSET;
extern const unsigned int STD_OPTION_ROW_PRINT;

extern unsigned int menu_select(
    const char * title,
    const char * subtitle,
    const struct option menuOptions[], 
    const int n_options
);

extern void get_input(
    const char * title, 
    const char * subtitle, 
    const unsigned int n_options, ...
);
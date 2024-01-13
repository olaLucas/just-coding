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

const unsigned int STD_COLUMN_OFFSET = 3;
const unsigned int STD_TITLES_OFFSET = 5;
const unsigned int STD_OPTION_ROW_PRINT = 3;
const unsigned int STD_TITLE_ROW = 0;
const unsigned int STD_SUBTITLE_ROW = 1;

struct APIData_t {
    char * lon;
    char * lat;
    char * appid;
    char * units;
    char * city;
};

struct win {
    WINDOW * window;
    int nrows, ncolumns;
    int startx, starty;
};

struct option {
    char * text;
    int row, column;
};

struct win initWindow(
        const unsigned int nrows, 
        const unsigned int ncolumns,
        const unsigned int starty,
        const unsigned int startx
    )
{
    struct win w;
    w.window = newwin(
        nrows, ncolumns, starty, startx
    );

    if (w.window == NULL) {
        fprintf(stderr, "initWindow(): Error while creating new window.");
        exit(-1);
    }

    box(w.window, 0, 0);
    w.nrows = nrows;
    w.ncolumns = ncolumns;
    w.starty = starty;
    w.startx = startx;
    return w;
}

void print_options(
        const struct win w, 
        const struct option menuOptions[], 
        const int n_options, 
        const int choice
    )
{
    wclear(w.window);
    box(w.window, 0, 0);

    for (int i = 0; i < n_options; i++)
    {
        mvwprintw(
            w.window, 
            menuOptions[i].row, 
            menuOptions[i].column, 
            "%d. %s", i + 1, menuOptions[i].text
        );

        if (choice == i + 1)
        {
            mvwchgat(
                w.window, 
                menuOptions[i].row, 
                menuOptions[i].column - 1, 
                w.ncolumns - 4, 
                A_REVERSE, 
                0, NULL
            );
        }
    }
    
    wrefresh(w.window);
}   

unsigned int menu_select(
        const char * title,
        const char * subtitle,
        const struct option menuOptions[], 
        const int n_options
    )
{
    initscr();
    struct win w = initWindow((LINES - 2), (COLS - 2), 1 ,1);

    cbreak();
    noecho();
    keypad(w.window, true);

    int ch = 0;
    int choice = 1;

    do
    {
        print_options(w, menuOptions, n_options, choice);
        mvwprintw(w.window, 0 , 5, title);
        mvwprintw(w.window, 1, 5, subtitle);

        ch = wgetch(w.window);
        switch (ch)
        {
        case KEY_UP: // 119 == w
            // going to the last element after reach the top of the menu
            if (choice == 1)
                choice = n_options; 
            else 
                choice--;

            break;
        
        case KEY_DOWN: // 115 == s
            // going to the first element after reach the bottom of the menu
            if (choice == n_options)
                choice = 1; 
            else
                choice++;
            
            break;

        case '\n':            

            delwin(w.window);
            endwin();
            return choice;
            break;

        default:
            break;
        }

        wrefresh(w.window);
        
    } while (true);
}

/* 

get an input from the user variable times. the variable arguments must be passed as pair like this:

char * bufferToStoreInput;
get_input("title", "subtitle", 1, "template asking the user what you want:", bufferToStoreInput);

(works both for char [] strings, char *)

*/
void get_input(
        const char * title, 
        const char * subtitle, 
        const unsigned int n_pairs, ...
    )
{
    initscr();
    struct win w = initWindow((LINES - 2), (COLS - 2), 1 ,1);
    char * template = NULL;
    char * buffer = NULL;

    va_list list;
    va_start(list, n_pairs);

    mvwprintw(w.window, STD_TITLE_ROW, STD_TITLES_OFFSET, title);
    mvwprintw(w.window, STD_SUBTITLE_ROW, STD_TITLES_OFFSET, subtitle);

    for (int i = 0; i < n_pairs; i++)
    {   
        template = va_arg(list, char *);
        mvwprintw(w.window, STD_OPTION_ROW_PRINT + i, STD_COLUMN_OFFSET, template);
        wrefresh(w.window);

        buffer = va_arg(list, char *);
        if (buffer == NULL)
            fprintf(stderr, "get_input(): buffer = NULL at \"%s\" template in %d pair\n\n", template, i + 1);
        else
            wgetstr(w.window, buffer);
    }

    va_end(list);
    delwin(w.window);
    endwin();
}


// void get_input(
//         const char * title, 
//         const char * subtitle, 
//         const unsigned int n_options, ...
//     )
// {   
//     /* ncurses window initialization */
//     initscr();
//     WINDOW * w = newwin((LINES - 2), (COLS - 2), 1 ,1);
//     box(w, 0, 0);

//     cbreak(); noecho();
//     keypad(w, true);

//     FORM * form;
//     FIELD * fields[n_options + 1];
//     char ** buffers[n_options];
//     int ch = 0;
    
//     if (n_options <= 0)
//     {
//         fprintf(stderr, "get_input(): n_options <= 0\n\n");
//         return;
//     }

//     va_list list;
//     va_start(list, n_options);

//     /* printing title and subtitle */
//     mvwprintw(w, 0 , 5, title);
//     mvwprintw(w, 1, 5, subtitle);
    
//     size_t siz = 0;
//     char * temp = NULL;

//     /* initializing fields */
//     for (int i = 0; i < n_options; i++)
//     {   
//         temp = va_arg(list, char *);
//         siz = strlen(temp);
//         mvwprintw(w, STD_OPTION_ROW_PRINT + i, STD_COLUMN_OFFSET, temp);
//         // int height, int width, int toprow, int leftcol, int offscreen, int nbuffers
//         fields[i] = new_field(1, COLS - 20, STD_OPTION_ROW_PRINT + (i + 1), siz + 1, 0, 0);

//         set_field_back(fields[i], A_UNDERLINE);
//         field_opts_off(fields[i], O_AUTOSKIP);

//         /* getting the pointer of the caller */
//         buffers[i] = va_arg(list, char **); 

//         /* assigning to the caller pointer the address of the user's input */
//         // *buffers[i] = field_buffer(fields[i], 0);
//         set_field_buffer(fields[i], 0, *buffers[i]);
//     }

//     /* why the last field needs to be NULL? Wished to know too... */
//     fields[n_options] = NULL;
    
//     form = new_form(fields);
//     set_current_field(form, fields[0]);

//     int frow = 0, fcolumn = 0;
//     scale_form(form, &frow, &fcolumn);

//     set_form_win(form, w);
//     set_form_sub(form, derwin(w, frow, fcolumn, 2, 2));
//     post_form(form);
//     wrefresh(w);


//     /* navigations through the fields */
//     do
//     {
//         ch = wgetch(w);
//         switch (ch)
//         {
//         case KEY_UP:
//             form_driver(form, REQ_PREV_FIELD);
//             form_driver(form, REQ_END_LINE);
//             break;
        
//         case KEY_DOWN:
//             form_driver(form, REQ_NEXT_FIELD);
//             form_driver(form, REQ_END_LINE);
//             break;

//         case '\n':
//             for (int i = 0; i < n_options; i++)
//             {*buffers[i] = field_buffer(fields[i], 0);}
//             break;

//         default:
//             form_driver(form, ch);
//             break;
//         }

//     } while (ch != KEY_F(1));
    
    
//     /* deleting fields */
//     unpost_form(form);
//     free_form(form);
//     for (size_t i = 0; i < n_options - 1; i++)
//     {
//         free_field(fields[i]);
//     }

//     va_end(list);
//     delwin(w);
//     endwin();
// }
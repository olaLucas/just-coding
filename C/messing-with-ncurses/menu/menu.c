#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

struct win 
{
    WINDOW * window;
    int nrows, ncolumns;
    int starty, startx;
};

typedef struct option
{
    char text[150];
    int row, column;

} option;

const option options[] = {
    {"Print: Hello, world!", 3, 2},
    {"Exit.", 4, 2}
};

const int n_options = sizeof(options) / sizeof(option);


void print_menu(struct win w, const int choice)
{
    wclear(w.window);
    box(w.window, 0, 0);

    mvwprintw(w.window, 0, 5, "Welcome!");
    mvwchgat(w.window, 0, 5, strlen("Welcome!"), A_BOLD, 0, NULL);
    
    mvwprintw(
        w.window, 1, 1, "This is an test menu. Please select an option:"
    );

    for (int i = 0; i < n_options; i++)
    {
        mvwprintw(
            w.window, options[i].row, options[i].column, "%d. %s", i + 1, options[i].text
        );

        if (choice == i + 1)
        {
            mvwchgat(
                w.window, options[i].row, options[i].column - 1, w.ncolumns - 2, A_REVERSE, 0, NULL
            );
        }
    }
    
    wrefresh(w.window);
}

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


    if (w.window != NULL)
    {
        box(w.window, 0, 0);
        w.nrows = nrows;
        w.ncolumns = ncolumns;
        w.starty = starty;
        w.startx = startx;

        return w;
    }
    else
    {
        fprintf(stderr, "Error while creating new window.");
        exit(-1);
    }
}

void exec(struct win w, const int choice)
{
    wclear(w.window);
    box(w.window, 0, 0);

    if (1 == choice)
    {
        const char str[] = "Hello, World!";
        if (has_colors())
        {   
            wattr_on(w.window, A_BOLD, NULL);
                mvwprintw(w.window, 2, 2, str);
            wattr_off(w.window, A_BOLD, NULL);
        

            wrefresh(w.window);
            wgetch(w.window);
            return;
        }
        else
        {
            wattr_on(w.window, A_BOLD, NULL);
                mvwprintw(w.window, 2, 2, str);
            wattr_off(w.window, A_BOLD, NULL);

            wrefresh(w.window);
            wgetch(w.window);
            return;
        }
    }
    else if (2 == choice)
    {
        wattr_on(w.window, A_BOLD, NULL);
            mvwprintw(w.window, 1, 2, "Exiting...");
            wgetch(w.window);
        wattr_off(w.window, A_BOLD, NULL);

        delwin(w.window);
        endwin();
    
        exit(0);
    }
    else
    {   
        const char str[] = "You might pressed an invalid key, please try again.";

        wattr_on(w.window, A_BOLD, NULL);
        mvwprintw(
            w.window, 1, 2, str 
        );

        wattr_off(w.window, A_BOLD, NULL);

        wrefresh(w.window);
        wgetch(w.window);
    }
}

int main(void)
{
    initscr();

    int ch = 0;
    int choice = 1;
    struct win menu = initWindow((LINES - 2), (COLS - 2), 1, 1);

    cbreak();
    noecho();
    keypad(menu.window, true);

    do
    {
        print_menu(menu, choice);

        ch = wgetch(menu.window);
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

            exec(menu, choice);
            break;

        default:
            break;
        }

        wrefresh(menu.window);
        
    } while (true);
    

    delwin(menu.window);
    endwin();

    return 0;
}
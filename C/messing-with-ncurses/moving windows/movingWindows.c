#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

typedef struct boder
{
    chtype leftside, rightside, topside, bottomside;
    chtype topleft, topright, bottomleft, bottomright;
} winborder;

typedef struct win
{
    int startx, starty;
    int height, width;
    winborder wb;
} win;

void init_win(win * w, const int height, const int width)
{
    // size
    w->height = height;
    w->width = width;
    
    // offset
    w->startx = (COLS - width) / 2;
    w->starty = (LINES - height) / 2;

    // retas
    w->wb.leftside = '|';
    w->wb.rightside = '|';
    w->wb.topside = '-';
    w->wb.bottomside = '-';

    // arestas
    w->wb.topleft = '+';
    w->wb.topright = '+';
    w->wb.bottomleft = '+';
    w->wb.bottomright = '+';
}


void print_win(const win * w)
{
    int stx, sty; 
    int height, width;

    stx = w->startx;
    sty = w->starty;
    height = w->height;
    width = w->width;

    // adding arestas
    mvaddch(sty, stx, w->wb.topleft);
    mvaddch(sty, stx + width, w->wb.topright);
    mvaddch(sty + height, stx, w->wb.bottomleft);
    mvaddch(sty + height, stx + width, w->wb.bottomright);

    // horizontal lines
    mvhline(sty, stx + 1, w->wb.topside, width - 1);
    mvhline(sty + height, stx + 1, w->wb.bottomside, width - 1);

    // vertical lines
    mvvline(sty + 1, stx, w->wb.leftside, height - 1);
    mvvline(sty + 1, stx + width, w->wb.rightside, height - 1);

    refresh();
}


void clean_win(const win * w)
{   
    for (int i = w->starty; i <= w->starty + w->height; ++i)
    {
        for (int j = w->startx; j <= w->startx + w->width; ++j)
        {
            mvaddch(i, j, ' ');
        }
    }

    refresh();
}


int main(void)
{
    initscr();
    cbreak();
    keypad(stdscr, true);

    win w;
    chtype ch;

    init_win(&w, 5, 10);

    printw("Press F1 to exit.\n");
    printw("Press one of the arrow keys to move the window.\n\n");
    refresh();


    print_win(&w);
    while ((ch = getch()) != KEY_F(1))
    {

        switch (ch)
        {
        case KEY_UP:
            clean_win(&w);
            --w.starty;
            print_win(&w);
            break;
        
        case KEY_DOWN:
            clean_win(&w);
            ++w.starty;
            print_win(&w);
            break;

        case KEY_LEFT:
            clean_win(&w);
            --w.startx;
            print_win(&w);            
            break;

        case KEY_RIGHT:
            clean_win(&w);
            ++w.startx;
            print_win(&w);            
            break;


        default:
            clean_win(&w);
            printw("Wrong key pressed\n");
            printw("Please, use only the arrow keys\n\n");
            refresh();
            getch();
            break;
        }
    }
    

    endwin();    

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

void helloWorld()
{
	// escreve os dados a serem impressos num buffer
	printw("Hello, world!");
	printw("\n\npressione enter para sair...");

	// atualiza a tela (escreve os dados do buffer na tela)
	refresh();

	// espera por um input do usuário
	getch();
}

void printKey()
{
	raw();
	keypad(stdscr, TRUE);
	noecho();

	printw("Pressione alguma tecla: \n");
	int ch = getch();

	if (ch == KEY_F(1))
	{
		printw("A tecla: F1 foi pressionada.\n\n");
	}
	else
	{
		attron(A_BOLD);
		printw("Tecla pressionada: %c\n\n", ch);
		attroff(A_BOLD);
	}

	refresh();
	getch();
}

void printwm()
{
	const char string[] = "Testando...";
	int row = 0, colom = 0;
	getmaxyx(stdscr, row, colom);

	int midrow = (row / 2);
	int midcolom = ((colom - strlen(string)) / 2);

	printw("row: %d\n", row);
	printw("colom: %d\n", colom);

	// print the string in the center of the terminal
	mvwprintw(stdscr, midrow, midcolom, string);

	refresh();
	getch();
}

void testingInputs()
{

	int row = 0, colum = 0;
	int midrow = 0;
	char nome[150] = "";
	char senha[150] = "";

	getmaxyx(stdscr, row, colum);
	midrow = (row / 2);

	cbreak();
	printw("Insira seu nome: ");
	getstr(nome);

	noecho();
	printw("\nInsira sua senha: ");
	getstr(senha);

	// importante se atenar à ordem da subtração
	mvwprintw(
		stdscr, midrow, ((colum - strlen(nome)) / 2), "nome: %s", nome);

	mvwprintw(
		stdscr, midrow + 1, ((colum - strlen(senha)) / 2), "senha: %s", senha);
	// o '+1' serve para pular uma linha, já que o nome está sendo exibido no meio da tela

	refresh();
	getch();

	echo();
	nocbreak();
}

void testingCbreakInputs()
{
	int number = 0;
	int result = 0;

	cbreak();

	printw("Insira um número (0 ~ 9): ");
	number = wgetch(stdscr); // retorna o código da tecla, não o character em si

	printw("\nNúmero inserido: %d", number);

	printw("\nInsira um número (0 ~ 9): ");
	while (true)
	{
		if ((result = getch()) != number)
		{
			printw("\nNúmero inserido: %d", result);
			printw("\nDigite %d para sair.\n\n", number);
			printw("\nInsira um número (0 ~ 9): ");
			refresh();
		}
		else
		{
			printw("Saindo...");
			refresh();
			nocbreak();
			break;
		}
	}
}

void testingAttributes()
{
	attron(A_STANDOUT);
	printw("A_STANDOUT\n\n");
	attroff(A_STANDOUT);

	attron(A_UNDERLINE);
	printw("A_UNDERLINE\n\n");
	attroff(A_UNDERLINE);

	attron(A_REVERSE);
	printw("A_REVERSE\n\n");
	attroff(A_REVERSE);

	attron(A_BLINK);
	printw("A_BLINK\n\n");
	attroff(A_BLINK);

	attron(A_DIM);
	printw("A_DIM\n\n");
	attroff(A_DIM);

	attron(A_BOLD);
	printw("A_BOLD\n\n");
	attroff(A_BOLD);

	attron(A_PROTECT);
	printw("A_PROTECT\n\n");
	attroff(A_PROTECT);

	attron(A_INVIS);
	printw("A_INVIS\n\n");
	attroff(A_INVIS);

	attron(A_ALTCHARSET);
	printw("A_ALTCHARSET\n\n");
	attroff(A_ALTCHARSET);

	attron(A_CHARTEXT);
	printw("A_CHARTEXT\n\n");
	attroff(A_CHARTEXT);

	// attron();
	// printw("");
	// attroff();

	refresh();
	getch();
}

void testingchgat()
{
	char j[] = "hello world";

	printw(j);
	mvchgat(0, 0, strlen(j), A_UNDERLINE, 0, NULL);

	refresh();
	getch();
}

void testingWindow(char str[])
{
	WINDOW * mywin;
	int x = 0, y = 0;

	mywin = newwin((LINES / 2), (COLS / 2), 5, 5);
	getmaxyx(mywin, y, x);

	wborder(mywin, '|', '|', '-', '-', '*', '*', '*', '*');

	mvwprintw(mywin, (y / 2), ((x - strlen(str)) / 2), str);
	wrefresh(mywin);
	wgetch(mywin);
	delwin(mywin);
}

int main(void)
{
	// inicializa o terminal no modo curses
	initscr();

	testingWindow("Hello, world!");

	// encerra e desaloca os recursos da lib
	endwin();

	return 0;
}
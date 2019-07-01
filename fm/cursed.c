#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <ncursesw/curses.h>

void sig_winch(int signo)
{
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char*) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void getext(WINDOW* swin, char* buffer, int maxlen)
{
	int i=0;
	int ch=0;
	wmove(swin, 1, 0);
	while(((ch=wgetch(swin))!=10)&&(i<maxlen-1))
	{
			int x=0, y=0;

		if(ch==KEY_BACKSPACE)
		{
			if (i==0) {waddch(swin, ' '); buffer[i]=' '; wmove(swin, 1, 0); continue;}//obrabotka 0
			getyx(swin, y, x);
			mvwaddch(swin, y, x+1, ' ');
			buffer[i]=' ';
			wrefresh(swin);
			wmove(swin, y, x);
			i--;
			continue;
		}
		if(ch==KEY_LEFT)
		{
			if(i==0) continue;
			getyx(swin, y, x);
			if(x==0) wmove(swin, y-1, x+47);
			else wmove(swin, y, x-1);
			i--;
			continue;
		}
		if(ch==KEY_RIGHT)
		{
			if (i==maxlen-2) continue;
			getyx(swin, y, x);
			if(x==47){ wmove(swin, y+1, x-47);}
			else wmove(swin, y, x+1);
			i++;
			continue;
		}
		buffer[i++]=ch;
		//waddch(swin, buffer[i++]);
	}
	buffer[i]=0;
}

int curses(char* buffer, int maxlen)
{
	WINDOW* wnd;
	WINDOW* swnd;
	initscr();
	signal(SIGWINCH, sig_winch);
	cbreak();
	curs_set(1);
	start_color();
	refresh();
	init_pair(1, COLOR_GREEN, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	wnd =newwin(30, 50, 1, 1);
	wattron(wnd, COLOR_PAIR(1));
	box(wnd, '|', '-');
	swnd= derwin(wnd, 28, 48, 1, 1);
	wbkgd(swnd, COLOR_PAIR(2));
	wrefresh(swnd);
	wrefresh(wnd);
	wmove(swnd, 1, 0);
	wprintw(swnd, buffer);
	refresh();
	keypad(swnd, TRUE);
	getext(swnd, buffer, maxlen);//text redactor
	getch();
	delwin(swnd);
	delwin(wnd);
	endwin();
	//exit(EXIT_SUCCESS);
}

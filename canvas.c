#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <ncurses.h>

int main (void)

{
		struct pollfd mypoll = { STDIN_FILENO, POLLIN|POLLPRI };
	
        /* compile with gcc -lncurses file.c */
        int c = 0;
        /* Init ncurses mode */
        initscr ();
        /* Hide cursor */
        curs_set (0);
        while (c < 1000) {
                /* Print at row 0, col 0 */
                mvprintw (0, 0, "%d", c++);
                refresh ();
                if( poll(&mypoll, 1, 2000) )
				{
					getch();
				}
        }
        /* End ncurses mode */
        endwin();
        return 0;
}

#include<ncurses.h>
int main()
{
    initscr();
    mvprintw(20,10,"#");
    refresh();
    getch();
    endwin();
    return 0;



}

#include<ncurses.h>
#include<unistd.h>
char data[19][11] = { 0 };
int x=4, y=-2, c=0, z=0; 
const char bk[7][4][4][4] =
    {
    {
    { { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
    { { 0,1,1,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 0,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 0,1,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 1,1,1,0 },{ 1,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,0,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } },
    { { 0,0,1,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 0,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 1,1,1,0 },{ 0,0,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 0,1,0,0 },{ 0,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,1,0,0 },{ 1,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 0,1,0,0 },{ 1,1,1,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 0,1,0,0 },{ 1,1,0,0 },{ 0,1,0,0 },{ 0,0,0,0 } },
    { { 1,1,1,0 },{ 0,1,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,1,0,0 },{ 1,0,0,0 },{ 0,0,0,0 } }
    }
    ,
    {
    { { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } },
    { { 1,1,1,1 },{ 0,0,0,0 },{ 0,0,0,0 },{ 0,0,0,0 } },
    { { 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 },{ 1,0,0,0 } }
    }
    };
const char bg[]=
    "|-----------|           \n"
    "|           |   \n"
    "|           |      Begin\n"
    "|           | Voice = Yes\n"
    "|           |      Sleep \n"
    "|           |       Quit \n"
    "|           |           \n"
    "|           |           \n"
    "|           | ＮＥＸＴ  \n"
    "|           ||-----|\n"
    "|           ||     |\n"
    "|           ||     |\n"
    "|           ||-----|\n"
    "|           | ＬＥＶＥＬ\n"
    "|           ||-----|\n"
    "|           ||  0  |\n"
    "|           ||-----|\n"
    "|           |ＳＣＯＲＥ \n"
    "|           ||-----|\n"
    "|           ||00000|\n"
    "|-----------||-----|\n";

bool IsFit( int x, int y, int c, int z ) // 给定的x,y,c,z是否可行
    {
    for( int i=0; i<4; ++i )
    {
    for( int j=0; j<4; ++j )
    {
    if( bk[c][z][i][j]==1 )
    {
    if( y+i < 0 ) continue;
    if( y+i>=19 || x+j<0 || x+j>=11 || data[y+i][x+j]==1 )
return false;
    }
    }
    }
    return true;
    }
void DrawC(  )
{
    for(int i=0;i<4;++i)
    {   
        if(y+i<0||y+i>=19) continue;
        for(int j=0;j<4;++j)
        {
            if(bk[c][z][i][j]==1)
            {
                attron(COLOR_PAIR(2));
                mvprintw(1+y+i,1+x+j,"#");
                attroff(COLOR_PAIR(2));
               
            }  
        }
    }



}
void DrawA(  )
{
    for(int i=0;i<4;++i)
    {   
        if(y+i<0||y+i>=19) continue;
        for(int j=0;j<4;++j)
        {
            if(bk[c][z][i][j]==1)
            {
                attron(COLOR_PAIR(1));
                 mvprintw(1+y+i,1+x+j,"#");
                attroff(COLOR_PAIR(1));
                
            }  
        }
    }



}
void MoveLeft(void)
{
    if(IsFit(x-1,y,c,z))
    {   
        DrawC();
        --x;
        DrawA();
    }


}
void MoveRight(void)
{
    if(IsFit(x+1,y,c,z))
    {   
        DrawC();
        ++x;
        DrawA();
    }


}
void MoveDown(void)
{
  //  if(IsFit(x,y+1,c,z))
    {   
        DrawC();
        ++y;
        DrawA();
    }
//    else if(y!=-2)
//    {
//        Draw( COLOR_B);

  //  }

}
void MoveTrans(void)
{
    if(IsFit(x,y,c,(z+1)%4))
    {   
        DrawC();
        z=(z+1)%4;
        DrawA();
    }


}
void MessageDeal(void)
{
    for(;;)
    {   
        for(;;){
        switch(getch())
        {
            case KEY_LEFT:
            MoveLeft();
            break;
            case KEY_DOWN:
            MoveDown();
            break;
            case KEY_RIGHT:
            MoveRight();
            break;
            case KEY_UP:
            MoveTrans();
            default:
            break;
        }
        sleep(5/100);
        }
        MoveDown();
    }
}
int main()
{
    initscr();
    curs_set(0);
    cbreak();
    keypad(stdscr,TRUE);
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLACK,COLOR_BLACK);
    printw(bg);
    MessageDeal();
    refresh();
    getch();
    endwin();
    return 0;



}

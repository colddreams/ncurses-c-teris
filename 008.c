#include<ncurses.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<fcntl.h>
char data[19][11] = { 0 };
int x=4, y=-2, c=-1, z=0; 
int next =-1;
int ch = 0;
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
/*
void sleep2()

{
    struct timeval delay;
    delay.tv_sec = 0;
    delay.tv_usec = 55*1000;
    select(0,NULL,NULL,NULL,&delay);

}
*/
void DrawOver()
{
    mvprintw(20,10,"GAME");
    mvprintw(21,11,"OVER");
}
void RemoveRow()
{
    const char FULLLINE[]={1,1,1,1,1,1,1,1,1,1,1};
    int linecount = 0;
    for(int i=0;i<19;++i)
    {
        if(0==memcmp(data[i],FULLLINE,11))
        {
            ++linecount;
            for(int m=0;m<11;++m)
            {
                for(int n=i;n>1;--n)
                {
                    data[n][m] = data[n-1][m];
                    if(data[n][m]==1){
                    attron(COLOR_PAIR(3));
                    mvprintw(1+m,1+n,"#");
                    attroff(COLOR_PAIR(3));}
                    else{
                    attron(COLOR_PAIR(2));
                    mvprintw(1+n,1+m,"#");
                    attroff(COLOR_PAIR(2));}
                                        
                }
                data[0][m] = 0;
                mvprintw(1,m,"#");
            }
        }
    }
    char data[19][11]={0};

}
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

void DrawB(  )
{
    for(int i=0;i<4;++i)
    {   
        if(y+i<0||y+i>=19) continue;
        for(int j=0;j<4;++j)
        {
            if(bk[c][z][i][j]==1)
            {
                attron(COLOR_PAIR(3));
                mvprintw(1+y+i,1+x+j,"#");
                attroff(COLOR_PAIR(3));
               
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
    if(IsFit(x,y+1,c,z))
    {   
        DrawC();
        ++y;
        DrawA();
    }
    else if(y!=-2)
    {
        DrawB( );
        for (int i=0;i<4;i++)
        {
            if(y+i<0)continue;
            for(int j=0;j<4;++j)
            {
                if(bk[c][z][i][j] ==1)
                {
                    data[y+i][x+j] =1;
                }
            }
        }
        RemoveRow();
        x = 4,y=-2,c=next,z=0;
        next =rand()%7;
       // DrawNext();
        
    }
    else
    {
    DrawOver();
    }
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
    while(ch!='q'||ch != 'Q')
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
            break;
            default:
            break;
        }
        usleep(100*1000);
        MoveDown();
        }
    }
}
int main()
{
    srand(time(0));
    next = rand()%7;
    initscr();
    curs_set(0);
    cbreak();
    keypad(stdscr,TRUE);
    noecho();
    fcntl(0,F_SETFL,O_NONBLOCK);
    start_color();
    init_pair(1,COLOR_RED,COLOR_BLACK);
    init_pair(2,COLOR_BLACK,COLOR_BLACK);
    init_pair(3,COLOR_YELLOW,COLOR_BLACK);
    printw(bg);
    x=4,y=-2,c=next,z=0;
    next = rand()%7;
    MessageDeal();
    refresh();
    endwin();
    return 0;



}

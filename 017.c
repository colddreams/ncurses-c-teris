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
bool vo = FALSE;
int score = 0,level = 0;
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
    "|----------------------|           \n"
    "|                      | VOICE=NO  \n"
    "|                      |      Begin\n"
    "|                      |            \n"
    "|                      |      Sleep \n"
    "|                      |       Quit \n"
    "|                      |   NEXT  \n"
    "|                      ||--------|  \n"
    "|                      ||        |  \n"
    "|                      ||        |\n"
    "|                      ||        |\n"
    "|                      ||        |\n"
    "|                      ||--------|\n"
    "|                      | LEVEL \n"
    "|                      ||-----|\n"
    "|                      ||  0  |\n"
    "|                      ||-----|\n"
    "|                      | SCORE \n"
    "|                      ||-----|\n"
    "|                      ||00000|\n"
    "|----------------------||-----|\n";

void Voice(bool v)
{
    if(v)
    beep();

}
void VoicePrint(void)
{
    if(vo)
    mvprintw(1,31,"YES");
    else
    mvprintw(1,31,"NO ");


}
void DrawOver()
{
    mvprintw(20,10,"GAME");
    mvprintw(21,10,"OVER");
}
void DrawScoreLevel( void ) // 绘制得分
    
{
mvprintw(19,25,"%5d",score);
mvprintw(15,27,"%1d",level);
    }
void RemoveRow()
{
    const char FULLLINE[]={1,1,1,1,1,1,1,1,1,1,1};
    int linecount = 0;
    for(int i=0;i<19;++i)
    {
        if(0==memcmp(data[i],FULLLINE,11))
        {
            Voice(vo);
            ++linecount;
            for(int m=0;m<11;++m)
            {
                for(int n=i;n>1;--n)
                {
                    data[n][m] = data[n-1][m];
                }
             //   data[0][m] = 0;
                
            }
        }
    for(int nx=18;nx>=0;--nx)
    for(int m=0;m<11;++m)
                {
                if(data[nx][m]==1){
                    attron(COLOR_PAIR(3));
                    mvprintw(1+nx,1+m*2,"[");
                    mvprintw(1+nx,2+m*2,"]");
                    attroff(COLOR_PAIR(3));}
                    else{
                    mvprintw(1+nx,1+m*2," ");
                    mvprintw(1+nx,1*2+m*2," ");
                         } 
                }    
                                        
    }
    if( linecount == 0 ) return;
    int _score = 0;
    switch( linecount )
    {
    case 1: _score = 100; break;
    case 2: _score = 300; break;
    case 3: _score = 700; break;
    case 4: _score = 1500;break;
    }
    score += _score;
    if( score > 99999 ) score = 99999;
    level = score/10000;
    DrawScoreLevel();
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
void Draw1(  )
{
    for(int i=0;i<4;++i)
    {   
        if(y+i<0||y+i>=19) continue;
        for(int j=0;j<4;++j)
        {
            if(bk[c][z][i][j]==1)
            {
                 mvprintw(1+y+i,1+x*2+j*2," ");
                mvprintw(1+y+i,2+x*2+j*2," ");
            }  
        }
    }



}

void Draw2(  )
{
    for(int i=0;i<4;++i)
    {   
        if(y+i<0||y+i>=19) continue;
        for(int j=0;j<4;++j)
        {
            if(bk[c][z][i][j]==1)
            {
                attron(COLOR_PAIR(1));
                 mvprintw(1+y+i,1+x*2+j*2,"[");
                mvprintw(1+y+i,2+x*2+j*2,"]");
                attroff(COLOR_PAIR(1));
            }  
        }
    }

}
void MoveLeft(void)
{
    if(IsFit(x-1,y,c,z))
    {   
        Draw1();
        --x;
        Draw2();
        Voice(vo);
    }


}
void MoveRight(void)
{
    if(IsFit(x+1,y,c,z))
    {   
        Draw1();
        ++x;
        Draw2();
        Voice(vo);
    }


}
void MoveDown(void)
{
    if(IsFit(x,y+1,c,z))
    {   
        Draw1();
        ++y;
        Draw2();
        Voice(vo);
    }
    else if(y!=-2)
    {
        Draw2( );
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
        Draw1();
        z=(z+1)%4;
        Draw2();
        Voice(vo);
    }


}
int MessageDeal(void)
{
    int a=0;
    int flag = 0;
    while(1)
    {   
        for(;;){
        switch(ch=getch())
        {
            case KEY_LEFT:
            if(flag)
            MoveLeft();
            break;
            case KEY_DOWN:
            if(flag)
            MoveDown();
            break;
            case KEY_RIGHT:
            if(flag)
            MoveRight();
            break;
            case KEY_UP:
            if(flag)
            MoveTrans();
            break;
            case 'q':
            case 'Q':
            endwin();
            exit( 0);
            case 's':
            case 'S':
            flag  =!flag ;
            break;
            case 'b':
            case 'B':
            flag = 1;
            break;
            case 'v':
            case 'V':
            vo = !vo;
            VoicePrint();
            break;
            default:
            break;
        }
        if(flag){
        napms(25);
        a=a+level+1;}
        break;
        }
        if(a>=40&&flag){
        a=0;
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
    start_color();
    init_pair(1,COLOR_BLUE,COLOR_RED);
    init_pair(3,COLOR_BLUE,COLOR_YELLOW);
    fcntl(0,F_SETFL,O_NONBLOCK);
    printw(bg);
    x=4,y=-2,c=next,z=0;
    next = rand()%7;
    MessageDeal();
    refresh();
    endwin();
    return 0;
}

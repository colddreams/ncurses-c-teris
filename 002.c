#include <windows.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <conio.h>
    class Console
    {
    public:
    Console()
    {
    hStdOutput = INVALID_HANDLE_VALUE;
    hStdError = INVALID_HANDLE_VALUE;
    }
    bool Open( void )
    {
    hStdOutput = GetStdHandle( STD_OUTPUT_HANDLE );
    hStdError = GetStdHandle( STD_ERROR_HANDLE );
    return INVALID_HANDLE_VALUE!=hStdOutput && INVALID_HANDLE_VALUE!=hStdError;
    }
    inline bool SetTitle( char* title ) // 设置标题，SetConsoleTitle("怎么用");标题栏上就显示  怎么用
    {
    return TRUE==SetConsoleTitle(title);
    }
    bool RemoveCursor( void ) // 去处光标
    {
    CONSOLE_CURSOR_INFO cci;
    if( !GetConsoleCursorInfo( hStdOutput, &cci ) ) return
false;
    cci.bVisible = false;
    if( !SetConsoleCursorInfo( hStdOutput, &cci ) ) return
false;
    if( !GetConsoleCursorInfo( hStdError, &cci ) ) return
false;
    cci.bVisible = false;
    if( !SetConsoleCursorInfo( hStdError, &cci ) ) return
false;
    return true;
    }
    bool SetWindowRect( short x, short y ) // 设置窗体尺寸
    {
    SMALL_RECT wrt = { 0, 0, x, y };
    if( !SetConsoleWindowInfo( hStdOutput, TRUE, &wrt ) )
return false;
    if( !SetConsoleWindowInfo( hStdError, TRUE, &wrt ) )
return false;
    return true;
    }
    bool SetBufSize( short x, short y ) // 设置缓冲尺寸
    {
    COORD coord = { x, y };
    if( !SetConsoleScreenBufferSize( hStdOutput, coord ) )
return false;
    if( !SetConsoleScreenBufferSize( hStdError, coord ) )
return false;
    return true;
    }
    bool GotoXY( short x, short y ) // 移动光标
    {
    COORD coord = { x, y };
    if( !SetConsoleCursorPosition( hStdOutput, coord ) )
return false;
    if( !SetConsoleCursorPosition( hStdError, coord ) )
return false;
    return true;
    }
    bool SetColor( WORD color ) // 设置前景色/背景色
    {
    if( !SetConsoleTextAttribute( hStdOutput, color ) )
return false;
    if( !SetConsoleTextAttribute( hStdError, color ) )
return false;
    return true;
    }
    bool OutputString( const char* pstr, size_t len=0 ) // 输出字符串
    {
    DWORD n = 0;
    return TRUE==WriteConsole( hStdOutput, pstr, len?
len:strlen(pstr), &n, NULL );
    }
    bool OutputStringNoMove( short x, short y, const char*pstr, size_t len=0 ) // 输出字符串
    {
    COORD coord = { x, y };
    DWORD n = 0;
    return TRUE==WriteConsoleOutputCharacter( hStdOutput,
pstr, len?len:strlen(pstr), coord, &n );
    }
    private:
    HANDLE hStdOutput;
    HANDLE hStdError;
    };
    const char bg[]=
    "┏━━━━━━━━━━━┓            "
    "┃■■■■■■■■■■■┃   ←↓→ ↑"
    "┃■■■■■■■■■■■┃      Begin "
    "┃■■■■■■■■■■■┃ Voice = Yes"
    "┃■■■■■■■■■■■┃      Sleep "
    "┃■■■■■■■■■■■┃       Quit "
    "┃■■■■■■■■■■■┃            "
    "┃■■■■■■■■■■■┃            "
    "┃■■■■■■■■■■■┃ ＮＥＸＴ   "
    "┃■■■■■■■■■■■┃┏━━━━┓"
    "┃■■■■■■■■■■■┃┃　　　　┃"
    "┃■■■■■■■■■■■┃┃　　　　┃"
    "┃■■■■■■■■■■■┃┗━━━━┛"
    "┃■■■■■■■■■■■┃ ＬＥＶＥＬ "
    "┃■■■■■■■■■■■┃┏━━━━┓"
    "┃■■■■■■■■■■■┃┃       0┃"
    "┃■■■■■■■■■■■┃┗━━━━┛"
    "┃■■■■■■■■■■■┃ ＳＣＯＲＥ "
    "┃■■■■■■■■■■■┃┏━━━━┓"
    "┃■■■■■■■■■■■┃┃ 00000  ┃"
    "┗━━━━━━━━━━━┛┗━━━━┛";
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
    const WORD COLOR_A = FOREGROUND_RED|FOREGROUND_GREEN|
FOREGROUND_INTENSITY; // 运动中的颜色
    const WORD COLOR_B = FOREGROUND_GREEN; // 固定不动的颜色
    const WORD COLOR_C = FOREGROUND_RED|FOREGROUND_GREEN|
FOREGROUND_BLUE; // 空白处的颜色
    bool voice = true;
    int score = 0, level = 0;
    char data[19][11] = { 0 };
    int next = -1;
    int x=4, y=-2, c=-1, z=0; // x坐标,坐标,当前方块,方向
    Console csl; // 定义控制台对象
    void VoiceBeep( void )
    {
    if( voice )
    Beep( 1760, 10 );
    }
    void DrawScoreLevel( void ) // 绘制得分
    {
    char tmp[6];
    sprintf( tmp, "%05d", score );
    csl.OutputStringNoMove( 31, 19, tmp, 5 );
    sprintf( tmp, "%1d", level );
    csl.OutputStringNoMove( 35, 15, tmp, 1 );
    }
    void DrawVoice( void )
    {
    csl.OutputStringNoMove( 35, 3, voice?"Yes":"No " );
    }
    void DrawNext( void ) // 绘制 "next框" 中的图形
    {
    for( int i=0; i<2; ++i )
    {
    for( int j=0; j<4; ++j )
    {
    csl.OutputStringNoMove( 28+j*2, 10+i, bk[next][0][i]
[j]==0?"　":"■", 2 );
    }
    }
    }
void DrawOver( void ) // 游戏结束
    {
    csl.OutputStringNoMove( 28, 10, "ＧＡＭＥ" );
    csl.OutputStringNoMove( 28, 11, "ＯＶＥＲ" );
    }
    void Draw( WORD color )
    {
    for( int i=0; i<4; ++i )
    {
    if( y+i<0 || y+i>= 19 ) continue;
    for( int j=0; j<4; ++j )
    {
    if( bk[c][z][i][j] == 1 )
    {
    csl.SetColor( color );
    csl.GotoXY( 2+x*2+j*2, 1+y+i );
    csl.OutputString( "■", 2 );
    }
    }
    }
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
    void RemoveRow( void ) // 消行
    {
    const char FULLLINE[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1 };
    int linecount = 0;
    for( int i=0; i<19; ++i )
    {
    if( 0 == memcmp( data[i], FULLLINE, 11 ) )
    {
    ++linecount;
    for( int m=0; m<11; ++m )
    {
    for( int n=i; n>1; --n )
    {
    data[n][m] = data[n-1][m];
    csl.SetColor( data[n][m]==1?COLOR_B:COLOR_C );
    csl.GotoXY( 2+m*2, 1+n );
    csl.OutputString( "■", 2 );
    }
    data[0][m] = 0;
    csl.OutputStringNoMove( 2+m*2, 1, "■", 2 );
    }
    }
    }
    char data[19][11] = { 0 };
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
    void MoveTrans( void ) // 逆时针翻转
    {
    if( IsFit( x, y, c, (z+1)%4 ) )
    {
    VoiceBeep();
    Draw( COLOR_C );
    z=(z+1)%4;
    Draw( COLOR_A );
    }
    }
void MoveLeft( void ) // 向左移
    {
    if( IsFit( x-1, y, c, z ) )
    {
    VoiceBeep();
    Draw( COLOR_C );
    --x;
    Draw( COLOR_A );
    }
    }
    void MoveRight( void ) // 向右移
    {
    if( IsFit( x+1, y, c, z ) )
    {
    VoiceBeep();
    Draw( COLOR_C );
    ++x;
    Draw( COLOR_A );
    }
    }
    void MoveDown( void ) // 向下移
    {
    if( IsFit( x, y+1, c, z ) )
    {
    VoiceBeep();
    Draw( COLOR_C );
    ++y;
    Draw( COLOR_A );
    }
    else if( y != -2 ) // 触底
    {
    Draw( COLOR_B );
    for(int i=0; i<4; ++i )
    {
    if( y+i<0 ) continue;
    for( int j=0; j<4; ++j )
    {
    if( bk[c][z][i][j] == 1 )
    {
    data[y+i][x+j] = 1;
    }
    }
    }
    RemoveRow();
    x=4, y=-2, c=next, z=0;
    next = rand()%7;
    DrawNext();
    }
    else // 游戏结束
    {
    DrawOver();
    }
    }
    void MessageDeal( void )
    {
    int cycle = 10 - level;
    for( ; ; )
    {
    for( int i=0; i<cycle; ++i )
    {
    if( _kbhit() )
    {
    switch( _getch() )
    {
    case 'Q':
    case 'q': // 退出
    return;
    break;
    case 'S': // 暂停
    case 's':
    for( ; ; )
    {
    switch( _getch() )
    {
    case 'Q':
    case 'q': // 退出
    return;
    case 'V': // 声音
    case 'v':
    voice = !voice;
    DrawVoice();
    break;
    case 'S':
    case 's':
    goto LABLE_CONTINUE;
    break;
 }
    }
    LABLE_CONTINUE:
    break;
    case 'V': // 声音
    case 'v':
    voice = !voice;
    DrawVoice();
    break;
    case 0xe0: // ←↓→ ↑
    switch( _getch() )
    {
    case 0x4B: // ←
    MoveLeft();
    break;
    case 0x50: // ↓
    MoveDown();
    break;
    case 0x4d: // →
    MoveRight();
    break; // ↑ 变形
    case 0x48:
    MoveTrans();
    default:
    break;
    }
    break;
    default:
    break;
    }
    }
    Sleep( 55 );
    }
    MoveDown();
    }
    }
    int main()
    {
    csl.Open();
    // 设置标题
    csl.SetTitle( "俄罗斯方块 " );
    // 去处光标
    csl.RemoveCursor();
    // 设置窗体尺寸
    csl.SetWindowRect( 38-1, 21-1 );
    // 设置缓冲尺寸
    csl.SetBufSize( 38, 21 );
    // 输出背景字符
    csl.OutputStringNoMove( 0,0,bg );
    // 设置随机种子
    srand( time(0) );
    next = rand()%7;
    DrawNext();
    {
    for( char c = (char)_getch(); c!='B'&&c!='b'; c=(char)
_getch() ) // 开始 Begin
    {
    if( c=='V' || c=='v' ) // 铃声 Vocie
    {
    if( voice )
    {
    voice = false;
    csl.OutputStringNoMove( 35, 3, "No " );
    }
    else
    {
    voice = true;
    csl.OutputStringNoMove( 35, 3, "Yes" );
    }
    }
    }
    }
    x=4, y=-2, c=next, z=0;
    next = rand()%7;
    DrawNext();
    MessageDeal();
    return 0;
    }


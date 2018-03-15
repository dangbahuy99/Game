#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <unistd.h>
#include <time.h>

using namespace std;
char tmp_map[18][32];

char map[18][32] = {
	"ANNNNNNNNNNNNNNNNNNNNNNNNNNNNNB",
	"|          ##          ##   # |",
	"|     ## #          ##    #   |",
	"|## | ## ##### ##   #### ## # |",
	"|   |           ##            |",
	"| | D### |  |           # #   |",
	"| |      |  | ####  #   #  #  |",
	"| | NNNNNN  | #      ## #     |",
	"| |           ####  #     ##  |",
	"| ###### ###         ##       |",
	"|          ######  ####### ###|",
	"|                             |",
	"|# ### ####      ###   #######|",
	"|         #    #    #      #  |",
	"|              #      #  #    |",
	"|   #  ##   ##   ###  ##  ##  |",
	"|     #           #           |",
	"DNNNNNNNNNNNNNNNNNNNNNNNNNNNNNC"
	};

void Color(int x) //mau 
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}


//void ShowMap()
//{
//	for(int i = 0; i < 18; i++)
//	{
//		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
//				printf("%s\n",map[i]);
//	}
//	
//}

void gotoxy( int x, int y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

void ColorMap()
{
	for(int i=0;i<18;i++)
	{
		for(int j=0;j<32;j++)
		{
			if(map[i][j]=='N')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",205);
			}
			if(map[i][j]=='A')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",201);
			}
			if(map[i][j]=='|')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",186);
			}
			if(map[i][j]=='B')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",187);
			}
			if(map[i][j]=='#'||map[i][j]==' ')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << map[i][j];
			}
			if(map[i][j]=='C')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",188);
			}
			if(map[i][j]=='D')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				printf("%c",200);
			}
			
		}
		
		
		
		cout <<endl;
	}
}

class entity {
public:
	entity( int x, int y ){
		this ->x = x;
		this ->y = y;
	}

	void move_x( int p ){
		if( map[y][x+p] == ' ' ) x += p;
	}

	void move_y( int p ){
		if( map[y+p][x] == ' ' ) y += p;
	}

	void move( int p, int q ){
		x += p;
		y += q;
	}

	int get_x(){ return x; }
	int get_y(){ return y; }

	void draw( char p ){
		map[x][y] = p;
		gotoxy( x, y ); printf( "%c", p );
	}

private:
	int x;
	int y;
};

struct walk {
	short walk_count;
	short x;
	short y;
	short back;
};

struct target {
	short x;
	short y;
};

vector<target> walk_queue;

vector<walk> BFSArray;

void AddArray( int x, int y, int wc , int back ){
	if( tmp_map[y][x] == ' ' || tmp_map[y][x] == '.' ){
		tmp_map[y][x] = '#';
		walk tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.walk_count = wc;
		tmp.back = back;
		BFSArray.push_back( tmp );
	}
}

void FindPath( int sx, int sy, int x, int y ){
	memcpy( tmp_map, map, sizeof(map) );
	BFSArray.clear();
	walk tmp;
	tmp.x = sx;
	tmp.y = sy;
	tmp.walk_count = 0;
	tmp.back = -1;
	BFSArray.push_back( tmp );

	int i = 0;
	while( i < BFSArray.size() ){
		if( BFSArray[i].x == x && BFSArray[i].y == y ){
			walk_queue.clear();
			target tmp2;
			while( BFSArray[i].walk_count != 0 ){
				tmp2.x = BFSArray[i].x;
				tmp2.y = BFSArray[i].y;
				walk_queue.push_back( tmp2 );

				i = BFSArray[i].back;
			}

			break;
		}

		AddArray( BFSArray[i].x+1, BFSArray[i].y, BFSArray[i].walk_count+1, i );
		AddArray( BFSArray[i].x-1, BFSArray[i].y, BFSArray[i].walk_count+1, i );
		AddArray( BFSArray[i].x, BFSArray[i].y+1, BFSArray[i].walk_count+1, i );
		AddArray( BFSArray[i].x, BFSArray[i].y-1, BFSArray[i].walk_count+1, i );

		/*
			AddArray( BFSArray[i].x+1, BFSArray[i].y+1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x-1, BFSArray[i].y+1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x+1, BFSArray[i].y+1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x+1, BFSArray[i].y-1, BFSArray[i].walk_count+1, i );

			AddArray( BFSArray[i].x+1, BFSArray[i].y-1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x-1, BFSArray[i].y-1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x-1, BFSArray[i].y+1, BFSArray[i].walk_count+1, i );
			AddArray( BFSArray[i].x-1, BFSArray[i].y-1, BFSArray[i].walk_count+1, i );
		*/
		i++;
	}

	BFSArray.clear();
}


int main()
{
    bool running = true;
	int x = 15; // hero x
	int y = 16; // hero y
	int old_x;
	int old_y;

	int ex = 1;
	int ey = 1;


	int pts = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout <<"\n\n\n\n\n\n\n\n\n                                                  PACMAN\n\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	
                   	cout <<"                                               code by D.B.H-IE3 \n\n\n\n\n\n\n";
    Sleep(2);
	cin.get();
    //system("pause");
	system("cls");
	cout << "\n\n\n\n\n\n\n";
	cout <<"                                              Vui long chon cap do tro choi:\n";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout <<"                                                      K -> Kho\n";
	cout <<"                                                      T -> Trung Binh\n";
	cout <<"                                                      D -> DE\n\n\n\n\n";
	cout <<"                                                     Input : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);

	char diffi;
	int speedmod = 3;

	cin >> diffi;

	if( diffi == 'T' ){
		speedmod = 2;
	}else if( diffi == 'K' ){
		speedmod = 1;
	}

	system("cls");
    //ShowMap();
    ColorMap();

	gotoxy( x, y );
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "O";

	int frame = 0;

	FindPath( ex,ey,x,y );

	while( running ){
		gotoxy( x, y ); cout << " ";

		old_x = x;
		old_y = y;

		if ( GetAsyncKeyState( VK_UP ) ){
			if( map[y-1][x] == '.' ){ y--; pts++; } else
			if( map[y-1][x] == ' ' ) y--;
		}
		if ( GetAsyncKeyState( VK_DOWN ) ){
			if( map[y+1][x] == '.' ){ y++; pts++; } else
			if( map[y+1][x] == ' ' ) y++;
		}
		if ( GetAsyncKeyState( VK_LEFT ) ){
			if( map[y][x-1] == '.' ){ x--; pts++; } else
			if( map[y][x-1] == ' ' ) x--;
		}
		if ( GetAsyncKeyState( VK_RIGHT ) ){
			if( map[y][x+1] == '.' ){ x++; pts++; } else
			if( map[y][x+1] == ' ' ) x++;
		}

		if( old_x != x || old_y != y ){
			FindPath( ex,ey,x,y );
		}

		gotoxy( x,y );
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
		 cout << "O";

		map[ey][ex] = '.';
		gotoxy( ex, ey );
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << ".";

		if( frame%speedmod == 0 && walk_queue.size() != 0 ){
			ex = walk_queue.back().x;
			ey = walk_queue.back().y;
			walk_queue.pop_back();
		}

		gotoxy( ex, ey ); 
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "C";

		if( ex == x && ey == y ){
			break;
		}


		gotoxy( 32, 18 );
		gotoxy( 35, 7 ); 
		cout << " Diem so: ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
		
		cout <<pts;
		Sleep( 100 );
		frame++;
	}
	
	system("cls");
	cout << "\n\n\n\n\n\n\n\n                                      Thua roi =)) Diem cua ban la : " ;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << pts;
	gotoxy( 0, 0);
	
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	cin.get();
	return 0;
}

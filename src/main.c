#include <chess.h>
#include <windows.h>



int main(int argc,const char** argv){
	SetConsoleOutputCP(CP_UTF8);
	DWORD im;
	HANDLE ho=GetStdHandle(-10);
	GetConsoleMode(ho,&im);
	SetConsoleMode(ho,0x80);
	DWORD om;
	ho=GetStdHandle(-11);
	GetConsoleMode(ho,&om);
	SetConsoleMode(ho,7);
	ChessBoard b=init_chess();
	run_console_chess_game(b);
	free_chess(b);
	SetConsoleMode(GetStdHandle(-10),im);
	SetConsoleMode(GetStdHandle(-11),om);
	return 0;
}

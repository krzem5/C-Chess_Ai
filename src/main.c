#include <chess.h>
#include <ai.h>
#include <windows.h>
#include <stdio.h>



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
	CONSOLE_SCREEN_BUFFER_INFO sbi;
	GetConsoleScreenBufferInfo(ho,&sbi);
	// SetConsoleWindowInfo(ho,1,&sbi.srWindow);
	// COORD sz={
	// 	sbi.srWindow.Right+1,
	// 	sbi.srWindow.Bottom+1
	// };
	// SetConsoleScreenBufferSize(ho,sz);
	// SetConsoleWindowInfo(ho,1,&sbi.srWindow);
	ChessBoard b=init_chess();
	run_game(b,default_player_move,default_ai_move);
	free_chess(b);
	SetConsoleMode(GetStdHandle(-10),im);
	SetConsoleMode(ho,om);
	SetConsoleScreenBufferSize(ho,sbi.dwSize);
	SetConsoleWindowInfo(ho,1,&sbi.srWindow);
	return 0;
}

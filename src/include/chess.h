#ifndef __CHESS_H__
#define __CHESS_H__ 1
#include <stdint.h>
#include <limits.h>



#ifndef NULL
#define NULL ((void*)0)
#endif
#define CHESS_BOARD_POS(x,y) (((y)<<3)|(x))
#define CHESS_BOARD_POS_X(p) ((p)&7)
#define CHESS_BOARD_POS_Y(p) ((p)>>3)
#define CHESS_PIECE_EXISTS(f) (!!(f))
#define CHESS_PIECE_GET_COLOR(f) ((f)&1)
#define CHESS_PIECE_GET_TYPE(f) (((f)>>1)&7)
#define CHESS_PIECE_GET_STATE(f) (((f)>>4)&1)
#define CHESS_PIECE_SET_COLOR(c) (c)
#define CHESS_PIECE_SET_TYPE(t) ((t)<<1)
#define CHESS_PIECE_SET_STATE(s) ((s)<<4)
#define CHESS_PIECE_EMPTY 0
#define CHESS_PIECE_COLOR_WHITE 0
#define CHESS_PIECE_COLOR_BLACK 1
#define CHESS_PIECE_TYPE_NONE 0
#define CHESS_PIECE_TYPE_PAWN 1
#define CHESS_PIECE_TYPE_KNIGHT 2
#define CHESS_PIECE_TYPE_BISHOP 3
#define CHESS_PIECE_TYPE_ROOK 4
#define CHESS_PIECE_TYPE_QUEEN 5
#define CHESS_PIECE_TYPE_KING 6
#define CHESS_PIECE_STATE_VISIBLE 0
#define CHESS_PIECE_STATE_NOT_VISIBLE 1



typedef uint8_t ChessPiece;
typedef struct _CHESS_BOARD* ChessBoard;
typedef struct _POSSIBLE_MOVES PossibleMoves;



struct _CHESS_BOARD{
	ChessPiece b[64];
	uint8_t t;
	uint8_t ws;
	uint8_t bs;
};



struct _POSSIBLE_MOVES{
	uint8_t* e;
	uint8_t l;
};



ChessBoard init_chess(void);



PossibleMoves get_moves(ChessBoard b,uint8_t x,uint8_t y);



void make_move(ChessBoard b,uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1);



void run_console_chess_game(ChessBoard b);



void free_chess(ChessBoard b);



#endif

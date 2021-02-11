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
#define CHESS_BOARD_POS_TO_SORT(p) ((((p)&7)<<3)|((p)>>3))
#define CHESS_BOARD_GET_TURN(f) ((f)&1)
#define CHESS_BOARD_GET_STATE(f) ((f)>>1)
#define CHESS_BOARD_SET_TURN(f) ((f))
#define CHESS_BOARD_SET_STATE(f) ((f)<<1)
#define CHESS_PIECE_EXISTS(f) (!!(f))
#define CHESS_PIECE_GET_COLOR(f) ((f)&1)
#define CHESS_PIECE_GET_TYPE(f) (((f)>>1)&7)
#define CHESS_PIECE_GET_STATE(f) ((f)>>4)
#define CHESS_PIECE_SET_COLOR(c) (c)
#define CHESS_PIECE_SET_TYPE(t) ((t)<<1)
#define CHESS_PIECE_SET_STATE(s) ((s)<<4)
#define CHESS_MOVE_GET_X0(m) ((m)&7)
#define CHESS_MOVE_GET_Y0(m) (((m)>>3)&7)
#define CHESS_MOVE_GET_X1(m) (((m)>>6)&7)
#define CHESS_MOVE_GET_Y1(m) ((m)>>9)
#define CHESS_MOVE_GET_POS0(m) ((m)&63)
#define CHESS_MOVE_GET_POS1(m) ((m)>>6)
#define CHESS_MOVE_SET(x0,y0,x1,y1) ((x0)|((y0)<<3)|((x1)<<6)|((y1)<<9))
#define CHESS_MOVE_SET_2POS(p0,p1) ((p0)|((p0)<<6))
#define CHESS_FLIP_COLOR(c) (!(c))
#define CHESS_BOARD_POS_UNKNOWN (0b111111+1)
#define CHESS_BOARD_STATE_PLAYING 0
#define CHESS_BOARD_STATE_DRAW 1
#define CHESS_BOARD_STATE_WIN 2
#define CHESS_PIECE_UNKNOWN 0
#define CHESS_PIECE_COLOR_WHITE 0
#define CHESS_PIECE_COLOR_BLACK 1
#define CHESS_PIECE_TYPE_NONE 0
#define CHESS_PIECE_TYPE_PAWN 1
#define CHESS_PIECE_TYPE_KNIGHT 2
#define CHESS_PIECE_TYPE_BISHOP 3
#define CHESS_PIECE_TYPE_ROOK 4
#define CHESS_PIECE_TYPE_QUEEN 5
#define CHESS_PIECE_TYPE_KING 6
#define CHESS_PIECE_STATE_NOT_MOVED 0
#define CHESS_PIECE_STATE_MOVED 1
#define CHESS_MOVE_UNKNOWN (0b111111111111+1)



typedef uint8_t ChessPiece;
typedef struct _CHESS_BOARD* ChessBoard;
typedef struct _POSSIBLE_MOVES PossibleMoves;
typedef uint16_t Move;
typedef uint8_t (*move_getter_func)(ChessBoard b,Move lm,Move* o);



struct _CHESS_BOARD{
	ChessPiece b[64];
	uint8_t f;
	uint8_t ws;
	uint8_t bs;
	void* w_dt;
	void* b_dt;
};



struct _POSSIBLE_MOVES{
	uint8_t* e;
	uint8_t l;
};



ChessBoard init_chess(void);



void get_moves(ChessPiece* b,uint8_t x,uint8_t y,PossibleMoves* pm);



void make_move(ChessBoard b,uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1);



uint8_t default_player_move(ChessBoard b,Move lm,Move* o);



void run_game(ChessBoard b,move_getter_func wf,move_getter_func bf);



void free_chess(ChessBoard b);



#endif

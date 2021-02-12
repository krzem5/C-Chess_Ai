#include <ai.h>
#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define MINMAX_DEPTH 4
#define FIG_EXP 2



const static float W_PAWN_BOARD_POS[]={0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,1,1,2,3,3,2,1,1,0.5,0.5,1,2.5,2.5,1,0.5,0.5,0,0,0,2,2,0,0,0,0.5,-0.5,-1,0,0,-1,-0.5,0.5,0.5,1,1,-2,-2,1,1,0.5,0,0,0,0,0,0,0,0};
const static float B_PAWN_BOARD_POS[]={0,0,0,0,0,0,0,0,0.5,1,1,-2,-2,1,1,0.5,0.5,-0.5,-1,0,0,-1,-0.5,0.5,0,0,0,2,2,0,0,0,0.5,0.5,1,2.5,2.5,1,0.5,0.5,1,1,2,3,3,2,1,1,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0};
const static float W_KNIGHT_BOARD_POS[]={-5,-4,-3,-3,-3,-3,-4,-5,-4,-2,0,0,0,0,-2,-4,-3,0,1,1.5,1.5,1,0,-3,-3,0.5,1.5,2,2,1.5,0.5,-3,-3,0,1.5,2,2,1.5,0,-3,-3,0.5,1,1.5,1.5,1,0.5,-3,-4,-2,0,0.5,0.5,0,-2,-4,-5,-4,-3,-3,-3,-3,-4,-5};
const static float B_KNIGHT_BOARD_POS[]={-5,-4,-3,-3,-3,-3,-4,-5,-4,-2,0,0.5,0.5,0,-2,-4,-3,0.5,1,1.5,1.5,1,0.5,-3,-3,0,1.5,2,2,1.5,0,-3,-3,0.5,1.5,2,2,1.5,0.5,-3,-3,0,1,1.5,1.5,1,0,-3,-4,-2,0,0,0,0,-2,-4,-5,-4,-3,-3,-3,-3,-4,-5};
const static float B_BISHOP_BOARD_POS[]={-2,-1,-1,-1,-1,-1,-1,-2,-1,0.5,0,0,0,0,0.5,-1,-1,1,1,1,1,1,1,-1,-1,0,1,1,1,1,0,-1,-1,0.5,0.5,1,1,0.5,0.5,-1,-1,0,0.5,1,1,0.5,0,-1,-1,0,0,0,0,0,0,-1,-2,-1,-1,-1,-1,-1,-1,-2};
const static float W_BISHOP_BOARD_POS[]={-2,-1,-1,-1,-1,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,1,1,0.5,0,-1,-1,0.5,0.5,1,1,0.5,0.5,-1,-1,0,1,1,1,1,0,-1,-1,1,1,1,1,1,1,-1,-1,0.5,0,0,0,0,0.5,-1,-2,-1,-1,-1,-1,-1,-1,-2};
const static float B_ROOK_BOARD_POS[]={0,0,0,0.5,0.5,0,0,0,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,0.5,1,1,1,1,1,1,0.5,0,0,0,0,0,0,0,0};
const static float W_ROOK_BOARD_POS[]={0,0,0,0,0,0,0,0,0.5,1,1,1,1,1,1,0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,0,0,0,0.5,0.5,0,0,0};
const static float B_QUEEN_BOARD_POS[]={-2,-1,-1,-0.5,-0.5,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,0.5,0.5,0.5,0,-1,-0.5,0,0.5,0.5,0.5,0.5,0,-0.5,0,0,0.5,0.5,0.5,0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0,-1,-1,0,0.5,0,0,0,0,-1,-2,-1,-1,-0.5,-0.5,-1,-1,-2};
const static float W_QUEEN_BOARD_POS[]={-2,-1,-1,-0.5,-0.5,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,0.5,0.5,0.5,0,-1,-0.5,0,0.5,0.5,0.5,0.5,0,-0.5,0,0,0.5,0.5,0.5,0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0,-1,-1,0,0.5,0,0,0,0,-1,-2,-1,-1,-0.5,-0.5,-1,-1,-2};
const static float B_KING_BOARD_POS[]={2,3,1,0,0,1,3,2,2,2,0,0,0,0,2,2,-1,-2,-2,-2,-2,-2,-2,-1,-2,-3,-3,-4,-4,-3,-3,-2,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3};
const static float W_KING_BOARD_POS[]={-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-2,-3,-3,-4,-4,-3,-3,-2,-1,-2,-2,-2,-2,-2,-2,-1,2,2,0,0,0,0,2,2,2,3,1,0,0,1,3,2};



typedef struct _BOARD_NODE* BoardNode;



struct _BOARD_NODE{
	ChessPiece b[64];
	Move m;
	float v;
	uint8_t cnl;
	BoardNode cn;
};



float _eval_board_piece(uint8_t p,uint8_t pp,uint8_t t){
	uint8_t cl=CHESS_PIECE_GET_COLOR(p);
	float o=0;
	switch (CHESS_PIECE_GET_TYPE(p)){
		case CHESS_PIECE_TYPE_PAWN:
			o+=1*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_PAWN_BOARD_POS:B_PAWN_BOARD_POS)[pp])*FIG_EXP;
			break;
		case CHESS_PIECE_TYPE_KNIGHT:
			o+=3*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_KNIGHT_BOARD_POS:B_KNIGHT_BOARD_POS)[pp])*FIG_EXP;
			break;
		case CHESS_PIECE_TYPE_BISHOP:
			o+=3*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_BISHOP_BOARD_POS:B_BISHOP_BOARD_POS)[pp])*FIG_EXP;
			break;
		case CHESS_PIECE_TYPE_ROOK:
			o+=5*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_ROOK_BOARD_POS:B_ROOK_BOARD_POS)[pp])*FIG_EXP;
			break;
		case CHESS_PIECE_TYPE_QUEEN:
			o+=9*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_QUEEN_BOARD_POS:B_QUEEN_BOARD_POS)[pp])*FIG_EXP;
			break;
		case CHESS_PIECE_TYPE_KING:
			o+=1000*(1+(cl==CHESS_PIECE_COLOR_WHITE?W_KING_BOARD_POS:B_KING_BOARD_POS)[pp])*FIG_EXP;
			break;
	}
	return o*(cl==t?1:-1);
}



BoardNode _create_board_node(uint8_t* b,uint8_t t){
	BoardNode o=malloc(sizeof(struct _BOARD_NODE));
	o->v=0;
	for (uint8_t i=0;i<64;i++){
		if (CHESS_PIECE_EXISTS(o->b[i]=b[i])){
			o->v+=_eval_board_piece(o->b[i],i,t);
		}
	}
	o->m=CHESS_MOVE_UNKNOWN;
	o->cnl=UINT8_MAX;
	o->cn=NULL;
	return o;
}



BoardNode _make_board_node_move(BoardNode b,uint8_t t,Move m){
	b->cnl++;
	b->cn=realloc(b->cn,b->cnl*sizeof(struct _BOARD_NODE));
	BoardNode o=b->cn+b->cnl-1;
	o->v=0;
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			o->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (CHESS_PIECE_EXISTS(o->b[i]=b->b[(i==CHESS_MOVE_GET_POS1(m)?CHESS_MOVE_GET_POS0(m):i)])){
			o->v+=_eval_board_piece(o->b[i],i,t);
		}
	}
	o->m=m;
	o->cnl=UINT8_MAX;
	o->cn=NULL;
	return o;
}



float _minmax(BoardNode n,uint8_t d,float a,float b,uint8_t mx,uint8_t t){
	if (!d||n->v<-100||n->v>100){
		return n->v;
	}
	PossibleMoves pm={
		NULL,
		0
	};
	if (n->cnl==UINT8_MAX){
		n->cnl=0;
		for (uint8_t i=0;i<64;i++){
			ChessPiece p=n->b[i];
			if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==(mx?CHESS_FLIP_COLOR(t):t)){
				get_moves(n->b,CHESS_BOARD_POS_X(i),CHESS_BOARD_POS_Y(i),&pm);
				for (uint8_t j=0;j<pm.l;j++){
					_make_board_node_move(n,t,CHESS_MOVE_SET_2POS(i,*(pm.e+j)));
				}
			}
		}
	}
	if (pm.l){
		free(pm.e);
	}
	if (n->cnl==0){
		return n->v;
	}
	if (mx){
		float o=-INFINITY;
		for (uint8_t i=0;i<n->cnl;i++){
			float nv=_minmax(n->cn+i,d-1,a,b,0,t);
			if (nv>a){
				a=nv;
			}
			if (a>=b){
				break;
			}
			if (nv>o){
				o=nv;
			}
		}
		return o;
	}
	float o=INFINITY;
	for (uint8_t i=0;i<n->cnl;i++){
		float nv=_minmax(n->cn+i,d-1,a,b,1,t);
		if (nv<b){
			b=nv;
		}
		if (b<=a){
			break;
		}
		if (nv<o){
			o=nv;
		}
	}
	return o;
}



BoardNode _free_nodes(BoardNode b,uint8_t i){
	BoardNode o=NULL;
	if (b->cnl!=UINT8_MAX){
		for (uint8_t j=0;j<b->cnl;j++){
			if (j==i){
				o=malloc(sizeof(struct _BOARD_NODE));
				memcpy(o,b->cn+j,sizeof(struct _BOARD_NODE));
			}
			else{
				_free_nodes(b->cn+j,UINT8_MAX);
			}
		}
		if (b->cnl){
			free(b->cn);
		}
	}
	if (i!=UINT8_MAX){
		free(b);
	}
	return o;
}



uint8_t default_ai_move(ChessBoard b,Move lm,Move* o){
	uint8_t t=CHESS_BOARD_GET_TURN(b->f);
	if (CHESS_BOARD_GET_STATE(b->f)!=CHESS_BOARD_STATE_PLAYING){
		_free_nodes((BoardNode)(t==CHESS_PIECE_COLOR_WHITE?b->w_dt:b->b_dt),UINT8_MAX);
		return 0;
	}
	if (t==CHESS_PIECE_COLOR_WHITE){
		if (b->w_dt==NULL){
			b->w_dt=_create_board_node(b->b,t);
		}
	}
	else{
		if (b->b_dt==NULL){
			b->b_dt=_create_board_node(b->b,t);
		}
	}
	BoardNode r=(BoardNode)(t==CHESS_PIECE_COLOR_WHITE?b->w_dt:b->b_dt);
	PossibleMoves pm={
		NULL,
		0
	};
	float bs=-INFINITY;
	uint8_t bi=0;
	if (r->cnl==UINT8_MAX){
		r->cnl=0;
		for (uint8_t i=0;i<64;i++){
			ChessPiece p=r->b[i];
			if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==t){
				get_moves(r->b,CHESS_BOARD_POS_X(i),CHESS_BOARD_POS_Y(i),&pm);
				for (uint8_t j=0;j<pm.l;j++){
					printf("Running MinMax with d = %u and move = {%u, %u} (%u) -> {%u, %u} (%u) => ",MINMAX_DEPTH,i&7,i>>3,CHESS_PIECE_GET_TYPE(r->b[i]),(*(pm.e+j))&7,(*(pm.e+j))>>3,CHESS_PIECE_GET_TYPE(r->b[*(pm.e+j)]));
					fflush(stdout);
					float s=_minmax(_make_board_node_move(r,t,CHESS_MOVE_SET_2POS(i,*(pm.e+j))),MINMAX_DEPTH-1,-INFINITY,INFINITY,1,t);
					printf("%f\n",s);
					if (s>bs){
						bs=s;
						bi=r->cnl-1;
						*o=CHESS_MOVE_SET_2POS(i,*(pm.e+j));
					}
				}
			}
		}
	}
	else{
		uint8_t i=0;
		for (;i<r->cnl;i++){
			BoardNode n=r->cn+i;
			if (n->m==lm){
				break;
			}
			if (i==r->cnl-1){
				printf("Unable to find Player Move ({%u, %u} (%u) -> {%u, %u} (%u))!\n",lm&7,(lm>>3)&7,CHESS_PIECE_GET_TYPE(r->b[lm&63]),(lm>>6)&7,lm>>9,CHESS_PIECE_GET_TYPE(r->b[lm>>6]));
				return 1;
			}
		}
		r=_free_nodes(r,i);
		if (r->cnl==UINT8_MAX){
			r->cnl=0;
			for (i=0;i<64;i++){
				ChessPiece p=r->b[i];
				if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==t){
					get_moves(r->b,CHESS_BOARD_POS_X(i),CHESS_BOARD_POS_Y(i),&pm);
					for (uint8_t j=0;j<pm.l;j++){
						printf("Running MinMax with d = %u and move = {%u, %u} (%u) -> {%u, %u} (%u) => ",MINMAX_DEPTH,i&7,i>>3,CHESS_PIECE_GET_TYPE(r->b[i]),(*(pm.e+j))&7,(*(pm.e+j))>>3,CHESS_PIECE_GET_TYPE(r->b[*(pm.e+j)]));
						fflush(stdout);
						float s=_minmax(_make_board_node_move(r,t,CHESS_MOVE_SET_2POS(i,*(pm.e+j))),MINMAX_DEPTH-1,-INFINITY,INFINITY,1,t);
						printf("%f\n",s);
						if (s>bs){
							bs=s;
							bi=r->cnl-1;
							*o=CHESS_MOVE_SET_2POS(i,*(pm.e+j));
						}
					}
				}
			}
		}
		else{
			for (i=0;i<r->cnl;i++){
				printf("Running MinMax with d = %u and move = {%u, %u} (%u) -> {%u, %u} (%u) => ",MINMAX_DEPTH,((r->cn+i)->m)&7,(((r->cn+i)->m)>>3)&7,CHESS_PIECE_GET_TYPE(r->b[((r->cn+i)->m)&63]),(((r->cn+i)->m)>>6)&7,((r->cn+i)->m)>>9,CHESS_PIECE_GET_TYPE(r->b[((r->cn+i)->m)>>6]));
				fflush(stdout);
				float s=_minmax(r->cn+i,MINMAX_DEPTH-1,-INFINITY,INFINITY,1,t);
				printf("%f\n",s);
				if (s>bs){
					bs=s;
					bi=i;
					*o=(r->cn+i)->m;
				}
			}
		}
	}
	if (pm.l){
		free(pm.e);
	}
	if (bs==-INFINITY){
		return 1;
	}
	if (t==CHESS_PIECE_COLOR_WHITE){
		b->w_dt=_free_nodes(r,bi);
	}
	else{
		b->b_dt=_free_nodes(r,bi);
	}
	return 0;
}

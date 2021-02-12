#include <ai.h>
#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>



#define MINMAX_DEPTH 7



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
typedef struct _CB_ARGS CbArgs;



struct _BOARD_NODE{
	ChessPiece b[64];
	Move m;
	float v;
	uint8_t f;
	uint8_t cnl;
	BoardNode cn;
};



struct _CB_ARGS{
	Move* o;
	float bs;
	uint8_t bi;
	BoardNode r;
};



float _eval_board_piece(uint8_t p,uint8_t pp,uint8_t t){
	uint8_t cl=CHESS_PIECE_GET_COLOR(p);
	float o=0;
	switch (CHESS_PIECE_GET_TYPE(p)){
		case CHESS_PIECE_TYPE_PAWN:
			o+=10+(cl==CHESS_PIECE_COLOR_WHITE?W_PAWN_BOARD_POS:B_PAWN_BOARD_POS)[pp];
			break;
		case CHESS_PIECE_TYPE_KNIGHT:
			o+=32+(cl==CHESS_PIECE_COLOR_WHITE?W_KNIGHT_BOARD_POS:B_KNIGHT_BOARD_POS)[pp];
			break;
		case CHESS_PIECE_TYPE_BISHOP:
			o+=33+(cl==CHESS_PIECE_COLOR_WHITE?W_BISHOP_BOARD_POS:B_BISHOP_BOARD_POS)[pp];
			break;
		case CHESS_PIECE_TYPE_ROOK:
			o+=50+(cl==CHESS_PIECE_COLOR_WHITE?W_ROOK_BOARD_POS:B_ROOK_BOARD_POS)[pp];
			break;
		case CHESS_PIECE_TYPE_QUEEN:
			o+=90+(cl==CHESS_PIECE_COLOR_WHITE?W_QUEEN_BOARD_POS:B_QUEEN_BOARD_POS)[pp];
			break;
		case CHESS_PIECE_TYPE_KING:
			o+=100000+(cl==CHESS_PIECE_COLOR_WHITE?W_KING_BOARD_POS:B_KING_BOARD_POS)[pp];
			break;
	}
	return o*(cl==t?1:-1);
}



void _get_moves_cb(void* dt,Move m){
	BoardNode n=(BoardNode)dt;
	n->cnl++;
	n->cn=realloc(n->cn,n->cnl*sizeof(struct _BOARD_NODE));
	BoardNode nn=n->cn+n->cnl-1;
	nn->v=0;
	nn->f=n->f&1;
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			nn->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (CHESS_PIECE_EXISTS(nn->b[i]=n->b[(i==CHESS_MOVE_GET_POS1(m)?CHESS_MOVE_GET_POS0(m):i)])){
			if (i==CHESS_MOVE_GET_POS1(m)&&CHESS_PIECE_GET_TYPE(n->b[i])==CHESS_PIECE_TYPE_KING){
				nn->f|=2;
			}
			nn->v+=_eval_board_piece(nn->b[i],i,n->f&1);
		}
	}
	nn->m=m;
	nn->cnl=UINT8_MAX;
	nn->cn=NULL;
}



#ifndef NDEBUG
float _minmax(BoardNode n,uint8_t d,float a,float b,uint8_t mx,uint8_t t,uint64_t* tn){
	(*tn)++;
#else
float _minmax(BoardNode n,uint8_t d,float a,float b,uint8_t mx,uint8_t t){
#endif
	if (!d||(n->f&2)){
		return n->v*((float)d+1)/MINMAX_DEPTH;
	}
	if (n->cnl==UINT8_MAX){
		n->cnl=0;
		for (uint8_t i=0;i<64;i++){
			ChessPiece p=n->b[i];
			if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==(mx?t:CHESS_FLIP_COLOR(t))){
				get_moves(n->b,i,_get_moves_cb,n);
			}
		}
	}
	if (n->cnl==0){
		return n->v;
	}
	if (mx){
		float o=-INFINITY;
		for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
			float nv=_minmax(n->cn+i,d-1,a,b,0,t,tn);
#else
			float nv=_minmax(n->cn+i,d-1,a,b,0,t);
#endif
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
		return o+n->v*((float)d+1)/MINMAX_DEPTH;
	}
	float o=INFINITY;
	for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
		float nv=_minmax(n->cn+i,d-1,a,b,1,t,tn);
#else
		float nv=_minmax(n->cn+i,d-1,a,b,1,t);
#endif
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
	return o+n->v*((float)d+1)/MINMAX_DEPTH;
}



BoardNode _free_nodes(BoardNode b,uint8_t i){
	struct _BOARD_NODE o;
	if (b->cnl!=UINT8_MAX){
		for (uint8_t j=0;j<b->cnl;j++){
			if (j==i){
				o=*(b->cn+j);
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
		*b=o;
	}
	return b;
}



void _run_minmax(void* dt,Move m){
	CbArgs* a=(CbArgs*)dt;
	a->r->cnl++;
	a->r->cn=realloc(a->r->cn,a->r->cnl*sizeof(struct _BOARD_NODE));
	BoardNode nn=a->r->cn+a->r->cnl-1;
	nn->v=0;
	nn->f=a->r->f&1;
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			nn->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (CHESS_PIECE_EXISTS(nn->b[i]=a->r->b[(i==CHESS_MOVE_GET_POS1(m)?CHESS_MOVE_GET_POS0(m):i)])){
			if (i==CHESS_MOVE_GET_POS1(m)&&CHESS_PIECE_GET_TYPE(nn->b[i])==CHESS_PIECE_TYPE_KING){
				nn->f|=2;
			}
			nn->v+=_eval_board_piece(nn->b[i],i,nn->f&1);
		}
	}
	nn->m=m;
	nn->cnl=UINT8_MAX;
	nn->cn=NULL;
#ifndef NDEBUG
	printf("Running MinMax with depth = %hhu and move = {%hhu %hhu (%hhu), %hhu %hhu (%hhu)} => ",MINMAX_DEPTH,CHESS_MOVE_GET_X0(m),CHESS_MOVE_GET_Y0(m),CHESS_PIECE_GET_TYPE(a->r->b[CHESS_MOVE_GET_POS0(m)]),CHESS_MOVE_GET_X1(m),CHESS_MOVE_GET_Y1(m),CHESS_PIECE_GET_TYPE(a->r->b[CHESS_MOVE_GET_POS1(m)]));
	fflush(stdout);
	uint64_t tn=0;
	float s=_minmax(nn,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,a->r->f&1,&tn);
	printf("%f (%llu Nodes Visisted)\n",s,tn);
#else
	float s=_minmax(nn,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,a->r->f&1);
#endif
	if (s>a->bs){
		a->bs=s;
		a->bi=a->r->cnl-1;
		*(a->o)=m;
	}
}



uint8_t default_ai_move(ChessBoard b,Move lm,Move* o){
	uint8_t t=CHESS_BOARD_GET_TURN(b->f);
	BoardNode r=(BoardNode)(t==CHESS_PIECE_COLOR_WHITE?b->w_dt:b->b_dt);
	if (CHESS_BOARD_GET_STATE(b->f)!=CHESS_BOARD_STATE_PLAYING){
		if (r!=NULL){
			_free_nodes(r,UINT8_MAX);
		}
		return 0;
	}
	if (r==NULL){
		r=malloc(sizeof(struct _BOARD_NODE));
		r->v=0;
		r->f=t;
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(r->b[i]=b->b[i])){
				r->v+=_eval_board_piece(r->b[i],i,t);
			}
		}
		r->m=CHESS_MOVE_UNKNOWN;
		r->cnl=UINT8_MAX;
		r->cn=NULL;
	}
	CbArgs cb_a={
		o,
		-INFINITY,
		0,
		r
	};
	if (r->cnl==UINT8_MAX){
		r->cnl=0;
		for (uint8_t i=0;i<64;i++){
			ChessPiece p=r->b[i];
			if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==t){
				get_moves(r->b,i,_run_minmax,&cb_a);
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
				printf("Unable to find Player Move ({%u, %u} (%u) -> {%u, %u} (%u))! (This shouldn't happen!)\n",CHESS_MOVE_GET_X0(lm),CHESS_MOVE_GET_Y0(lm),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS0(lm)]),CHESS_MOVE_GET_X1(lm),CHESS_MOVE_GET_Y1(lm),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS1(lm)]));
				return 1;
			}
		}
		r=_free_nodes(r,i);
		if (r->cnl==UINT8_MAX){
			r->cnl=0;
			for (i=0;i<64;i++){
				ChessPiece p=r->b[i];
				if (CHESS_PIECE_EXISTS(p)&&CHESS_PIECE_GET_COLOR(p)==t){
					get_moves(r->b,i,_run_minmax,&cb_a);
				}
			}
		}
		else{
			for (i=0;i<r->cnl;i++){
#ifndef NDEBUG
				printf("Running MinMax with depth = %hhu and move = {%hhu %hhu (%hhu), %hhu %hhu (%hhu)} => ",MINMAX_DEPTH,CHESS_MOVE_GET_X0((r->cn+i)->m),CHESS_MOVE_GET_Y0((r->cn+i)->m),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS0((r->cn+i)->m)]),CHESS_MOVE_GET_X1((r->cn+i)->m),CHESS_MOVE_GET_Y1((r->cn+i)->m),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS1((r->cn+i)->m)]));
				fflush(stdout);
				uint64_t tn=0;
				float s=_minmax(r->cn+i,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,t,&tn);
				printf("%f (%llu Nodes Visisted)\n",s,tn);
#else
				float s=_minmax(r->cn+i,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,t);
#endif
				if (s>cb_a.bs){
					cb_a.bs=s;
					cb_a.bi=i;
					*o=(r->cn+i)->m;
				}
			}
		}
	}
	if (cb_a.bs==-INFINITY){
		return 1;
	}
	if (t==CHESS_PIECE_COLOR_WHITE){
		b->w_dt=_free_nodes(r,cb_a.bi);
	}
	else{
		b->b_dt=_free_nodes(r,cb_a.bi);
	}
	return 0;
}

#include <ai.h>
#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <windows.h>



#define MINMAX_DEPTH 5
#define MAX_THR_MEM 0x4000000
#define GET_DEPTH(f) ((f)&63)
#define GET_MAXIMIZING(f) (((f)>>6)&1)
#define GET_TURN(f) ((f)>>7)
#define SET_DEPTH(d) (d)
#define SET_MAXIMIZING 0x40
#define SET_TURN(t) ((t)<<7)
#define COPY_TURN(f) ((f)&0x80)
#define DECREASE_DEPTH(f) (((f)&63)-1)



const static float W_KING_BOARD_POS[]={-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-2,-3,-3,-4,-4,-3,-3,-2,-1,-2,-2,-2,-2,-2,-2,-1,2,2,0,0,0,0,2,2,2,3,1,0,0,1,3,2};
const static float B_KING_BOARD_POS[]={2,3,1,0,0,1,3,2,2,2,0,0,0,0,2,2,-1,-2,-2,-2,-2,-2,-2,-1,-2,-3,-3,-4,-4,-3,-3,-2,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3,-3,-4,-4,-5,-5,-4,-4,-3};
const static float W_QUEEN_BOARD_POS[]={-2,-1,-1,-0.5,-0.5,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,0.5,0.5,0.5,0,-1,-0.5,0,0.5,0.5,0.5,0.5,0,-0.5,0,0,0.5,0.5,0.5,0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0,-1,-1,0,0.5,0,0,0,0,-1,-2,-1,-1,-0.5,-0.5,-1,-1,-2};
const static float B_QUEEN_BOARD_POS[]={-2,-1,-1,-0.5,-0.5,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,0.5,0.5,0.5,0,-1,-0.5,0,0.5,0.5,0.5,0.5,0,-0.5,0,0,0.5,0.5,0.5,0.5,0,-0.5,-1,0.5,0.5,0.5,0.5,0.5,0,-1,-1,0,0.5,0,0,0,0,-1,-2,-1,-1,-0.5,-0.5,-1,-1,-2};
const static float W_ROOK_BOARD_POS[]={0,0,0,0,0,0,0,0,0.5,1,1,1,1,1,1,0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,0,0,0,0.5,0.5,0,0,0};
const static float B_ROOK_BOARD_POS[]={0,0,0,0.5,0.5,0,0,0,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,-0.5,0,0,0,0,0,0,-0.5,0.5,1,1,1,1,1,1,0.5,0,0,0,0,0,0,0,0};
const static float W_BISHOP_BOARD_POS[]={-2,-1,-1,-1,-1,-1,-1,-2,-1,0,0,0,0,0,0,-1,-1,0,0.5,1,1,0.5,0,-1,-1,0.5,0.5,1,1,0.5,0.5,-1,-1,0,1,1,1,1,0,-1,-1,1,1,1,1,1,1,-1,-1,0.5,0,0,0,0,0.5,-1,-2,-1,-1,-1,-1,-1,-1,-2};
const static float B_BISHOP_BOARD_POS[]={-2,-1,-1,-1,-1,-1,-1,-2,-1,0.5,0,0,0,0,0.5,-1,-1,1,1,1,1,1,1,-1,-1,0,1,1,1,1,0,-1,-1,0.5,0.5,1,1,0.5,0.5,-1,-1,0,0.5,1,1,0.5,0,-1,-1,0,0,0,0,0,0,-1,-2,-1,-1,-1,-1,-1,-1,-2};
const static float W_KNIGHT_BOARD_POS[]={-5,-4,-3,-3,-3,-3,-4,-5,-4,-2,0,0,0,0,-2,-4,-3,0,1,1.5,1.5,1,0,-3,-3,0.5,1.5,2,2,1.5,0.5,-3,-3,0,1.5,2,2,1.5,0,-3,-3,0.5,1,1.5,1.5,1,0.5,-3,-4,-2,0,0.5,0.5,0,-2,-4,-5,-4,-3,-3,-3,-3,-4,-5};
const static float B_KNIGHT_BOARD_POS[]={-5,-4,-3,-3,-3,-3,-4,-5,-4,-2,0,0.5,0.5,0,-2,-4,-3,0.5,1,1.5,1.5,1,0.5,-3,-3,0,1.5,2,2,1.5,0,-3,-3,0.5,1.5,2,2,1.5,0.5,-3,-3,0,1,1.5,1.5,1,0,-3,-4,-2,0,0,0,0,-2,-4,-5,-4,-3,-3,-3,-3,-4,-5};
const static float W_PAWN_BOARD_POS[]={0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,1,1,2,3,3,2,1,1,0.5,0.5,1,2.5,2.5,1,0.5,0.5,0,0,0,2,2,0,0,0,0.5,-0.5,-1,0,0,-1,-0.5,0.5,0.5,1,1,-2,-2,1,1,0.5,0,0,0,0,0,0,0,0};
const static float B_PAWN_BOARD_POS[]={0,0,0,0,0,0,0,0,0.5,1,1,-2,-2,1,1,0.5,0.5,-0.5,-1,0,0,-1,-0.5,0.5,0,0,0,2,2,0,0,0,0.5,0.5,1,2.5,2.5,1,0.5,0.5,1,1,2,3,3,2,1,1,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0};



typedef struct _BOARD_NODE BoardNode;
typedef struct _CB_ARGS CbArgs;
typedef struct _PAGE_LIST PageList;
typedef struct _THREAD_ARGS ThreadArgs;



struct _BOARD_NODE{
	ChessPiece b[64];
	BoardNode* cn;
	float v;
	Move m;
	uint8_t f;
	uint8_t cnl;
};



struct _CB_ARGS{
	Move* o;
	DWORD_PTR pl;
	float bs;
	void* pg;
	uint8_t t;
	ChessPiece* b;
	HANDLE mx;
	uint8_t tll;
	HANDLE* tl;
};



struct _PAGE_LIST{
	void* b;
	uint64_t t;
};



struct _THREAD_ARGS{
	BoardNode* nn;
	CbArgs* a;
	void* pg;
};



uint8_t _s=0;
DWORD_PTR _pl=0;



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
	BoardNode* n=(BoardNode*)dt;
	BoardNode* nn=n->cn+n->cnl;
	n->cnl++;
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
float _minmax(BoardNode* n,uint8_t f,float a,float b,PageList* pl,uint64_t* tn){
	(*tn)++;
#else
float _minmax(BoardNode* n,uint8_t f,float a,float b,PageList* pl){
#endif
	if (!GET_DEPTH(f)||(n->f&2)){
		return n->v;
	}
	if (n->cnl==UINT8_MAX){
		n->cnl=0;
		uint8_t j=0;
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(n->b[i])&&CHESS_PIECE_GET_COLOR(n->b[i])==(GET_MAXIMIZING(f)?GET_TURN(f):CHESS_FLIP_COLOR(GET_TURN(f)))){
				j+=get_moves_c(n->b,i);
			}
		}
		n->cn=(void*)((uint64_t)pl->b+pl->t);
		pl->t+=(uint64_t)j*sizeof(BoardNode);
		if (pl->t>MAX_THR_MEM){
			printf("Not Enought Memory!\n");
			raise(SIGABRT);
		}
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(n->b[i])&&CHESS_PIECE_GET_COLOR(n->b[i])==(GET_MAXIMIZING(f)?GET_TURN(f):CHESS_FLIP_COLOR(GET_TURN(f)))){
				get_moves(n->b,i,_get_moves_cb,n);
				if (n->cnl==j){
					break;
				}
			}
		}
	}
	if (n->cnl==0){
		return n->v;
	}
	if (GET_MAXIMIZING(f)){
		float o=-INFINITY;
		for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
			float nv=_minmax(n->cn+i,DECREASE_DEPTH(f)|COPY_TURN(f),a,b,pl,tn);
#else
			float nv=_minmax(n->cn+i,DECREASE_DEPTH(f)|COPY_TURN(f),a,b,pl);
#endif
			if (nv>o){
				o=nv;
			}
			if (o>a){
				a=o;
			}
			if (a>=b){
				return b;
			}
		}
		return o;
	}
	float o=INFINITY;
	for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
		float nv=_minmax(n->cn+i,DECREASE_DEPTH(f)|SET_MAXIMIZING|COPY_TURN(f),a,b,pl,tn);
#else
		float nv=_minmax(n->cn+i,DECREASE_DEPTH(f)|SET_MAXIMIZING|COPY_TURN(f),a,b,pl);
#endif
		if (nv<o){
			o=nv;
		}
		if (o<b){
			b=o;
		}
		if (b<=a){
			return a;
		}
	}
	return o;
}



BOOL _minmax_thr(LPVOID dt){
	ThreadArgs* ta=(ThreadArgs*)dt;
	PageList pl={
		ta->pg,
		sizeof(BoardNode)+sizeof(ThreadArgs)
	};
#ifndef NDEBUG
	printf("Running minmax(depth = %hhu, move = {%hhu %hhu (%hhu), %hhu %hhu (%hhu)}) => Thread#%lu\n",MINMAX_DEPTH,CHESS_MOVE_GET_X0(ta->nn->m),CHESS_MOVE_GET_Y0(ta->nn->m),CHESS_PIECE_GET_TYPE(ta->a->b[CHESS_MOVE_GET_POS0(ta->nn->m)]),CHESS_MOVE_GET_X1(ta->nn->m),CHESS_MOVE_GET_Y1(ta->nn->m),CHESS_PIECE_GET_TYPE(ta->a->b[CHESS_MOVE_GET_POS1(ta->nn->m)]),GetCurrentThreadId());
	LARGE_INTEGER tf;
	LARGE_INTEGER ts;
	LARGE_INTEGER te;
	QueryPerformanceFrequency(&tf);
	uint64_t tn=0;
	QueryPerformanceCounter(&ts);
	float s=_minmax(ta->nn,SET_DEPTH(MINMAX_DEPTH-1)|SET_TURN(ta->a->t),-INFINITY,INFINITY,&pl,&tn);
	QueryPerformanceCounter(&te);
	printf("Thread#%lu => %.1f (%llu node%c, %.6f seconds, %llu bytes)\n",GetCurrentThreadId(),s,tn,(tn==1?' ':'s'),(te.QuadPart-ts.QuadPart)*1e6/tf.QuadPart*1e-6,pl.t);
#else
	float s=_minmax(ta->nn,SET_DEPTH(MINMAX_DEPTH-1)|SET_TURN(ta->a->t),-INFINITY,INFINITY,&pl);
#endif
	if (WaitForSingleObject(ta->a->mx,INFINITE)!=WAIT_OBJECT_0){
		printf("Unknown WaitForSingleObject Value!\n");
	}
	else{
		if (s>ta->a->bs){
			ta->a->bs=s;
			*(ta->a->o)=ta->nn->m;
		}
		ReleaseMutex(ta->a->mx);
	}
	VirtualFree(pl.b,0,MEM_RELEASE);
	return 0;
}



void _run_minmax(void* dt,Move m){
	CbArgs* a=(CbArgs*)dt;
	void* pg=VirtualAlloc(a->pg,MAX_THR_MEM,MEM_COMMIT|MEM_RESERVE|MEM_LARGE_PAGES,PAGE_READWRITE);
	a->pg=(void*)((uint64_t)pg+MAX_THR_MEM);
	BoardNode* nn=(BoardNode*)pg;
	nn->v=0;
	nn->f=a->t;
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			nn->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (CHESS_PIECE_EXISTS(nn->b[i]=a->b[(i==CHESS_MOVE_GET_POS1(m)?CHESS_MOVE_GET_POS0(m):i)])){
			if (i==CHESS_MOVE_GET_POS1(m)&&CHESS_PIECE_GET_TYPE(nn->b[i])==CHESS_PIECE_TYPE_KING){
				nn->f|=2;
			}
			nn->v+=_eval_board_piece(nn->b[i],i,nn->f&1);
		}
	}
	nn->m=m;
	nn->cnl=UINT8_MAX;
	nn->cn=NULL;
	ThreadArgs* ta=(ThreadArgs*)(void*)((uint64_t)pg+sizeof(BoardNode));
	ta->nn=nn;
	ta->a=a;
	ta->pg=pg;
	a->tll++;
	a->tl=realloc(a->tl,a->tll*sizeof(HANDLE));
	DWORD tmp;
	*(a->tl+a->tll-1)=CreateThread(NULL,0,_minmax_thr,ta,0,&tmp);
	if (!a->pl){
		a->pl=_pl;
	}
	DWORD_PTR p=a->pl^(a->pl&(a->pl-1));
	SetThreadAffinityMask(*(a->tl+a->tll-1),p);
	a->pl&=~p;
}



uint8_t default_ai_move(ChessBoard b,Move lm,Move* o){
	uint8_t t=CHESS_BOARD_GET_TURN(b->f);
	if (CHESS_BOARD_GET_STATE(b->f)!=CHESS_BOARD_STATE_PLAYING){
		return 0;
	}
	if (!_s){
		_s=1;
		LUID lm_p;
		HANDLE tk;
		if (LookupPrivilegeValue(NULL,SE_LOCK_MEMORY_NAME,&lm_p)&&OpenProcessToken(GetCurrentProcess(),TOKEN_QUERY|TOKEN_ADJUST_PRIVILEGES,&tk)){
			DWORD ln=0;
			if (GetTokenInformation(tk,TokenPrivileges,NULL,0,&ln)==TRUE){
				CloseHandle(tk);
			}
			else{
				uint8_t* bf=HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,ln);
				if (bf){
					if (GetTokenInformation(tk,TokenPrivileges,bf,ln,&ln)){
						TOKEN_PRIVILEGES* tk_p=(TOKEN_PRIVILEGES*)bf;
						for (DWORD i=0;i<tk_p->PrivilegeCount;i++){
							if (tk_p->Privileges[i].Luid.LowPart==lm_p.LowPart&&tk_p->Privileges[i].Luid.HighPart==lm_p.HighPart){
								tk_p->Privileges[i].Attributes|=SE_PRIVILEGE_ENABLED;
								AdjustTokenPrivileges(tk,FALSE,tk_p,ln,NULL,NULL);
								break;
							}
						}
					}
					CloseHandle(tk);
					HeapFree(GetProcessHeap(),0,bf);
				}
			}
		}
		if (MAX_THR_MEM<GetLargePageMinimum()){
			printf("MAX_THR_MEM Too Small!\n");
		}
		DWORD_PTR tmp;
		GetProcessAffinityMask(GetCurrentProcess(),&tmp,&_pl);
	}
	CbArgs cb_a={
		o,
		_pl,
		-INFINITY,
		NULL,
		t,
		(ChessPiece*)b->b,
		CreateMutexW(NULL,FALSE,NULL),
		0,
		NULL
	};
	for (uint8_t i=0;i<64;i++){
		if (CHESS_PIECE_EXISTS(b->b[i])&&CHESS_PIECE_GET_COLOR(b->b[i])==t){
			get_moves(b->b,i,_run_minmax,&cb_a);
		}
	}
	WaitForMultipleObjects(cb_a.tll,cb_a.tl,TRUE,INFINITE);
	while (cb_a.tll){
		cb_a.tll--;
		CloseHandle(*(cb_a.tl+cb_a.tll));
	}
	free(cb_a.tl);
	CloseHandle(cb_a.mx);
	return (cb_a.bs==-INFINITY?1:0);
}

#include <ai.h>
#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <signal.h>
#include <windows.h>



#define MINMAX_DEPTH 6
#define MAX_THR_MEM 0x8000
#define NODE_GET_TURN(n) ((n)->f&1)
#define NODE_GET_COMPLETE(n) ((n)->f&2)
#define NODE_GET_WHITE_KING_POS(n) ((n)->f>>2)
#define NODE_GET_BLACK_KING_POS(n) ((n)->f2)
#define NODE_SET_TURN(t) (t)
#define NODE_SET_COMPLETE 2
#define NODE_SET_WHITE_KING_POS(p) ((p)<<2)
#define NODE_SET_BLACK_KING_POS(p) (p)
#define GET_DEPTH(f) ((f)&63)
#define GET_MAXIMIZING(f) ((f)&0x40)
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
	uint16_t f2;
	uint8_t f;
	uint8_t cnl;
};



struct _CB_ARGS{
	Move* o;
	float bs;
	void* pg;
	uint64_t pgl;
	uint64_t pgt;
	uint8_t t;
	ChessPiece* b;
	HANDLE mx;
	uint8_t tll;
	HANDLE* tl;
};



struct _PAGE_LIST{
	void* b;
	uint64_t t;
#ifndef NDEBUG
	uint64_t tm;
	uint64_t mx;
#endif
};



struct _THREAD_ARGS{
	CbArgs* a;
	Move m;
};



uint64_t _pg_sz=0;



#ifndef NDEBUG
void _print_comma(uint64_t v){
	const uint64_t pw[]={10ull,100ull,1000ull,10000ull,100000ull,1000000ull,10000000ull,100000000ull,1000000000ull,10000000000ull,100000000000ull,1000000000000ull,10000000000000ull,100000000000000ull,1000000000000000ull,10000000000000000ull,100000000000000000ull,1000000000000000000ull,10000000000000000000ull};
	uint8_t sz=1;
	while (pw[sz-1]<v+1){
		sz++;
		if (sz==20){
			break;
		}
	}
	uint8_t c=((sz-1)%3)+1;
	while (sz){
		sz--;
		c--;
		putchar(48+(v/pw[sz-1])%10);
		if (!c&&sz){
			c=3;
			putchar(',');
		}
	}
}
#endif



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
	nn->f=NODE_SET_TURN(NODE_GET_TURN(n));
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			nn->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (i==CHESS_MOVE_GET_POS1(m)){
			nn->b[i]=n->b[CHESS_MOVE_GET_POS0(m)];
			if (CHESS_PIECE_GET_TYPE(n->b[i])==CHESS_PIECE_TYPE_KING){
				nn->f|=NODE_SET_COMPLETE;
			}
			else if (CHESS_PIECE_GET_TYPE(nn->b[i])==CHESS_PIECE_TYPE_KING){
				if (CHESS_PIECE_GET_COLOR(nn->b[i])==CHESS_PIECE_COLOR_WHITE){
					nn->f|=NODE_SET_WHITE_KING_POS(i);
				}
				else{
					nn->f2|=NODE_SET_BLACK_KING_POS(i);
				}
			}
			nn->v+=_eval_board_piece(nn->b[i],i,NODE_GET_TURN(n));
		}
		else if (CHESS_PIECE_EXISTS(nn->b[i]=n->b[i])){
			nn->v+=_eval_board_piece(nn->b[i],i,NODE_GET_TURN(n));
			if (CHESS_PIECE_GET_TYPE(nn->b[i])==CHESS_PIECE_TYPE_KING){
				if (CHESS_PIECE_GET_COLOR(nn->b[i])==CHESS_PIECE_COLOR_WHITE){
					nn->f|=NODE_SET_WHITE_KING_POS(i);
				}
				else{
					nn->f2|=NODE_SET_BLACK_KING_POS(i);
				}
			}
		}
	}
	nn->cnl=0;
}



#ifndef NDEBUG
float _minmax(BoardNode* n,uint8_t f,float a,float b,PageList* pl,uint64_t* tn){
	(*tn)++;
#else
float _minmax(BoardNode* n,uint8_t f,float a,float b,PageList* pl){
#endif
	if (!GET_DEPTH(f)||NODE_GET_COMPLETE(n)){
		return n->v;
	}
	uint64_t lt=pl->t;
	n->cn=(void*)((uint64_t)pl->b+pl->t);
	uint8_t cl=(GET_MAXIMIZING(f)?GET_TURN(f):CHESS_FLIP_COLOR(GET_TURN(f)));
	for (uint8_t i=0;i<64;i++){
		if (CHESS_PIECE_EXISTS(n->b[i])&&CHESS_PIECE_GET_COLOR(n->b[i])==cl){
			get_moves(n->b,i,_get_moves_cb,n);
		}
	}
	pl->t+=(uint64_t)n->cnl*sizeof(BoardNode);
#ifndef NDEBUG
	pl->tm+=(uint64_t)n->cnl*sizeof(BoardNode);
	pl->mx=(pl->t>pl->mx?pl->t:pl->mx);
#endif
	if (pl->t>MAX_THR_MEM){
		printf("Not Enought Memory!\n");
		raise(SIGABRT);
	}
	if (GET_MAXIMIZING(f)){
		float o=-INFINITY;
		uint8_t nf=DECREASE_DEPTH(f)|COPY_TURN(f);
		for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
			float nv=_minmax(n->cn+i,nf,a,b,pl,tn);
#else
			float nv=_minmax(n->cn+i,nf,a,b,pl);
#endif
			if (nv>o){
				o=nv;
				if (o>a){
					a=o;
					if (a>=b){
						pl->t=lt;
						return b;
					}
				}
			}
		}
		pl->t=lt;
		return o;
	}
	float o=INFINITY;
	uint8_t nf=DECREASE_DEPTH(f)|SET_MAXIMIZING|COPY_TURN(f);
	for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
		float nv=_minmax(n->cn+i,nf,a,b,pl,tn);
#else
		float nv=_minmax(n->cn+i,nf,a,b,pl);
#endif
		if (nv<o){
			o=nv;
			if (o<b){
				b=o;
				if (b<=a){
					pl->t=lt;
					return a;
				}
			}
		}
	}
	pl->t=lt;
	return o;
}



BOOL _run_minmax(LPVOID dt){
	ThreadArgs* ta=(ThreadArgs*)dt;
	PageList pl={
		(void*)((uint64_t)(void*)ta-sizeof(BoardNode)),
		sizeof(BoardNode)+sizeof(ThreadArgs)
#ifndef NDEBUG
		,0,0
#endif
	};
#ifndef NDEBUG
	if (WaitForSingleObject(ta->a->mx,INFINITE)!=WAIT_OBJECT_0){
		printf("Unknown WaitForSingleObject Value!\n");
	}
	else{
		printf("Checking Move %c%c -> %c%c (%hu -> %hu) => %#.8lx\n",CHESS_MOVE_GET_X0(ta->m)+65,CHESS_MOVE_GET_Y0(ta->m)+49,CHESS_MOVE_GET_X1(ta->m)+65,CHESS_MOVE_GET_Y1(ta->m)+49,CHESS_PIECE_GET_TYPE(ta->a->b[CHESS_MOVE_GET_POS0(ta->m)]),CHESS_PIECE_GET_TYPE(ta->a->b[CHESS_MOVE_GET_POS1(ta->m)]),GetCurrentThreadId());
		ReleaseMutex(ta->a->mx);
	}
	LARGE_INTEGER tf;
	LARGE_INTEGER ts;
	LARGE_INTEGER te;
	QueryPerformanceFrequency(&tf);
	uint64_t tn=0;
	QueryPerformanceCounter(&ts);
	float s=_minmax(pl.b,SET_DEPTH(MINMAX_DEPTH)|SET_TURN(ta->a->t),-INFINITY,INFINITY,&pl,&tn);
	QueryPerformanceCounter(&te);
	if (WaitForSingleObject(ta->a->mx,INFINITE)!=WAIT_OBJECT_0){
		printf("Unknown WaitForSingleObject Value!\n");
	}
	else{
		printf("%#.8lx => %.1f (n = ",GetCurrentThreadId(),s);
		_print_comma(tn);
		printf("; t = %.6f; mem = ",(te.QuadPart-ts.QuadPart)*1e6/tf.QuadPart*1e-6);
		_print_comma(pl.tm);
		printf(" (mx: ");
		_print_comma(pl.mx);
		printf("); n/s = ");
		_print_comma((uint64_t)(tn/((te.QuadPart-ts.QuadPart)*1e6/tf.QuadPart*1e-6)));
		printf(")");
		if (s>ta->a->bs){
			printf(" -> TOP");
		}
		putchar('\n');
#else
	float s=_minmax(pl.b,SET_DEPTH(MINMAX_DEPTH)|SET_TURN(ta->a->t),-INFINITY,INFINITY,&pl);
	if (WaitForSingleObject(ta->a->mx,INFINITE)!=WAIT_OBJECT_0){
		printf("Unknown WaitForSingleObject Value!\n");
	}
	else{
#endif
		if (s>ta->a->bs){
			ta->a->bs=s;
			*(ta->a->o)=ta->m;
		}
		ReleaseMutex(ta->a->mx);
	}
	return 0;
}



void _root_move_cb(void* dt,Move m){
	CbArgs* a=(CbArgs*)dt;
	if (a->pgt+MAX_THR_MEM>a->pgl){
		a->pg=(void*)((uint64_t)VirtualAlloc(a->pg,_pg_sz,MEM_COMMIT|MEM_RESERVE|MEM_LARGE_PAGES,PAGE_READWRITE)+_pg_sz);
		a->pgl+=_pg_sz;
		if (!a->pgt){
			a->pgt=(uint64_t)a->pg-_pg_sz;
		}
	}
	void* pg=(void*)a->pgt;
	a->pgt+=MAX_THR_MEM;
	BoardNode* nn=(BoardNode*)pg;
	nn->v=0;
	nn->f=a->t;
	for (uint8_t i=0;i<64;i++){
		if (i==CHESS_MOVE_GET_POS0(m)){
			nn->b[i]=CHESS_PIECE_UNKNOWN;
		}
		else if (i==CHESS_MOVE_GET_POS1(m)){
			if (CHESS_PIECE_GET_TYPE(a->b[i])==CHESS_PIECE_TYPE_KING){
				nn->f|=NODE_SET_COMPLETE;
			}
			nn->b[i]=a->b[CHESS_MOVE_GET_POS0(m)];
			nn->v+=_eval_board_piece(nn->b[i],i,NODE_GET_TURN(nn));
		}
		else if (CHESS_PIECE_EXISTS(nn->b[i]=a->b[i])){
			nn->v+=_eval_board_piece(nn->b[i],i,NODE_GET_TURN(nn));
		}
	}
	nn->cnl=0;
	ThreadArgs* ta=(ThreadArgs*)(void*)((uint64_t)pg+sizeof(BoardNode));
	ta->a=a;
	ta->m=m;
	a->tll++;
	a->tl=realloc(a->tl,a->tll*sizeof(HANDLE));
	DWORD tmp;
	*(a->tl+a->tll-1)=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)_run_minmax,ta,0,&tmp);
	SetThreadPriority(*(a->tl+a->tll-1),THREAD_PRIORITY_ABOVE_NORMAL);
}



uint8_t default_ai_move(ChessBoard b,Move lm,Move* o){
	uint8_t t=CHESS_BOARD_GET_TURN(b->f);
	if (CHESS_BOARD_GET_STATE(b->f)!=CHESS_BOARD_STATE_PLAYING){
		return 0;
	}
	if (!_pg_sz){
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
		_pg_sz=GetLargePageMinimum();
	}
	CbArgs cb_a={
		o,
		-INFINITY,
		NULL,
		0,
		0,
		t,
		(ChessPiece*)b->b,
		CreateMutexW(NULL,FALSE,NULL),
		0,
		NULL
	};
	SetPriorityClass(GetCurrentProcess(),ABOVE_NORMAL_PRIORITY_CLASS);
	for (uint8_t i=0;i<64;i++){
		if (CHESS_PIECE_EXISTS(b->b[i])&&CHESS_PIECE_GET_COLOR(b->b[i])==t){
			get_moves(b->b,i,_root_move_cb,&cb_a);
		}
	}
	WaitForMultipleObjects(cb_a.tll,cb_a.tl,TRUE,INFINITE);
	SetPriorityClass(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);
	while (cb_a.pgl){
		cb_a.pgl-=_pg_sz;
		cb_a.pg=(void*)((uint64_t)cb_a.pg-_pg_sz);
		VirtualFree(cb_a.pg,0,MEM_RELEASE);
	}
	while (cb_a.tll){
		cb_a.tll--;
		CloseHandle(*(cb_a.tl+cb_a.tll));
	}
	free(cb_a.tl);
	CloseHandle(cb_a.mx);
	return (cb_a.bs==-INFINITY?1:0);
}

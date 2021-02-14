#include <ai.h>
#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>



#define MINMAX_DEPTH 5
#define MEM_HEADER_HAS_NEXT(h) ((uint8_t)(((h)->a)>>63))
#define MEM_HEADER_GET_PREV(h) ((MemHeader*)(((h)->a)&0x7fffffffffffffff))
#define MEM_HEADER_GET_NEXT(h) ((MemHeader*)(void*)((uint64_t)(void*)h+(((h)->b)&0x7fffffffffffffff)+sizeof(MemHeader)))
#define MEM_HEADER_GET_SIZE(h) (((h)->b)&0x7fffffffffffffff)
#define MEM_HEADER_GET_FREE(h) ((uint8_t)(((h)->b)>>63))
#define MEM_HEADER_SET_PREV(p) ((uint64_t)p)
#define MEM_HEADER_SET_NEXT 0x8000000000000000
#define MEM_HEADER_SET_SIZE(l) ((uint64_t)l)
#define MEM_HEADER_SET_FREE 0x8000000000000000
#define MEM_HEADER_COPY_NEXT(h) (((h)->a)&0x8000000000000000)



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



typedef struct _BOARD_NODE* BoardNode;
typedef struct _CB_ARGS CbArgs;
typedef struct _MEM_HEADER MemHeader;



struct _BOARD_NODE{
	ChessPiece b[64];
	BoardNode cn;
	float v;
	Move m;
	uint8_t f;
	uint8_t cnl;
};



struct _CB_ARGS{
	Move* o;
	float bs;
	BoardNode bn;
	BoardNode r;
};



struct _MEM_HEADER{
	uint64_t a;
	uint64_t b;
};



uint16_t _ptr_ll=0;
void** _ptr_l=NULL;
MemHeader* _mem_h;
MemHeader* _lf;
size_t _pg_sz=0;



void _free_node_list(void* p){
	MemHeader* h=(MemHeader*)(void*)((uint64_t)p-sizeof(MemHeader));
	if (MEM_HEADER_GET_PREV(h)&&MEM_HEADER_GET_FREE(MEM_HEADER_GET_PREV(h))){
		MemHeader* ph=MEM_HEADER_GET_PREV(h);
		ph->a=MEM_HEADER_SET_PREV(MEM_HEADER_GET_PREV(ph))|MEM_HEADER_COPY_NEXT(h);
		ph->b=MEM_HEADER_SET_SIZE(MEM_HEADER_GET_SIZE(ph)+h->b+sizeof(MemHeader));
		h=ph;
	}
	if (MEM_HEADER_HAS_NEXT(h)&&MEM_HEADER_GET_FREE(MEM_HEADER_GET_NEXT(h))){
		MemHeader* nh=MEM_HEADER_GET_NEXT(h);
		h->a=MEM_HEADER_SET_PREV(MEM_HEADER_GET_PREV(h))|MEM_HEADER_COPY_NEXT(nh);
		h->b=MEM_HEADER_SET_SIZE(h->b+MEM_HEADER_GET_SIZE(nh)+sizeof(MemHeader));
	}
	h->b|=MEM_HEADER_SET_FREE;
	if (h<_lf){
		_lf=h;
	}
}



void* _alloc_node_list(uint64_t l){
	MemHeader* h=_lf;
	while (!MEM_HEADER_GET_FREE(h)||MEM_HEADER_GET_SIZE(h)<l+sizeof(MemHeader)){
		if (!MEM_HEADER_HAS_NEXT(h)){
			_ptr_ll++;
			_ptr_l=realloc(_ptr_l,_ptr_ll*sizeof(void*));
			*(_ptr_l+_ptr_ll-1)=VirtualAlloc((void*)((uint64_t)*_ptr_l+_pg_sz*(_ptr_ll-1)),_pg_sz,MEM_COMMIT|MEM_RESERVE|MEM_LARGE_PAGES,PAGE_READWRITE);
			if (MEM_HEADER_GET_FREE(h)){
				h->b=MEM_HEADER_SET_SIZE(MEM_HEADER_GET_SIZE(h)+_pg_sz)|MEM_HEADER_SET_FREE;
			}
			else{
				MemHeader* nh=(MemHeader*)*(_ptr_l+_ptr_ll-1);
				nh->a=MEM_HEADER_SET_PREV(h);
				nh->b=MEM_HEADER_SET_SIZE(_pg_sz-sizeof(MemHeader))|MEM_HEADER_SET_FREE;
				h->a|=MEM_HEADER_SET_NEXT;
				h=nh;
			}
			continue;
		}
		h=MEM_HEADER_GET_NEXT(h);
	}
	void* o=(void*)((uint64_t)(void*)h+sizeof(MemHeader));
	MemHeader* nh=(MemHeader*)(void*)((uint64_t)(void*)h+l+sizeof(MemHeader));
	nh->a=MEM_HEADER_SET_PREV(h)|MEM_HEADER_COPY_NEXT(h);
	nh->b=MEM_HEADER_SET_SIZE(MEM_HEADER_GET_SIZE(h)-l-sizeof(MemHeader))|MEM_HEADER_SET_FREE;
	h->a|=MEM_HEADER_SET_NEXT;
	h->b=MEM_HEADER_SET_SIZE(l);
	if (_lf==h){
		_lf=nh;
	}
	if (MEM_HEADER_HAS_NEXT(nh)){
		MemHeader* nnh=MEM_HEADER_GET_NEXT(nh);
		nnh->a=MEM_HEADER_SET_PREV(nh)|MEM_HEADER_COPY_NEXT(nnh);
	}
	return o;
}



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
	BoardNode nn=n->cn+n->cnl;
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
float _minmax(BoardNode n,uint8_t d,float a,float b,uint8_t mx,uint8_t t,uint64_t* tn){
	(*tn)++;
#else
float _minmax(BoardNode n,uint8_t d,float a,float b,uint8_t mx,uint8_t t){
#endif
	if (!d||(n->f&2)){
		return n->v;
	}
	if (n->cnl==UINT8_MAX){
		n->cnl=0;
		uint8_t j=0;
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(n->b[i])&&CHESS_PIECE_GET_COLOR(n->b[i])==(mx?t:CHESS_FLIP_COLOR(t))){
				j+=get_moves_c(n->b,i);
			}
		}
		n->cn=_alloc_node_list(j*sizeof(struct _BOARD_NODE));
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(n->b[i])&&CHESS_PIECE_GET_COLOR(n->b[i])==(mx?t:CHESS_FLIP_COLOR(t))){
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
	if (mx){
		float o=-INFINITY;
		for (uint8_t i=0;i<n->cnl;i++){
#ifndef NDEBUG
			float nv=_minmax(n->cn+i,d-1,a,b,0,t,tn);
#else
			float nv=_minmax(n->cn+i,d-1,a,b,0,t);
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
		float nv=_minmax(n->cn+i,d-1,a,b,1,t,tn);
#else
		float nv=_minmax(n->cn+i,d-1,a,b,1,t);
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



void _free_nodes(BoardNode b){
	if (b->cnl!=UINT8_MAX){
		for (uint8_t i=0;i<b->cnl;i++){
			_free_nodes(b->cn+i);
		}
		if (b->cnl){
			_free_node_list(b->cn);
		}
	}
}



void _run_minmax(void* dt,Move m){
	CbArgs* a=(CbArgs*)dt;
	BoardNode nn=malloc(sizeof(struct _BOARD_NODE));
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
	printf("Running minmax(depth = %hhu, move = {%hhu %hhu (%hhu), %hhu %hhu (%hhu)}) => ",MINMAX_DEPTH,CHESS_MOVE_GET_X0(m),CHESS_MOVE_GET_Y0(m),CHESS_PIECE_GET_TYPE(a->r->b[CHESS_MOVE_GET_POS0(m)]),CHESS_MOVE_GET_X1(m),CHESS_MOVE_GET_Y1(m),CHESS_PIECE_GET_TYPE(a->r->b[CHESS_MOVE_GET_POS1(m)]));
	fflush(stdout);
	LARGE_INTEGER tf;
	LARGE_INTEGER ts;
	LARGE_INTEGER te;
	QueryPerformanceFrequency(&tf);
	uint64_t tn=0;
	QueryPerformanceCounter(&ts);
	float s=_minmax(nn,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,a->r->f&1,&tn);
	QueryPerformanceCounter(&te);
	printf("%.1f (%llu node%c, %.6f seconds)\n",s,tn,(tn==1?' ':'s'),(te.QuadPart-ts.QuadPart)*1e6/tf.QuadPart*1e-6);
#else
	float s=_minmax(nn,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,a->r->f&1);
#endif
	if (s>a->bs){
		if (a->bs!=-INFINITY){
			_free_nodes(a->bn);
		}
		a->bs=s;
		*a->bn=*nn;
		*(a->o)=nn->m;
	}
	else{
		_free_nodes(nn);
	}
	free(nn);
}



uint8_t default_ai_move(ChessBoard b,Move lm,Move* o){
	uint8_t t=CHESS_BOARD_GET_TURN(b->f);
	BoardNode r=(BoardNode)(t==CHESS_PIECE_COLOR_WHITE?b->w_dt:b->b_dt);
	if (CHESS_BOARD_GET_STATE(b->f)!=CHESS_BOARD_STATE_PLAYING){
		if (r!=NULL){
			free(r);
		}
		while (_ptr_ll){
			_ptr_ll--;
			VirtualFree(*((void**)_ptr_l+_ptr_ll),0,MEM_RELEASE);
		}
		return 0;
	}
	if (!_ptr_ll){
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
		_ptr_ll=1;
		_ptr_l=malloc(sizeof(void*));
		_pg_sz=GetLargePageMinimum();
		*_ptr_l=VirtualAlloc(NULL,_pg_sz,MEM_COMMIT|MEM_RESERVE|MEM_LARGE_PAGES,PAGE_READWRITE);
		_mem_h=*_ptr_l;
		_mem_h->a=MEM_HEADER_SET_PREV(NULL);
		_mem_h->b=MEM_HEADER_SET_SIZE(_pg_sz-sizeof(MemHeader))|MEM_HEADER_SET_FREE;
		_lf=_mem_h;
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
		malloc(sizeof(struct _BOARD_NODE)),
		r
	};
	if (r->cnl==UINT8_MAX){
		for (uint8_t i=0;i<64;i++){
			if (CHESS_PIECE_EXISTS(r->b[i])&&CHESS_PIECE_GET_COLOR(r->b[i])==t){
				get_moves(r->b,i,_run_minmax,&cb_a);
			}
		}
	}
	else{
		uint8_t i=0;
		for (;i<r->cnl;i++){
			if ((r->cn+i)->m==lm){
				break;
			}
			if (i==r->cnl-1){
				printf("Unable to find Player Move ({%u, %u} (%u) -> {%u, %u} (%u))! (This shouldn't happen!)\n",CHESS_MOVE_GET_X0(lm),CHESS_MOVE_GET_Y0(lm),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS0(lm)]),CHESS_MOVE_GET_X1(lm),CHESS_MOVE_GET_Y1(lm),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS1(lm)]));
				return 1;
			}
		}
		struct _BOARD_NODE nr;
		if (r->cnl!=UINT8_MAX){
			for (uint8_t j=0;j<r->cnl;j++){
				if (j==i){
					nr=*(r->cn+j);
				}
				else{
					_free_nodes(r->cn+j);
				}
			}
			if (r->cnl){
				_free_node_list(r->cn);
			}
		}
		*r=nr;
		if (r->cnl==UINT8_MAX){
			for (i=0;i<64;i++){
				if (CHESS_PIECE_EXISTS(r->b[i])&&CHESS_PIECE_GET_COLOR(r->b[i])==t){
					get_moves(r->b,i,_run_minmax,&cb_a);
				}
			}
		}
		else{
			for (i=0;i<r->cnl;i++){
#ifndef NDEBUG
				printf("Running minmax(depth = %hhu, move = {%hhu %hhu (%hhu), %hhu %hhu (%hhu)}) => ",MINMAX_DEPTH,CHESS_MOVE_GET_X0((r->cn+i)->m),CHESS_MOVE_GET_Y0((r->cn+i)->m),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS0((r->cn+i)->m)]),CHESS_MOVE_GET_X1((r->cn+i)->m),CHESS_MOVE_GET_Y1((r->cn+i)->m),CHESS_PIECE_GET_TYPE(r->b[CHESS_MOVE_GET_POS1((r->cn+i)->m)]));
				fflush(stdout);
				LARGE_INTEGER tf;
				LARGE_INTEGER ts;
				LARGE_INTEGER te;
				QueryPerformanceFrequency(&tf);
				uint64_t tn=0;
				QueryPerformanceCounter(&ts);
				float s=_minmax(r->cn+i,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,t,&tn);
				QueryPerformanceCounter(&te);
				printf("%.1f (%llu node%c, %.6f seconds)\n",s,tn,(tn==1?' ':'s'),(te.QuadPart-ts.QuadPart)*1e6/tf.QuadPart*1e-6);
#else
				float s=_minmax(nn,MINMAX_DEPTH-1,-INFINITY,INFINITY,0,t);
#endif
				if (s>cb_a.bs){
					if (cb_a.bs!=-INFINITY){
						_free_nodes(cb_a.bn);
					}
					cb_a.bs=s;
					*(cb_a.bn)=*(r->cn+i);
					*o=(r->cn+i)->m;
				}
				else{
					_free_nodes(r->cn+i);
				}
			}
			if (r->cnl){
				_free_node_list(r->cn);
			}
		}
	}
	free(r);
	r=cb_a.bn;
	if (cb_a.bs==-INFINITY){
		free(cb_a.bn);
		return 1;
	}
	if (t==CHESS_PIECE_COLOR_WHITE){
		b->w_dt=r;
	}
	else{
		b->b_dt=r;
	}
	return 0;
}

#include <chess.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>



ChessBoard init_chess(void){
	ChessBoard o=malloc(sizeof(struct _CHESS_BOARD));
	memset(o->b,CHESS_PIECE_EMPTY,64*sizeof(ChessPiece));
	o->b[CHESS_BOARD_POS(0,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_ROOK)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(1,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KNIGHT)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(2,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_BISHOP)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(3,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_QUEEN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(4,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KING)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(5,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_BISHOP)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(6,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KNIGHT)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(7,0)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_ROOK)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(0,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(1,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(2,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(3,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(4,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(5,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(6,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(7,1)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_BLACK)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(0,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(1,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(2,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(3,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(4,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(5,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(6,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(7,6)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_PAWN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(0,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_ROOK)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(1,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KNIGHT)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(2,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_BISHOP)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(3,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_QUEEN)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(4,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KING)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(5,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_BISHOP)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(6,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_KNIGHT)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->b[CHESS_BOARD_POS(7,7)]=CHESS_PIECE_SET_COLOR(CHESS_PIECE_COLOR_WHITE)|CHESS_PIECE_SET_TYPE(CHESS_PIECE_TYPE_ROOK)|CHESS_PIECE_SET_STATE(CHESS_PIECE_STATE_VISIBLE);
	o->t=CHESS_PIECE_COLOR_WHITE;
	o->ws=0;
	o->bs=0;
	return o;
}



PossibleMoves get_moves(ChessBoard b,uint8_t x,uint8_t y){
	PossibleMoves o={
		NULL,
		0
	};
	ChessPiece f=b->b[CHESS_BOARD_POS(x,y)];
	if (!CHESS_PIECE_EXISTS(f)){
		return o;
	}
	uint8_t cl=CHESS_PIECE_GET_COLOR(f);
	switch (CHESS_PIECE_GET_TYPE(f)){
		case CHESS_PIECE_TYPE_PAWN:
			if (CHESS_PIECE_GET_COLOR(f)==CHESS_PIECE_COLOR_WHITE){
				if (!CHESS_PIECE_EXISTS(b->b[CHESS_BOARD_POS(x,y-1)])){
					o.l++;
					o.e=realloc(o.e,o.l*sizeof(uint8_t));
					*(o.e+o.l-1)=CHESS_BOARD_POS(x,y-1);
				}
				if (y==6&&!CHESS_PIECE_EXISTS(b->b[CHESS_BOARD_POS(x,y-2)])){
					o.l++;
					o.e=realloc(o.e,o.l*sizeof(uint8_t));
					*(o.e+o.l-1)=CHESS_BOARD_POS(x,y-2);
				}
				if (x){
					ChessPiece t=b->b[CHESS_BOARD_POS(x-1,y-1)];
					if (CHESS_PIECE_EXISTS(t)&&CHESS_PIECE_GET_COLOR(t)!=cl){
						o.l++;
						o.e=realloc(o.e,o.l*sizeof(uint8_t));
						*(o.e+o.l-1)=CHESS_BOARD_POS(x-1,y-1);
					}
				}
				if (x<7){
					ChessPiece t=b->b[CHESS_BOARD_POS(x+1,y-1)];
					if (CHESS_PIECE_EXISTS(t)&&CHESS_PIECE_GET_COLOR(t)!=cl){
						o.l++;
						o.e=realloc(o.e,o.l*sizeof(uint8_t));
						*(o.e+o.l-1)=CHESS_BOARD_POS(x+1,y-1);
					}
				}
			}
			else{
				if (!CHESS_PIECE_EXISTS(b->b[CHESS_BOARD_POS(x,y+1)])){
					o.l++;
					o.e=realloc(o.e,o.l*sizeof(uint8_t));
					*(o.e+o.l-1)=CHESS_BOARD_POS(x,y+1);
				}
				if (y==1&&!CHESS_PIECE_EXISTS(b->b[CHESS_BOARD_POS(x,y+2)])){
					o.l++;
					o.e=realloc(o.e,o.l*sizeof(uint8_t));
					*(o.e+o.l-1)=CHESS_BOARD_POS(x,y+2);
				}
				if (x){
					ChessPiece t=b->b[CHESS_BOARD_POS(x-1,y+1)];
					if (CHESS_PIECE_EXISTS(t)&&CHESS_PIECE_GET_COLOR(t)!=cl){
						o.l++;
						o.e=realloc(o.e,o.l*sizeof(uint8_t));
						*(o.e+o.l-1)=CHESS_BOARD_POS(x-1,y+1);
					}
				}
				if (x<7){
					ChessPiece t=b->b[CHESS_BOARD_POS(x+1,y+1)];
					if (CHESS_PIECE_EXISTS(t)&&CHESS_PIECE_GET_COLOR(t)!=cl){
						o.l++;
						o.e=realloc(o.e,o.l*sizeof(uint8_t));
						*(o.e+o.l-1)=CHESS_BOARD_POS(x+1,y+1);
					}
				}
			}
			break;
		case CHESS_PIECE_TYPE_KNIGHT:
			break;
		case CHESS_PIECE_TYPE_BISHOP:
			break;
		case CHESS_PIECE_TYPE_ROOK:
			break;
		case CHESS_PIECE_TYPE_QUEEN:
			break;
		case CHESS_PIECE_TYPE_KING:
			break;
	}
	return o;
}



void make_move(ChessBoard b,uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1){
	const uint8_t pp[]={0,1,3,3,5,9,100};
	ChessPiece t=b->b[CHESS_BOARD_POS(x1,y1)];
	if (CHESS_PIECE_EXISTS(t)){
		printf("\x1b[0m\nPiece: %hhu (%hhu points)\n",CHESS_PIECE_GET_TYPE(t),pp[CHESS_PIECE_GET_TYPE(t)]);
		if (b->t==CHESS_PIECE_COLOR_WHITE){
			b->ws+=pp[CHESS_PIECE_GET_TYPE(t)];
		}
		else{
			b->bs+=pp[CHESS_PIECE_GET_TYPE(t)];
		}
	}
	b->b[CHESS_BOARD_POS(x1,y1)]=b->b[CHESS_BOARD_POS(x0,y0)];
	b->b[CHESS_BOARD_POS(x0,y0)]=CHESS_PIECE_EMPTY;
	b->t=!b->t;
}



void run_console_chess_game(ChessBoard b){
	const char pl0[]={' ','P','K','B','R','Q','K'};
	const char pl1[]={' ',' ','n',' ',' ',' ',' '};
	uint8_t x0=UINT8_MAX;
	uint8_t y0=UINT8_MAX;
	uint8_t x1=UINT8_MAX;
	uint8_t y1=UINT8_MAX;
	uint8_t lx0=UINT8_MAX;
	uint8_t ly0=UINT8_MAX;
	uint8_t lx1=UINT8_MAX;
	uint8_t ly1=UINT8_MAX;
	uint8_t e=0;
	PossibleMoves pm={
		NULL,
		0
	};
	uint8_t vm=0;
	printf("\x1b[?25l");
	while (1){
		printf("\x1b[0;0H\x1b[2J\x1b[48;2;40;40;40m\x1b[38;2;29;68;225m  A B C D E F G H   \n");
		for (uint8_t i=0;i<8;i++){
			printf("\x1b[38;2;25;230;100m%c ",i+48);
			for (uint8_t j=0;j<8;j++){
				ChessPiece f=b->b[CHESS_BOARD_POS(j,i)];
				uint8_t sm=(i==y0&&j==x0&&CHESS_PIECE_EXISTS(f)&&CHESS_PIECE_GET_COLOR(f)==b->t&&pm.l?1:0);
				if (!sm){
					for (uint8_t k=0;k<pm.l;k++){
						if (CHESS_BOARD_POS(j,i)==*(pm.e+k)){
							sm=1;
							break;
						}
					}
				}
				if (((i*9+j)%2)){
					if (sm){
						printf("\x1b[48;2;105;105;105m");
					}
					else{
						printf("\x1b[48;2;181;136;99m");
					}
				}
				else{
					if (sm){
						printf("\x1b[48;2;169;169;169m");
					}
					else{
						printf("\x1b[48;2;240;217;181m");
					}
				}
				if (CHESS_PIECE_GET_COLOR(f)==CHESS_PIECE_COLOR_WHITE){
					printf("\x1b[38;2;255;255;255m");
				}
				else{
					printf("\x1b[38;2;0;0;0m");
				}
				putchar(pl0[CHESS_PIECE_GET_TYPE(f)]);
				putchar(pl1[CHESS_PIECE_GET_TYPE(f)]);
			}
			printf("\x1b[48;2;40;40;40m  \n");
		}
		printf("                    \n");
		printf("\x1b[38;2;230;230;230m\x1b[49m\nFrom: ");
		if (!e){
			printf("\x1b[48;2;30;30;30m");
		}
		if (x0==UINT8_MAX){
			printf("\x1b[38;2;50;50;50m<Row>");
		}
		else{
			printf("\x1b[38;2;29;68;225m%c",x0+65);
		}
		if (y0==UINT8_MAX){
			printf("\x1b[38;2;50;50;50m<Col>");
		}
		else{
			printf("\x1b[38;2;25;230;100m%c",y0+49);
		}
		if (!e){
			printf("\x1b[49m");
		}
		if (x0!=UINT8_MAX&&y0!=UINT8_MAX){
			ChessPiece f=b->b[CHESS_BOARD_POS(x0,y0)];
			if (!CHESS_PIECE_EXISTS(f)){
				printf("\n\x1b[38;2;230;65;25mNo Figure at \x1b[38;2;29;68;225m%c\x1b[38;2;25;230;100m%c\x1b[38;2;230;65;25m!",x0+65,y0+49);
			}
			else if (CHESS_PIECE_GET_COLOR(f)!=b->t){
				printf("\n\x1b[38;2;230;65;25mFigure at \x1b[38;2;29;68;225m%c\x1b[38;2;25;230;100m%c\x1b[38;2;230;65;25m isn't yours!",x0+65,y0+49);
			}
			else if (!pm.l){
				printf("\n\x1b[38;2;230;65;25mFigure at \x1b[38;2;29;68;225m%c\x1b[38;2;25;230;100m%c\x1b[38;2;230;65;25m has no avaible moves!",x0+65,y0+49);
			}
			else{
				printf("\x1b[38;2;230;230;230m\nTo: ");
				if (e==1){
					printf("\x1b[48;2;30;30;30m");
				}
				if (x1==UINT8_MAX){
					printf("\x1b[38;2;50;50;50m<Row>");
				}
				else{
					printf("\x1b[38;2;29;68;225m%c",x1+65);
				}
				if (y1==UINT8_MAX){
					printf("\x1b[38;2;50;50;50m<Col>\n");
				}
				else{
					printf("\x1b[38;2;25;230;100m%c\n",y1+49);
				}
				if (e==1){
					printf("\x1b[49m");
				}
				for (uint8_t i=0;i<pm.l;i++){
					printf("\x1b[38;2;14;32;108m%c\x1b[38;2;12;110;46m%c",CHESS_BOARD_POS_X(*(pm.e+i))+65,CHESS_BOARD_POS_Y(*(pm.e+i))+49);
					if (i<pm.l-1){
						printf("\x1b[38;2;53;53;53m, ");
					}
				}
				if (!vm&&x1!=UINT8_MAX&&y1!=UINT8_MAX){
					printf("\n\x1b[38;2;230;65;25mMove from \x1b[38;2;29;68;225m%c\x1b[38;2;25;230;100m%c\x1b[38;2;230;65;25m to \x1b[38;2;29;68;225m%c\x1b[38;2;25;230;100m%c\x1b[38;2;230;65;25m isn't valid!",x0+65,y0+49,x1+65,y1+49);
				}
			}
		}
		printf("\x1b[0m");
		int c=_getch();
		uint8_t u_m=0;
		if (c==3){
			break;
		}
		else if (c==9){
			ChessPiece f=b->b[CHESS_BOARD_POS(x0,y0)];
			if (CHESS_PIECE_EXISTS(f)&&CHESS_PIECE_GET_COLOR(f)==b->t){
				if (!e){
					e=1;
				}
				else if (e==1){
					e=0;
				}
			}
		}
		else if (c==13){
			if (e==1&&vm){
				make_move(b,x0,y0,x1,y1);
				x0=UINT8_MAX;
				y0=UINT8_MAX;
				x1=UINT8_MAX;
				y1=UINT8_MAX;
				lx0=UINT8_MAX;
				ly0=UINT8_MAX;
				lx1=UINT8_MAX;
				ly1=UINT8_MAX;
				e=0;
				if (pm.l){
					free(pm.e);
					pm.l=0;
				}
				vm=0;
			}
		}
		else if (c>48&&c<57){
			if (!e){
				y0=c-49;
				u_m=1;
			}
			else if (e==1){
				y1=c-49;
				u_m=1;
			}
		}
		else if (c>64&&c<73){
			if (!e){
				x0=c-65;
				u_m=1;
			}
			else if (e==1){
				x1=c-65;
				u_m=1;
			}
		}
		else if (c>96&&c<105){
			if (!e){
				x0=c-97;
				u_m=1;
			}
			else if (e==1){
				x1=c-97;
				u_m=1;
			}
		}
		if (u_m&&x0!=UINT8_MAX&&y0!=UINT8_MAX&&(x0!=lx0||y0!=ly0)){
			lx0=x0;
			ly0=y0;
			x1=UINT8_MAX;
			y1=UINT8_MAX;
			lx1=UINT8_MAX;
			ly1=UINT8_MAX;
			if (pm.l){
				free(pm.e);
				pm.l=0;
			}
			if (CHESS_PIECE_EXISTS(b->b[CHESS_BOARD_POS(x0,y0)])&&CHESS_PIECE_GET_COLOR(b->b[CHESS_BOARD_POS(x0,y0)])==b->t){
				pm=get_moves(b,x0,y0);
			}
		}
		else if (u_m&&x1!=UINT8_MAX&&y1!=UINT8_MAX&&(x1!=lx1||y1!=ly1)){
			lx0=x0;
			ly0=y0;
			vm=0;
			uint8_t m=CHESS_BOARD_POS(x1,y1);
			for (uint8_t i=0;i<pm.l;i++){
				if (m==*(pm.e+i)){
					vm=1;
					break;
				}
			}
		}
	}
	printf("\x1b[?25h");
}



void free_chess(ChessBoard b){
	free(b);
}

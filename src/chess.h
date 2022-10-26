#include<stdint.h>
#ifndef __CHESS_H__
#define __CHESS_H__
#endif

#define ASII_UPPERCASE 65
#define ASII_LOWERCASE 97
#define ROW 9
#define COLUMN 9
#define CHESS_NUM 20
/*
空 = z(122), 
香 = L,P,l,p;(76,80,108,112)
桂 = N,O,n,o;(78,79,110,111)
銀 = S,U,s,u;(83,85,115,117)
金 = J,V,j,v;(74,86,106,118)
玉 = K,k;(75,107)
角 = W,w;(87,119)
飛 = R,r;(82,114)
步 = ABCDEFGHI,abcdefghi;(65~73,97~105)
*/ 

// char detect_chess();
// void chess_move(uint8_t* i_pos,uint8_t* f_pos,char* ptboard);
typedef struct bag_t
{
    int top;
    char my_chess[CHESS_NUM];
}bag;

typedef enum _Direction
{
    UP,DOWN,LEFT,RIGHT,UL,UR,DL,DR
} Direction;
static Direction detect_direction(int8_t dx,int8_t dy);
int break_rule(const char* ptu_chess,const uint8_t* origin_pos,const uint8_t* destin_pos,const char* ptboard);
// void chess_detect(char* const location,char* const ptboard);

void init_bag(bag* ptxb,bag* ptyb);
void print_chess(const char* ptboard);
void chess_move(char* const ptu_chess,char* const ptg_chess);
void chess_eat(char* const ptu_chess,char* const ptg_chess,bag* ptcb);
int detect_Pawn(char user,int8_t dx,int8_t dy);
int detect_Knight(char user,int8_t dx,int8_t dy);
int detect_Sliver(char user,int8_t dx,int8_t dy);
int detect_Gold(char user,int8_t dx,int8_t dy);
int detect_King(char user,int8_t dx,int8_t dy);
int detect_Lance(char user,int8_t dx,int8_t dy);
int detect_Rook(char user,int8_t dx,int8_t dy);
int detect_Bishop(char user,int8_t dx,int8_t dy);
int detect_path(const char* ptch,int8_t dx,int8_t dy,Direction d);
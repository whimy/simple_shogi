#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "chess.h"
#include "board.h"


// // chess act rule
void init_bag(bag* ptxb,bag* ptyb)
{   
    bag x_bag;
    bag y_bag;
    *ptxb = x_bag;
    ptxb->top = -1;
    memset(ptxb->my_chess,0,CHESS_NUM);
    *ptyb = y_bag;
    ptyb->top = -1;
    memset(ptyb->my_chess,0,CHESS_NUM);
}


void print_chess(const char* ptboard){
    if(*ptboard <= 105 && *ptboard >= 97){
                printf("\033[31m步\033[m ");
            }else if(*ptboard == 'l' || *ptboard == 'p'){
                printf("\033[31m香\033[m ");
            }else if(*ptboard == 'n' || *ptboard == 'o'){
                printf("\033[31m桂\033[m ");
            }else if(*ptboard == 's' || *ptboard == 'u'){
                printf("\033[31m銀\033[m ");
            }else if(*ptboard == 'j' || *ptboard == 'v'){
                printf("\033[31m金\033[m ");
            }else if(*ptboard == 'k'){
                printf("\033[31m玉\033[m ");
            }else if(*ptboard == 'w'){
                printf("\033[31m角\033[m ");
            }else if(*ptboard == 'r'){
                printf("\033[31m飛\033[m ");
            }
            // player x
            else if(*ptboard <= 73 && *ptboard >= 65){
                printf("\033[34m步\033[m ");
            }else if(*ptboard == 'L' || *ptboard == 'P'){
                printf("\033[34m香\033[m ");
            }else if(*ptboard == 'N' || *ptboard == 'O'){
                printf("\033[34m桂\033[m ");
            }else if(*ptboard == 'S' || *ptboard == 'U'){
                printf("\033[34m銀\033[m ");
            }else if(*ptboard == 'J' || *ptboard == 'V'){
                printf("\033[34m金\033[m ");
            }else if(*ptboard == 'K'){
                printf("\033[34m玉\033[m ");
            }else if(*ptboard == 'W'){
                printf("\033[34m角\033[m ");
            }else if(*ptboard == 'R'){
                printf("\033[34m飛\033[m ");
            }else{
                printf("　");
            }
}

void chess_move(char* const ptu_chess,char* const ptg_chess){ 
    char temp = *ptg_chess;
    *ptg_chess = *ptu_chess;
    *ptu_chess = temp;
}

void chess_eat(char* const ptu_chess,char* const ptg_chess,bag* ptcb){
    ptcb->top += 1;
    ptcb->my_chess[ptcb->top] = *ptg_chess;
    *ptg_chess = *ptu_chess;
    *ptu_chess = 'z';
}

// 引寄上直左右
static Direction detect_direction(int8_t dx,int8_t dy){
    if(dy < 0 ){
        if(dx == 0){
            return UP;
        }else if(dx > 0){
            return UL;
        }else{
            return UR;
        }
    }else if(dy > 0){
        if(dx == 0){
            return DOWN;
        }else if(dx > 0){
            return DL;
        }else{
            return DR;
        }
    }else{
        if(dx > 0){
            return LEFT;
        }else{
            return RIGHT;
        }
    }
}

int break_rule(const char* ptu_chess,const uint8_t* origin_pos,const uint8_t* destin_pos,const char* ptboard){
    char u_chess = *ptu_chess;
    int8_t x0 = COLUMN - *origin_pos;      int8_t x1 = COLUMN - *destin_pos;
    int8_t y0 = *(origin_pos + 1) - 1;     int8_t y1 = *(destin_pos + 1) - 1;
    int8_t delta_x = (int8_t)(x1-x0);      int8_t delta_y = (int8_t)(y1-y0);
    Direction dir = detect_direction(delta_x,delta_y);
    // 步Pawn A-I/a-i
    if(u_chess >= 'A' && u_chess <= 'I'){
        return detect_Pawn('x',delta_x,delta_y);
    }else if(u_chess >= 'a' && u_chess <= 'i'){
        return detect_Pawn('y',delta_x,delta_y);
    }
    //桂 NO/no
    if(u_chess == 'N' || u_chess == 'O'){
        return detect_Knight('x',delta_x,delta_y);
    }else if(u_chess == 'n' && u_chess == 'o'){
        return detect_Knight('y',delta_x,delta_y);
    }
    //銀 SU/su
    if(u_chess == 'S' || u_chess == 'U'){
        return detect_Sliver('x',delta_x,delta_y);
    }else if(u_chess == 's' && u_chess == 'u'){
        return detect_Sliver('y',delta_x,delta_y);
    }
    // 金 JV/jv
    if(u_chess == 'J' || u_chess == 'V'){
        return detect_Gold('x',delta_x,delta_y);
    }
    else if(u_chess == 'j' || u_chess == 'v'){
        return detect_Gold('y',delta_x,delta_y);
    }
    // 玉 K/k
    if(u_chess == 'K' || u_chess == 'k'){
        return detect_King('b',delta_x,delta_y);
    }
    // 香 LP/lp (detect path empty)
    if(u_chess == 'L' || u_chess == 'P'){
        return (detect_Lance('x',delta_x,delta_y) || detect_path(ptu_chess,delta_x,delta_y,dir));
    }else if(u_chess == 'l' || u_chess == 'p'){
        return (detect_Lance('y',delta_x,delta_y) || detect_path(ptu_chess,delta_x,delta_y,dir));
    }
    // 飛 R/r (detect path empty)
    if(u_chess == 'R' || u_chess == 'r'){
        return (detect_Rook('b',delta_x,delta_y) || detect_path(ptu_chess,delta_x,delta_y,dir));
    }
    // 角 Bishop W/w (detect path empty)
    if(u_chess == 'W' || u_chess == 'w'){
        return (detect_Bishop('b',delta_x,delta_y) || detect_path(ptu_chess,delta_x,delta_y,dir));
    }
    return 0;
}


// 步 x:ABCDEFGHI ->    
int detect_Pawn(char user,int8_t dx,int8_t dy){
    if(dx != 0){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 步 cannot move horizontally.\n  Please try again.\n\n");
        return 1;
    }else if((user == 'x' && dy < -1) ||(user == 'y' && dy > 1)){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 步 can only move forward one step.\n  Please try again.\n\n");
        return 1;            
    }else if((user == 'x' && dy > -1) || (user == 'y' && dy < 1)){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 步 cannot move backward.\n  Please try again.\n\n");
        return 1;            
    }else{
        return 0;
    }
}

// 桂 Knight NO/no
int detect_Knight(char user,int8_t dx,int8_t dy){
    if(user == 'x' && ((abs(dx) != 1) || (dy != -2))){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 桂 can only jumps at the foward angle of a 2x3 triangle.\n  Please try again.\n\n");
        return 1;
    }else if(user == 'y' && ((abs(dx) != 1) || (dy != 2))){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 桂 can only jumps at an angle intermediate to orthogonal and diagonal.\n  Please try again.\n\n");
        return 1;
    }else{
        return 0;
    }
}

// 銀 Sliver SU/su
int detect_Sliver(char user,int8_t dx,int8_t dy){
    if(abs(dy) > 1 || abs(dx) > 1){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 銀 can only move within one square around itself.\n  Please try again.\n\n");
        return 1;
    }else if(abs(dx) == 1 && abs(dy) == 0){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 銀 cannot move just right or left.\n  Please try again.\n\n");
        return 1; 
    }else if((user == 'x' && dy == 1) || (user == 'y' && -dy == 1)){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 銀 cannot move right backward.\n  Please try again.\n\n");
        return 1;
    }else{
        return 0;
    }
}

// 金 Gold JV/jv
int detect_Gold(char user,int8_t dx,int8_t dy){
    // fliter x,y > 0
    if(abs(dy) > 1 || abs(dx) > 1){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 金 can only move within one square around itself.\n  Please try again.\n\n");
        return 1;
    }else if((user == 'x' && (dy == 1 && abs(dx) == 1)) || (user == 'y' && (-dy == 1 && abs(dx) == 1))){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 金 cannot move diagonally backwards.\n  Please try again.\n\n");
        return 1;
    }else{
        return 0;
    }
}

// 玉 King K/k
int detect_King(char user,int8_t dx,int8_t dy){
    if(abs(dx) > 1 || abs(dy) > 1){
    printf("  \033[31mYou can not move to here.\033[m\n  Error: 玉 can only move within one square.\n  Please try again.\n\n");
        return 1;
    }else{
        return 0;
    }
}

// 香 Lance LP/lp
int detect_Lance(char user,int8_t dx,int8_t dy){
    if(dx != 0){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 香 can only move straight foward.\n  Please try again.\n\n");
        return 1;
     }else if(user == 'x' && dy > 0 || user == 'y' && -dy > 0){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 香 can only move foward.\n  Please try again.\n\n");
        return 1;
    }
    // else if(detect_path()){
    //  return 1;
    // }
    else{
        return 0;
    }
}

// 飛 Rook R/r
int detect_Rook(char user,int8_t dx,int8_t dy){
    if( dx*dy != 0){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 飛 can only move straight horizontally or vertically.\n  Please try again.\n\n");
        return 1;        
    }
    return 0;
}

// 角 Bishop W/w
int detect_Bishop(char user,int8_t dx,int8_t dy){
    if(abs(dx) != abs(dy)){
        printf("  \033[31mYou can not move to here.\033[m\n  Error: 角 can only move in a diagonal direction.\n  Please try again.\n\n");
        return 1;
    }
    return 0;
}

// detect path
int detect_path(const char* ptch,int8_t dx,int8_t dy,Direction d){
    if(d == UP){    // y--
        for(int8_t t = 1;t <= abs(dy);t++){
            if(*(ptch-t*ROW) != 'z'){
            printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
            return 1;
            }
        }
        return 0;
    }else if(d == DOWN){    //y++
        for(int8_t t = 1;t <= abs(dy);t++){
            if(*(ptch+t*ROW) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }
        }
        return 0;
    }else if(d == LEFT){    //x++
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch+t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }
        }
        return 0;        
    }else if(d == RIGHT){   //x--
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch-t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }
        }
        return 0;            
    }else if(d == UR){  //x-- y--
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch-t*ROW-t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }            
        }
        return 0;
    }else if(d == UL){  //x++ y--
        printf("case UL");
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch-t*ROW+t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }            
        }
        return 0;
    }else if(d == DR){  //x--y++
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch+t*ROW-t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }            
        }
        return 0;
    }else if(d == DL){  // x++ y++
        for(int8_t t = 1;t <= abs(dx);t++){
            if(*(ptch+t*ROW+t) != 'z'){
                printf("  \033[31mYou can not move to here.\033[m\n  Error: There is chess in your moving path.\n  Please try again.\n\n");
                return 1;
            }            
        }
        return 0;
    }
 
}
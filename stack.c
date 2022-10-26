#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "backprop.h"
#include "board.h"
#include "chess.h"
#include "stack.h"


void init_record(stack* pts)
{   
    *pts = create_stack(STACKSIZE);
    pts->top = -1;
}

stack create_stack(int stacksize)
{
	stack record;
	record.step = (struct step_t *) malloc(STACKSIZE * sizeof(struct step_t));
	return record;
}

// top + 1 -> push in value
void data_push(stack* const pts, char user, char u_chess,char g_chess,char* ptu_chess,char* ptg_chess,char act,char dir)
{
    if(!overflow(pts)){
        // stack is not overflow
        pts->top += 1;
        pts->step[pts->top]._player = user;
        pts->step[pts->top]._u_chess = u_chess;
        pts->step[pts->top]._g_chess = g_chess;
        pts->step[pts->top]._iptboard[0] = *ptu_chess;
        pts->step[pts->top]._iptboard[1] = *(ptu_chess+1);
        pts->step[pts->top]._dptboard[0] = *ptg_chess;
        pts->step[pts->top]._dptboard[1] = *(ptg_chess+1);
        pts->step[pts->top]._action = act;
        pts->step[pts->top]._direction = dir;
        
    }else{
        // stack is overflow
        printf("Stack overflow!");
    }

    
}

// pop up value -> top - 1
void pop(stack* const pts,bag* const ptxb,bag* const ptyb){
    if(!empty(pts)){

        if(pts->step[pts->top]._action == 'e'){
            if(pts->step[pts->top]._player == 'x'){
                ptxb->my_chess[ptxb->top] = 0;
                ptxb->top -=1;
            }else{
                ptyb->my_chess[ptyb->top] = 0;
                ptyb->top -=1;
            }
        }

        pts->step[pts->top]._player = 0;
        pts->step[pts->top]._u_chess = 0;
        pts->step[pts->top]._g_chess = 0;
        pts->step[pts->top]._iptboard[0] = 0;
        pts->step[pts->top]._dptboard[0] = 0;
        pts->step[pts->top]._iptboard[1] = 0;
        pts->step[pts->top]._dptboard[1] = 0;
        pts->step[pts->top]._action = 0;
        pts->step[pts->top]._direction = 0;
        pts->top -= 1;

    }else{
        printf("The stack is empty.\n");
    }
}

int empty(const stack* pts){
    if(pts->top == -1){
        return(TRUE);
    }else{
        return(FALSE);
    }
}

int overflow(const stack* pts)
{
    if(pts->top == STACKSIZE - 1){
        return(TRUE);
    }else{
        return(FALSE);
    }
}


void create_file(FILE* fp){
    fp = fopen("game_record.csv","w+");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }else{
        printf("File create successfully.\n");
    }
    
    fprintf(fp, "先後手,筋,段,駒名,\n");

    fclose(fp);
}

void write_file(FILE* fp,char user,const char* u_chess,const uint8_t* destin_pos){
    fp = fopen("game_record.csv","a+");
    if (fp == NULL) {
        fprintf(stderr, "fopen() failed.\n");
        exit(EXIT_FAILURE);
    }
    // 寫入先後手
    if(user == 'x'){
        fprintf(fp,"先手▲,");
    }else{
        fprintf(fp,"後手△,");
    }
    // 以羅馬數字寫入筋
    fprintf(fp, "%hhd,",*destin_pos);
    // 以國字寫入段
    if(*(destin_pos+1) == 1){
        fprintf(fp,"一,");
    }else if(*(destin_pos+1) == 2){
        fprintf(fp,"二,");
    }else if(*(destin_pos+1) == 3){
        fprintf(fp,"三,");
    }else if(*(destin_pos+1) == 4){
        fprintf(fp,"四,");
    }else if(*(destin_pos+1) == 5){
        fprintf(fp,"五,");
    }else if(*(destin_pos+1) == 6){
        fprintf(fp,"六,");
    }else if(*(destin_pos+1) == 7){
        fprintf(fp,"七,");
    }else if(*(destin_pos+1) == 8){
        fprintf(fp,"八,");
    }else if(*(destin_pos+1) == 9){
        fprintf(fp,"九,");
    }
    // 以國字寫入棋
    fread_chess(fp,u_chess);
    fprintf(fp,"\n");
    

    fclose(fp);

}
// 棋以國字寫入檔案
void fread_chess(FILE* fp,const char* u_chess){
    if((*u_chess <= 'I' && *u_chess >= 'A') || (*u_chess <= 'i' && *u_chess >= 'a')){
        fprintf(fp,"步,");
    }else if(*u_chess == 'l' || *u_chess == 'p' || *u_chess == 'L' || *u_chess == 'P'){
        fprintf(fp,"香,");
    }else if(*u_chess == 'n' || *u_chess == 'o' || *u_chess == 'N' || *u_chess == 'O'){
        fprintf(fp,"桂,");
    }else if(*u_chess == 's' || *u_chess == 'u' || *u_chess == 'S' || *u_chess == 'U'){
        fprintf(fp,"銀,");
    }else if(*u_chess == 'j' || *u_chess == 'v' || *u_chess == 'J' || *u_chess == 'V'){
        fprintf(fp,"金,");
    }else if(*u_chess == 'k' || *u_chess == 'K'){
        fprintf(fp,"玉,");
    }else if(*u_chess == 'w' || *u_chess == 'W'){
        fprintf(fp,"角,");
    }else if(*u_chess == 'r' || *u_chess == 'R'){
        fprintf(fp,"飛,");
    }
}
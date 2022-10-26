#include<stdio.h>
#include<stdlib.h>
#include "board.h"
#include "chess.h"
#include "stack.h"


// init board with 1d memory
void init_board(char ptboard[][ROW]){
    // 後手
    ptboard[0][0] = 'l';    ptboard[0][1] = 'n';    ptboard[0][2] = 's';    ptboard[0][3] = 'j';
    ptboard[0][4] = 'k';
    ptboard[0][8] = 'p';    ptboard[0][7] = 'o';    ptboard[0][6] = 'u';    ptboard[0][5] = 'v';
    for(int r = 0;r < COLUMN;r++){
        if(r == 1){
            ptboard[1][r] = 'r';
        }else if(r == 7){
            ptboard[1][r] = 'w';
        }else{
            ptboard[1][r] = 'z';
        }
    }
    for(int asii = 'a';asii <= 'i'; asii++){
        ptboard[2][asii-ASII_LOWERCASE] = asii; 
    }
    // 先手
    ptboard[8][0] = 'L';    ptboard[8][1] = 'N';    ptboard[8][2] = 'S';    ptboard[8][3] = 'J';
    ptboard[8][4] = 'K';
    ptboard[8][8] = 'P';    ptboard[8][7] = 'O';    ptboard[8][6] = 'U';    ptboard[8][5] = 'V';
    for(int row = 0;row < ROW;row++){
        if(row == 1){
            ptboard[7][row] = 'W';
        }else if(row == 7){
            ptboard[7][row] = 'R';
        }else{
            ptboard[7][row] = 'z';
        }
    } 
    for(int asii = 'A';asii <= 'I'; asii++){
        ptboard[6][asii-ASII_UPPERCASE] = asii; 
    }
    // empty
    for(int column = 3; column < 6; column++){
        for(int row = 0;row < ROW; row++){
            ptboard[column][row] = 'z';
        }
    }       
}

void visualize_board(const char* ptboard){

    printf("============================\n");
    for(int z = 0; z < ROW;z++){
            printf("%1d  ",ROW-z);
    }
    printf("\n");
    for(int c = 0;c < COLUMN;c++){
        for(int r = 0;r< ROW;r++){
            if(ptboard[c*ROW+r] <= 105 && ptboard[c*ROW+r] >= 97){
                printf("\033[31m步\033[m ");
            }else if(ptboard[c*ROW+r] == 'l' || ptboard[c*ROW+r] == 'p'){
                printf("\033[31m香\033[m ");
            }else if(ptboard[c*ROW+r] == 'n' || ptboard[c*ROW+r] == 'o'){
                printf("\033[31m桂\033[m ");
            }else if(ptboard[c*ROW+r] == 's' || ptboard[c*ROW+r] == 'u'){
                printf("\033[31m銀\033[m ");
            }else if(ptboard[c*ROW+r] == 'j' || ptboard[c*ROW+r] == 'v'){
                printf("\033[31m金\033[m ");
            }else if(ptboard[c*ROW+r] == 'k'){
                printf("\033[31m玉\033[m ");
            }else if(ptboard[c*ROW+r] == 'w'){
                printf("\033[31m角\033[m ");
            }else if(ptboard[c*ROW+r] == 'r'){
                printf("\033[31m飛\033[m ");
            }
            // player x
            else if(ptboard[c*ROW+r] <= 73 && ptboard[c*ROW+r] >= 65){
                printf("\033[34m步\033[m ");
            }else if(ptboard[c*ROW+r] == 'L' || ptboard[c*ROW+r] == 'P'){
                printf("\033[34m香\033[m ");
            }else if(ptboard[c*ROW+r] == 'N' || ptboard[c*ROW+r] == 'O'){
                printf("\033[34m桂\033[m ");
            }else if(ptboard[c*ROW+r] == 'S' || ptboard[c*ROW+r] == 'U'){
                printf("\033[34m銀\033[m ");
            }else if(ptboard[c*ROW+r] == 'J' || ptboard[c*ROW+r] == 'V'){
                printf("\033[34m金\033[m ");
            }else if(ptboard[c*ROW+r] == 'K'){
                printf("\033[34m玉\033[m ");
            }else if(ptboard[c*ROW+r] == 'W'){
                printf("\033[34m角\033[m ");
            }else if(ptboard[c*ROW+r] == 'R'){
                printf("\033[34m飛\033[m ");
            }else{
                printf("　 ");
            }
        }
        printf("%d\n",c+1);
    }
    printf("============================\n");

}

void recover_board(char* ptboard,char i_chess,char d_chess,char o_pos[2],char d_pos[2]){
    char* i_ptboard = &(ptboard[(o_pos[1]-1)*ROW + (ROW-o_pos[0])]);
    char* d_ptboard = &(ptboard[(d_pos[1]-1)*ROW + (ROW-d_pos[0])]);
    *i_ptboard = i_chess;
    *d_ptboard = d_chess;
}


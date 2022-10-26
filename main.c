#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ev.h>
#include <time.h>
#include "board.h"
#include "chess.h"
#include "backprop.h"
#include "stack.h"


char board[ROW][COLUMN];
char player;
int status;
char direction;
bag* ptxbag;
bag* ptybag;
uint8_t turn;
uint8_t* origin_position;
uint8_t* destin_position;
stack* spt = NULL;
FILE *fp;
time_t result;

ev_timer timeout_watcher;
ev_timer repeate_watcher;
ev_timer oneshot_watcher;

int main(){

    origin_position = (uint8_t*)malloc(2*sizeof(int));
    destin_position = (uint8_t*)malloc(2*sizeof(int));
    spt = (stack*) malloc(sizeof(stack));
    ptxbag = (bag*)malloc(sizeof(bag));
    ptybag = (bag*)malloc(sizeof(bag));
    init_bag(ptxbag,ptybag);
    init_record(spt);
    create_file(fp);
    // initialize game
    init_board(board);
    
    view_result();
    game();

    free(origin_position);
    free(destin_position);
    free(spt);
    return 0;
}

void game(){
    turn = 1;
    // each player take turn
    while(1){
        printf("Turn %d\n",turn);

        if(turn % 2 == 1){
            player = 'x';
            printf("Player \033[34m %c\033[m:\n",player);
        }else if(turn % 2 == 0){
            player = 'y';
            printf("Player \033[31m %c\033[m:\n",player);
        }

        char* ptused_chess = 0;     char* ptgoal_chess = 0;
        char used_chess = 0;        char goal_chess = 0;
        char action = 'z';

        // regret
        if(turn > 2){
            char re;
            printf("  Regret for the previous move?(Enter 0):");
            scanf(" %c",&re);
            if(re == '0'){
                chess_regret();
                continue;                
            }
        }
        // feed input
        while(1){
            // init_pos input
            status = feed_init_pos();
            while(status){
                status = feed_init_pos();
            }
            ptused_chess = &board[*(origin_position+1) - 1][ROW - *(origin_position)];
            used_chess = *ptused_chess;
            // dest_pos input
            status = feed_dest_pos(ptused_chess);
            while(status){
                status = feed_dest_pos(ptused_chess);
            }
            ptgoal_chess = &board[*(destin_position+1) - 1][ROW - *(destin_position)];
            goal_chess = *ptgoal_chess;
            break;
        }


        // implement chess_move
        if(*ptgoal_chess != 'z'){
            if(player == 'x'){
                action = 'e';
                chess_eat(ptused_chess,ptgoal_chess,ptxbag);
            }else{
                chess_eat(ptused_chess,ptgoal_chess,ptybag);
                action = 'e';
            }
        }else{
            chess_move(ptused_chess,ptgoal_chess);
        }

        // data push in
        data_push(spt,player,used_chess,goal_chess,origin_position,destin_position,action,direction);
        write_file(fp,player,ptused_chess,destin_position);
        // show board

        view_result();
        
        // print moves
        printf("============================\n");
        if(player == 'x'){
            printf("▲ %hhd",*destin_position);
            print_y(destin_position);
            print_chess(ptgoal_chess);
            printf("\n");
        }else{
            printf("△ %hhd ",*destin_position);
            print_y(destin_position);
            print_chess(ptgoal_chess);
            printf("\n");
        }
        
        
        printf("============================\n");
        turn++;

    }
}          
        

int feed_init_pos(){

    printf("  Enter the initial position: ");
    for(int i = 0 ;i < AXIS_NUM;i++){
        scanf("%hhd",origin_position + i);
    }
    uint8_t x = ROW - *(origin_position);
    uint8_t y = *(origin_position+1) - 1;
    const char* used_chess = &board[y][x];

    if(x < 0 || y < 0 || x > ROW || y > COLUMN){
        printf("  \033[31mThis position does not exist.\033[m\n  Please try again.\n\n");
        return 1;
    }else if(*used_chess == 'z'){
        printf("  \033[31mThere is empty.\033[m\n  Please try again.\n\n");
        return 1;
    }
    else if(detect_player(used_chess) != player){
        printf("  \033[31mThis is not your chess.\033[m\n  Please try again.\n\n");
        return 1;
    }
    // else if(cannot move)
    return 0;
}

int feed_dest_pos(const char* ptu_chess){
    printf("  Enter the new position: ");
    for(int i = 0 ;i < AXIS_NUM;i++){
        scanf("%hhd",destin_position + i);
    }
    uint8_t x = ROW - *(destin_position);
    uint8_t y = *(destin_position+1) - 1;
    const char* goal_chess = &board[y][x];

    if(x < 0 || y < 0 || x > ROW || y > COLUMN)
    {
        printf("  \033[31mThis position does not exist.\033[m\n  Please try again.\n\n");
        return 1;
    }
    // direction = detect_direction();
    else if(break_rule(ptu_chess,origin_position,destin_position,board[0]))
    {
        return 1;
    }
    // else if(what is on the goal)
    else if(detect_player(goal_chess) == player)
    {
        printf("  \033[31mYou cannot eat your chess.\033[m\n  Please try again.\n\n");
        return 1;
    }
    // else if(cannot move)
    
    return 0;
}

char detect_player(const char* u_chess){
    if(*u_chess < 'z' && *u_chess >= 'a'){
        return 'y'; // y_chess
    }
    else if(*u_chess >= 'A' && *u_chess < 'Z'){
        return 'x'; // x_chess
    }
}

// 以國字寫入段
void print_y(const uint8_t* destin_pos){
    if(*(destin_pos+1) == 1){
        printf("一");
    }else if(*(destin_pos+1) == 2){
        printf("二");
    }else if(*(destin_pos+1) == 3){
        printf("三");
    }else if(*(destin_pos+1) == 4){
        printf("四");
    }else if(*(destin_pos+1) == 5){
        printf("五");
    }else if(*(destin_pos+1) == 6){
        printf("六");
    }else if(*(destin_pos+1) == 7){
        printf("七");
    }else if(*(destin_pos+1) == 8){
        printf("八");
    }else if(*(destin_pos+1) == 9){
        printf("九");
    }
}

void chess_regret(){
    recover_board(board[0],spt->step[spt->top]._u_chess,spt->step[spt->top]._g_chess,spt->step[spt->top]._iptboard,spt->step[spt->top]._dptboard);
    pop(spt,ptxbag,ptybag);
    recover_board(board[0],spt->step[spt->top]._u_chess,spt->step[spt->top]._g_chess,spt->step[spt->top]._iptboard,spt->step[spt->top]._dptboard);
    pop(spt,ptxbag,ptybag);
    view_result();
    turn -= 2;
    printf("Regret successfully!\n");

}

void view_result(){
    printf("\n--------- player y ---------\n");
    for(int c = 0;c<CHESS_NUM;c++){
        print_chess(ptybag->my_chess + c);
    }
    printf("\n");
    visualize_board(board[0]);
    for(int c = 0;c<CHESS_NUM;c++){
        print_chess(ptxbag->my_chess + c);
    }
    printf("\n--------- player x ---------\n");
}

void init_timer(){
    EV_DEFAULT_DEC;
    result = time(NULL);
}

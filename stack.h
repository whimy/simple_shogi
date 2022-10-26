#ifndef __STACK_H__
#define __STACK_H__
#endif

#define STACKSIZE 100

typedef struct step_t{
    char _player;
    char _u_chess;
    char _g_chess;
    char _iptboard[2];
    char _dptboard[2];
    char _action;  //吃,打
    char _direction;
    char buf[3];
}step;


typedef struct stack_t{
    int top;
    struct step_t *step;
}stack;

void init_record(stack* pts);
stack create_stack(int stacksize);
int empty(const stack* pts);
int overflow(const stack* pts);
void pop(stack* const pts,bag* const ptxb,bag* const ptyb);
void data_push(stack* const pts, char user, char u_chess,char g_chess,char* ptu_chess,char* ptg_chess,char act,char dir);

void create_file(FILE* fp);
void write_file(FILE* fp, char user, const char* u_chess, const uint8_t* destin_pos);
void fread_chess(FILE* fp,const char* u_chess);
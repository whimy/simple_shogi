#ifndef __BACKPROP_H__
#define __BACKPROP_H__
#endif

#include<stdint.h>
#define TRUE 1
#define FALSE 0
#define ROW 9
#define COLUMN 9
#define AXIS_NUM 2

#if EV_MULTIPLICITY
# define EV_DEFAULT_DEC EV_P = EV_DEFAULT
#else
# define EV_DEFAULT_DEC ev_default_loop(0)
#endif



void game();
int feed_init_pos();
int feed_dest_pos(const char* ptu_chess);
char detect_player(const char* u_chess);
void print_y(const uint8_t* destin_pos);
void chess_regret();
void view_result();
void init_timer();



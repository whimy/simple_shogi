#ifndef __BOARD_H__
#define __BOARD_H__
#endif
#define ROW 9
#define COLUMN 9

void init_board(char ptboard[][ROW]);
void visualize_board(const char* ptboard);
void recover_board(char* ptboard,char i_chess,char d_chess,char o_pos[2],char d_pos[2]);

// scan_board();


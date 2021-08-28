#include<ncurses.h>
#include<stdlib.h>

#define ARRAY_SIZE 16
#define SLEEP_TIME 100
//--------------------------------------------------------
// FUNCTION PROTOTYPES
//--------------------------------------------------------
void copy_board(char dst[ARRAY_SIZE][ARRAY_SIZE], char src[ARRAY_SIZE][ARRAY_SIZE]);
void clear_board(char some_board[ARRAY_SIZE][ARRAY_SIZE], char which_char);
void print_board(char some_board[ARRAY_SIZE][ARRAY_SIZE]);
void update(char current_board[ARRAY_SIZE][ARRAY_SIZE], char old_board[ARRAY_SIZE][ARRAY_SIZE]);

void clear_board(char some_board[ARRAY_SIZE][ARRAY_SIZE], char which_char){
  for(int row=0; row<ARRAY_SIZE; row++){
    for(int col=0; col<ARRAY_SIZE; col++){
      some_board[row][col] = which_char;
    }
  }
}

void print_board(char some_board[ARRAY_SIZE][ARRAY_SIZE]){
  for(int row=0; row<ARRAY_SIZE; row++){
    for(int col=0; col<ARRAY_SIZE; col++){
      addch(some_board[row][col]);
      addch(' ');
    }
    addch('\n');
  }
}

void copy_board(char dst[ARRAY_SIZE][ARRAY_SIZE], char src[ARRAY_SIZE][ARRAY_SIZE]){
  for(int row=0; row<ARRAY_SIZE; row++){
    for(int col=0; col<ARRAY_SIZE; col++){
      dst[ARRAY_SIZE][ARRAY_SIZE] = src[ARRAY_SIZE][ARRAY_SIZE];
    }
  }
}

void update(char current_board[ARRAY_SIZE][ARRAY_SIZE], char old_board[ARRAY_SIZE][ARRAY_SIZE]){
  clear();
  print_board(current_board);
  copy_board(old_board, current_board);
  refresh();
  napms(SLEEP_TIME);
}

int main(void)
{
    char board[ARRAY_SIZE][ARRAY_SIZE];
    char tmp_board[ARRAY_SIZE][ARRAY_SIZE];
    int sleep_time = 1000;
    initscr();
    clear_board(board, ' ');
    board[5][5] = 'x';
    for(int i = 0; i < 100; i++){
      // clear_board(board, ' ');
      update(board, tmp_board);
    }

    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();

    return EXIT_SUCCESS;
}

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

void print_horz_border(){
  addch(' ');
  for(int col=0; col<ARRAY_SIZE; col++){
    addch('_');
    addch('_');
  }
  addch('\n');
}

void print_board(char some_board[ARRAY_SIZE][ARRAY_SIZE]){
  print_horz_border();
  for(int row=ARRAY_SIZE-1; row>=0; row--){
    addch('|');
    for(int col=0; col<ARRAY_SIZE; col++){
      addch(some_board[col][row]);
      addch(' ');
    }
    addch('|');
    addch('\n');
  }
  print_horz_border();
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
  // napms(SLEEP_TIME);
}

int bound_position(int location){
  if (location >= ARRAY_SIZE){
    location = ARRAY_SIZE - 1;
  }
  else if (location < 0){
    location = 0;
  }
  return location;
}

int main(void)
{
    char tmp_board[ARRAY_SIZE][ARRAY_SIZE];
    // int sleep_time = 1000;
    int character_code;
    int player_x = 5, player_y = 5, player_big = 0;
    char board[ARRAY_SIZE][ARRAY_SIZE];
    int done = 0;
    int mush_x = 9, mush_y = 4, mush_exists = 1;
    initscr();
    while(done == 0){
      // Setup a turn.
      clear_board(board, ' ');

      // Turn logic.
      if (mush_exists){
        board[mush_x][mush_y] = 'o';
      }
      if (player_big){
        board[player_x][player_y] = 'X';
      }else{
        board[player_x][player_y] = 'x';
      }
      // Draw the turn to the screen.
      update(board, tmp_board);

      char letter = getch();
      if (letter == 'w') {
        player_y++;
      }
      else if (letter == 's'){
        player_y--;
      }
      else if (letter == 'd'){
        player_x++;
      }
      else if (letter == 'a'){
        player_x--;
      }
      player_x = bound_position(player_x);
      player_y = bound_position(player_y);
      if (player_x == mush_x && player_y == mush_y){
        mush_exists = 0;
        player_big = 1;
      }

    }

    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();

    return EXIT_SUCCESS;
}

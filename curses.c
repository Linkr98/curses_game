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
    int location_x = 5;
    int location_y = 5;
    char board[ARRAY_SIZE][ARRAY_SIZE];
    int done = 0;
    initscr();
    while(done == 0){
      clear_board(board, ' ');
      board[location_x][location_y] = 'x';
      update(board, tmp_board);
      char letter = getch();
      if (letter == 'w') {
        location_y++;
      }
      else if (letter == 's'){
        location_y--;
      }
      else if (letter == 'd'){
        location_x++;
      }
      else if (letter == 'a'){
        location_x--;
      }
      location_x = bound_position(location_x);
      location_y = bound_position(location_y);
      // character_code = getch();
      // clear_board(board, character_code);
    }

    addstr("\npress any key to exit...");
    refresh();

    getch();

    endwin();

    return EXIT_SUCCESS;
}

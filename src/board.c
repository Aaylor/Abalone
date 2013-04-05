#include "utility.h"
#include "board.h"

board init_new_board(){
  board b;
  //Creation du tableau
  int i, j;
  for(i=c_to_key('A'); i <= c_to_key('I');i++){
    for(j=i_to_key(1); j <= i_to_key(9); j++){
      b.tab[i][j] = '.';
    }
  }
  return b;
}

void display_board(board *b){
  int i, j;
  for(i = c_to_key('A'); i <= c_to_key('I'); i++){
    for(j=i_to_key(1); j <=i_to_key(9); j++){
      printf("%c ", b->tab[i][j]);
    }
    printf("\n");
  }
}

main(){
  board b = init_new_board();
  display_board(&b);
}

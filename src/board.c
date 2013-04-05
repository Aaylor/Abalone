#include "utility.h"
#include "board.h"

board init_new_board(){
  board b;
  //Creation du tableau
  char i;
  int j;
  //On initialise toutes les cases à ' ' si elle n'existe pas, '.' sinon
  for(i='A'; i <= 'I';i++){
    printf("%c, min : %d, max : %d\n", i, min_col(i), max_col(i));
    for(j=1; j <= 9; j++){
      if(j < min_col(i) || j > max_col(i))
	b.tab[c_to_key(i)][i_to_key(j)] = '0';
      else
	b.tab[c_to_key(i)][i_to_key(j)] = '.';
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

//min_line renvoie la cle de l'element minimal de la ligne l (la CLE, pas l'indice de tab)
int min_col(char l){
  l = c_to_key(l);
  if(l>=c_to_key('A') && l<=c_to_key('E'))
    return 1;
  else if (l == c_to_key('F'))
    return 2;
  else if (l == c_to_key('G'))
    return 3;
  else if (l == c_to_key('H'))
    return 4;
  else if (l == c_to_key('I'))
    return 5;
}

//max_line renvoie la cle de l'element maximal de la ligne l (la CLE, pas l'indice de tab)
int max_col(char l){
  l = c_to_key(l);
  if(l==c_to_key('A'))
    return 5;
  else if (l==c_to_key('B'))
    return 6;
  else if (l==c_to_key('C') )
    return 7;
  else if (l==c_to_key('D'))
    return 8;
  else if (l == c_to_key('E') || l==c_to_key('F')|| l==c_to_key('G') || l==c_to_key('H') || l==c_to_key('I'))
    return 9;
}


main(){
  board b = init_new_board();
  display_board(&b);
}

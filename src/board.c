#include "utility.h"
#include "board.h"
#include <math.h>
#include <string.h>

/*  Créer et renvoie un plateau initialisé  */
board create_new_board(){
    board b;
    init_board(&b);
    return b;
}

/*  Initialise le board dont le pointeur est en parametre   */
board *init_board(board*b){
  /* Creation du tableau */
  char i;
  int j;
  /* On initialise toutes les cases à ' ' si elle n'existe pas, '.' sinon */
  for(i='A'; i <= 'I';i++){
    for(j=1; j <= 9; j++){
      if(j < min_col(i) || j > max_col(i))
	b->tab[c_to_key(i)][i_to_key(j)] = '0';
      else
	b->tab[c_to_key(i)][i_to_key(j)] = '.';
    }
  }

  /* On pose les pieces
   * Piece B */
  for(i='A'; i <='B'; i++){ /* Les lignes A et B sont totalement à remplir */
    for(j=min_col(i); j <= max_col(i); j++){
      b->tab[c_to_key(i)][i_to_key(j)] = 'B';
    }
  }
  b->tab[c_to_key('C')][i_to_key(3)] = 'B';
  b->tab[c_to_key('C')][i_to_key(4)] = 'B';
  b->tab[c_to_key('C')][i_to_key(5)] = 'B';
  /* Piece N */
  for(i='H'; i <='I'; i++){ /* Les lignes H et I sont totalement à remplir */
    for(j=min_col(i); j <= max_col(i); j++){
      b->tab[c_to_key(i)][i_to_key(j)] = 'N';
    }
  }
  b->tab[c_to_key('G')][i_to_key(5)] = 'N';
  b->tab[c_to_key('G')][i_to_key(6)] = 'N';
  b->tab[c_to_key('G')][i_to_key(7)] = 'N';
  return b;
}

/* Affiche le plateau */
void display_board(board *b){
  /*Partie haute*/
  printf("       ____________\n");
  char i;
  int j;
  for(i='I'; i >= 'A';i--){
    /*Partie droite du plateau*/
    if(i == 'I') printf("    I / ");
    else if(i == 'H') printf("   H / ");
    else if(i == 'G') printf("  G / ");
    else if(i == 'F') printf(" F / ");
    else if(i == 'E') printf("E | ");
    else if(i == 'D') printf(" D \\ ");
    else if(i == 'C') printf("  C \\ ");
    else if(i == 'B') printf("   B \\ ");
    else if(i == 'A') printf("    A \\ ");
    /*Dessin du corps du plateau*/
    for(j=1; j <= 9; j++){
      if(b->tab[c_to_key(i)][i_to_key(j)] != '0')
	printf("%c ", b->tab[c_to_key(i)][i_to_key(j)]);
    }
    /*Partie gauche du plateau*/
    if(i<= 'I' && i >= 'F') printf(" \\ \n");
    else if (i == 'E') printf(" | \n");
    else if (i == 'D') printf(" / \n");
    else if (i == 'C') printf(" / 9\n");
    else if (i == 'B') printf(" / 8\n");
    else if (i == 'A') printf(" / 7\n");
  }
  /*Partie basse*/
  printf("       ------------ 6\n           1 2 3 4 5\n");
}

/* min_col renvoie le numero de l'element minimal de la ligne l (la numero, pas l'indice de tab) */
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
  return -1;
}

/* max_col renvoie le numero de l'element maximal de la ligne l (le numero, pas l'indice de tab) */
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
  return -1;
}

/*Je met cette fonction ici pour l'instant pour eviter d'eventuels conflit avec git */
/*move_is_possible renvoie pour l'instant :
  _1 si le coup est possible
  _0 si les cases ne sont pas adjacentes
  _-1 si les cases de depart sont identiques ou si les cases d'arrivee sont identiques
  _-2 si le coups n'est pas possible pour diverse raisons
Le coup est décrit dans tabCoup qui est de la forme {{depart1},...{arrive1},...}
ex : {"B3","D3"} ou {"B3","B4","D3","D4"} ou encore {"B3","B4","B5","D3","D4","D5"}*/
int move_is_possible(board *b, char **tabMove, int tabLen){
  int i, j;
  /*Testons si les cases de depart et d'arrivee sont adjacentes*/
  for(i=0; i < tabLen/2; i++){
    if(abs(tabMove[i][0]-tabMove[i+tabLen/2][0]) >1 || abs(tabMove[i][1]-tabMove[i+tabLen/2][1]) >1) 
      return 0;
  }
  /*Testons si des cases de depart son identiques, idem pour les cases d'arrivee*/
  for(i = 0; i < tabLen; i++){
    for(j = i + 1;((i < tabLen/2) && (j < tabLen/2)) || ((i >= tabLen/2) && (j < tabLen)); j++){
      if(!(strcmp(tabMove[i], tabMove[j]))) return -1;
    }
  }
  /*Testons si le coup est faisable par rapport au nombre de billes à deplacer*/ 

  /*Aucun soucis detecte*/
  return 1;
}

/*
int main(){
board b = create_new_board();
display_board(&b);

//Test coup 1
 char *coups1[2] = {"B3","B4"};
 //printf("Le coup est est il faisable ? %d\n", move_is_possible(&b, coups1, 2));

 //Test coup 2
 char *coups2[6] = {"B3","B4","B5","C3","C4","C5"};
 printf("Le coup est est il faisable ? %d\n", move_is_possible(&b, coups2, 6));
 

return 0;
}
*/

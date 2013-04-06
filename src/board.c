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

/*Renvoie 1 si les billes du tableau sont adjacentes, renvoie 0 sinon*/
int marbles_are_adjacent(char **tab, int tabLen){
  if(tabLen == 1)
    return 1;
  else{ 
    int i;
    for(i=0; i < tabLen; i++){
      if(i < (tabLen - 1) && (abs(tab[i][0]-tab[i+1][0]) >1 || abs(tab[i][1]-tab[i+1][1]) >1)) 
	return 0;
    }
    return 1;
  }
}

/*Renvoie 0 si les billes du tableau ne sont pas dans le même alignement, renvoie 1 si elle sont alignee horizontalement, 2 si elle sont en "\" et 3 si elle sont en "\" 
  Ainsi si on veut tester si des billes sont juste alignée ou fait if(marble_alignement(..))*/
int marbles_alignement(char **tab, int tabLen){
  if(tabLen < 3)
    return 1;
  else{
    int i;
    /*Les billes sont dans une direction horizontale*/
    for(i=0; i < tabLen; i++){
      if(i==tabLen-1) return 1;
      else if(tab[i][0] != tab[i+1][0]){
	break;
      }
    }
    /*En "\" */
    for(i=0; i < tabLen; i++){
      if(i==tabLen-1) return 2;
      else if(tab[i][1] != tab[i+1][1]){
	break;
      }
    }
    /*En / */
    for(i=0; i < tabLen; i++){
      if(i==tabLen-1) return 3;
      else if(tab[i][0] - tab[i+1][0] != tab[i][1] - tab[i+1][1]){
	break;
      }
    }
    /*Finalement elles ne sont pas alignee*/
    return 0;
  }
}

/*Je met cette fonction ici pour l'instant pour eviter d'eventuels conflit avec git */
/*move_is_possible renvoie pour l'instant :
  _1 si le coup est possible
  _0 pas jouable pour des raisons inconnues
  _-1 cases non adjacentes
  _-2 cases non alignees
  _-3 cases identiques
  Le coup est décrit dans tabCoup qui est de la forme {{depart1},...{arrive1},...}
  ex : {"B3","D3"} ou {"B3","B4","D3","D4"} ou encore {"B3","B4","B5","D3","D4","D5"}*/


int move_is_possible(board *b, char **tabMove, int tabLen){
  //POUR LE TEST : printf("%s donne %c %c -> %d %d\n", tabMove[i], tabMove[i][0], tabMove[i][1], c_to_key(tabMove[i][0]), tabMove[i][1] - '1');
  int i, j;

  /*LA COMMANDE A-T-ELLE UN SENS ?*/
  /*Les cases de départ ne doivent pas etre vide*/
  for(i = 0; i < tabLen/2; i++){
    if(b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] == '.')
      return -1;
  }
  /*Les cases de depart ne doivent pas comporter des cases identiques, idem pour les cases d'arrivee*/
  for(i = 0; i < tabLen; i++){
    for(j = i + 1;((i < tabLen/2) && (j < tabLen/2)) || ((i >= tabLen/2) && (j < tabLen)); j++){
      if(!(strcmp(tabMove[i], tabMove[j]))) 
	return -2;
    }
  } 
  for(i = 0; i < tabLen/2; i++){
    for(j = tabLen/2; j< tabLen; j++){
      if(!(strcmp(tabMove[i], tabMove[j]))) 
	return -2;
    }
  } 
  /*Les cases de depart doivent etre adjacente, idem pour les cases d'arrivee*/
  if(!(marbles_are_adjacent(tabMove, tabLen/2)) || !(marbles_are_adjacent(&tabMove[tabLen/2], tabLen/2)))
    return -3;
  /*Les cases de depart ne doivent pas comporter des cases identiques, idme pour les cases d'arrivee*/
  if(marbles_alignement(tabMove, tabLen/2) == 0 || marbles_are_adjacent(&tabMove[tabLen/2], tabLen/2) ==0)
    return -4;
  
  /*LE COUP EST-IL FAISABLE PAR RAPPORT AUX REGLES DE JEU ?*/
  /*DEPLACEMENT LATERAL*/
  /*Le joueur deplace une seule bille OU la direction choisie n'est pas dans l'alignement de la rangee de bille deplacee : toutes les cases d'arrivee doivent etre vide*/  
  if(tabLen == 2)
    if(b->tab[c_to_key(tabMove[1][0])][tabMove[1][1] - '1'] == '.')
      return 1;
  if(tabLen > 2 &&  marbles_alignement(tabMove, tabLen) != 0)
    for(i=tabLen/2; i < tabLen; i++)
      if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.'))
	return -5;
 
  /*DEPLACEMENT EN LIGNE*/
  /*Les conditions d'acceptation :*/
  /*La case d'arrivee est libre, dans ce cas le coup est possible*/
  for(i=tabLen/2; i <= tabLen; i++){
    if(i==tabLen) return 1;
    if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.'))
      break ;
  }
  /*Il ne manque plus qu'à verifier que le nombre de cases de depart est suffisant pour pousser la bille contenue dans la case d'arrivée (si c'est vide derriere elle ou non*/
  if(tabLen==2){
    /*On va considerer que la case de depart est la case du joueur*/
    if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.')){
      char joueur = b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'];
      char adversaire = (joueur = 'B') ? 'N' : 'B';
      /*On va compter les case dans la direction des pieces du joueur puis de l'adversaire dans le sens donné par le coup, jusqu'à rencontrer une case vide*/
      /*On definit la variation de position de la case de depart et d'arrivee pour definir la direction*/
      int variationX = tabMove[1][1] - tabMove[0][1], variationY = tabMove[1][0] - tabMove[0][0];
      int originY = c_to_key(tabMove[0][0]), originX =  tabMove[0][1] - '1';
      i = 0; int compteur = 0; int compteurJ = 0; int compteurA = 0;

      while((b->tab[originY + i*variationY][originX + i*variationX] == 'B' || b->tab[originY + i*variationY][originX + i*variationX] == 'N') && (originY + i*variationY >= 0 && originY + i*variationY < 9 &&  tabMove[0][1] - '1' >= 0 &&  tabMove[0][1] - '1' < 9)){
	//printf("%c%c -> %c\n", tabMove[0][0] + i*variationY, tabMove[0][1] + i*variationX, b->tab[originY + i*variationY][originX + i*variationX]);
	if (b->tab[originY + i*variationY][originX + i*variationX] == joueur)
	  compteurJ++;
	else if (b->tab[originY + i*variationY][originX + i*variationX] == adversaire)
	  compteurA++;
	i++;
      }
      /*printf("Joueur : %d Adversaire : %d", compteurJ, compteurA);*/
      if(compteurA > 2) return -7;/*Trop de bille adverses*/
      if(compteurJ > 3) return -8;/*Trop de bille du joueur*/
      if(compteurJ == compteurA) return -9;/*Egalite des bille*/
      if(compteurJ < compteurA) return -10; /*+ de bille adverses*/
      return 1;/*Pas de soucis*/
    }

    /*Cas qui n'a pas été traité*/
    return -666;
  }

  /*Aucun soucis detecté a priori */
  return 1;
}

/*
int main(){
  board b = create_new_board();
  display_board(&b);

  //Test coup 1
  char *coups1[2] = {"C3","C3"};
  printf("Le coup est est il faisable ? %d\n", move_is_possible(&b, coups1, 2));
  //printf("Les billes sont elles adjacentes ? %d\n", marbles_are_adjacent(coups1, 2));
  //printf("Les billes sont elles alignee ? %d\n", marbles_alignement(coups1, 2));


  putchar('\n');

  //Test coup 2
  char *coups2[6] = {"A1","A2","A3","B1","B2","B3"};
  //printf("Le coup est est il faisable ? %d\n", move_is_possible(&b, coups2, 6));
  //printf("Les billes sont elles adjacentes ? %d\n", marbles_are_adjacent(coups2, 3));
  //printf("Les billes sont elles alignee ? %d\n", marbles_alignement(coups2, 3));
 

  return 0;
}
*/

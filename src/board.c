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
  char *color_background = "47", *color_board = "32", *color_B = "34", *color_N = "30", *color_text;
  char i;
  int j;
  /*Partie haute*/
  set_colot_text(color_background);/*Couleur de fond*/
  set_colot_text(color_board);/*Couleur du plateau*/
  printf("\t       ____________\t\t\n");
  for(i='I'; i >= 'A';i--){
    set_colot_text(color_board);
    /*Partie gauche du plateau*/
    putchar('\t');
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
      if(b->tab[c_to_key(i)][i_to_key(j)] != '0'){
	color_text = (b->tab[c_to_key(i)][i_to_key(j)] == 'B') ? color_B : (b->tab[c_to_key(i)][i_to_key(j)] == 'N') ? color_N : color_board;
	set_colot_text(color_text);
	printf("%c ", b->tab[c_to_key(i)][i_to_key(j)]);
      }
    }
    /*Partie droite du plateau*/
    set_colot_text(color_board);
    if(i<= 'I' && i >= 'F') printf(" \\\t");
    else if (i == 'E') printf(" |");
    else if (i == 'D') printf(" /\t");
    else if (i == 'C') printf(" / 9");
    else if (i == 'B') printf(" / 8\t");
    else if (i == 'A') printf(" / 7\t");
    putchar('\t'); putchar('\n');
  }
  /*Partie basse*/
  printf("\t       ------------ 6\t\t\n\t           1 2 3 4 5\t\t");
  set_colot_text("0");
  putchar('\n');
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
/*move_is_possible renvoie :
  _1 : Coups Lateral POSSIBLE, 2 : Coups en ligne POSSIBLE
  _-1 : Une case de depart ne contient pas une bille du joueur, -2 : Il y a des case identiques dans les case de depart ou d'arrivee
  _-3 : Case de depart ou d'arrivee non adjacentes, -4 : Case de depart ou d'arrivee non alignee
  _-5 : Coups Lateral IMPOSSIBLE : car case d'arrivee non vide
  _-7 : Coups Lateral IMPOSSIBLE : trop de billes adverses sur l'alignement
  _-8 : Coups Lateral IMPOSSIBLE : trop de billes du joueurs sur l'alignement
  _-9 : Coups Lateral IMPOSSIBLE : egalite de billes joueur et adverses dans l'alignement
  _-10 : Coups Lateral IMPOSSIBLE : + de billes adverses que de bille du joueur dans l'alignement
  _-11 Une case n'a aucun sens
  _-12 : Ejection d'une bille du joueur
  _-666 : Coups Lateral non capturé; 666 : coups quelconque non capturé (pour le debugage)
*/
int move_is_possible(board *b, p_move *commande){
  int tabLen = commande->length;
  char **tabMove = commande->squares;
  char joueur = commande->color;
  char adversaire = (commande->color == 'B')? 'N' : 'B';
  int i, j;

  /*LA COMMANDE A-T-ELLE UN SENS ?*/
  /*Les cases doivent avoir un sens*/
  for(i =0; i < tabLen; i++){
    if(tabMove[i][0] < 'A' || tabMove[i][0] > 'I' || tabMove[i][1] < '1' || tabMove[i][1] > '9')
      return -11;
  }
  /*Les cases de départ doivent contenir les billes du joueur*/
  for(i = 0; i < tabLen/2; i++){
    if(b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != joueur)
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
  /*Les cases de depart doivent etre adjacente aux cases d'arrivee*/
  for(i = 0; i < tabLen/2; i++){
    char* tabDepartArrivee[2];
    tabDepartArrivee[0] = tabMove[i]; tabDepartArrivee[1] = tabMove[i+tabLen/2];
    if(marbles_are_adjacent(tabDepartArrivee, 2) == 0) 
      return -3;
  }
  /*Les cases de depart doivent etre dans le même alignement, idem pour les cases d'arrivee*/
  if(marbles_alignement(tabMove, tabLen/2) == 0 || marbles_alignement(&tabMove[tabLen/2], tabLen/2) ==0)
    return -4;

  /*LE COUP EST-IL FAISABLE PAR RAPPORT AUX REGLES DE JEU ?*/
  /*DEPLACEMENT LATERAL*/
  /*Le joueur deplace une seule bille OU la direction choisie n'est pas dans l'alignement de la rangee de bille deplacee : toutes les cases d'arrivee doivent etre vide*/  
  if(tabLen == 2)
    if(b->tab[c_to_key(tabMove[1][0])][tabMove[1][1] - '1'] == '.'){
      /*Dernier test : Est ce qu'on ejecterai une bille du joueur :*/
      if(does_move_eject_marble(b, commande) == 1){
	return -12;
      }
      else{
	return 1;
      }
    }
  if(tabLen > 2 &&  marbles_alignement(tabMove, tabLen) == 0){
    for(i=tabLen/2; i < tabLen; i++)
      if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.'))
	return -5;
  }
  /*DEPLACEMENT EN LIGNE*/
  /*Les conditions d'acceptation :*/
  /*La case d'arrivee est libre, dans ce cas le coup est possible*/
  for(i=tabLen/2; i <= tabLen; i++){
    if(i==tabLen) return 2;
    if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.'))
      break ;
  }
  /*Verifions que le nombre de cases de depart est suffisant pour pousser la bille contenue dans la case d'arrivée (si c'est vide derriere elle ou non*/
  if(tabLen==2){
    /*La case de depart est la case du joueur*/
    if((b->tab[c_to_key(tabMove[i][0])][tabMove[i][1] - '1'] != '.')){
      /*Comptions les case dans la direction des pieces du joueur puis de l'adversaire dans le sens donné par le coup, jusqu'à rencontrer une case vide*/
      /*On definit la variation de position de la case de depart et d'arrivee pour definir la direction*/
      int variationX = tabMove[1][1] - tabMove[0][1], variationY = tabMove[1][0] - tabMove[0][0];
      int originY = c_to_key(tabMove[0][0]), originX =  tabMove[0][1] - '1';
      int compteurJ = 0; int compteurA = 0;
      i = 0; 

      while((b->tab[originY + i*variationY][originX + i*variationX] == 'B' || b->tab[originY + i*variationY][originX + i*variationX] == 'N') && (originY + i*variationY >= 0 && originY + i*variationY < 9 &&  tabMove[0][1] - '1' >= 0 &&  tabMove[0][1] - '1' < 9)){
	if (b->tab[originY + i*variationY][originX + i*variationX] == joueur)
	  compteurJ++;
	else if (b->tab[originY + i*variationY][originX + i*variationX] == adversaire)
	  compteurA++;
	i++;
      }
      if(compteurA > 2) return -7;/*Trop de bille adverses*/
      if(compteurJ > 3) return -8;/*Trop de bille du joueur*/
      if(compteurJ == compteurA) return -9;/*Egalite des bille*/
      if(compteurJ < compteurA) return -10; /*+ de bille adverses*/
      /*Dernier test : Est ce qu'on ejecterai une bille du joueur :*/
      if(does_move_eject_marble(b, commande) == 1){
	return -12;
      }
      else{
	return 2;/*Pas de soucis*/
      }
    }
    /*Cas qui n'a pas été traité*/
    return -666;
  }
  /*Aucun soucis detecté a priori */
  return 666;
}

/*Renvoie 1 si le mouvement ejecte une bille, 0 sinon*/
int does_move_eject_marble(board *b, p_move* commande){
  int tabLen = commande->length;
  char **tabMove = commande->squares;
  /*Calcul de la direction du mouvement*/
  int variationX = tabMove[tabLen/2][1] - tabMove[0][1], variationY = tabMove[tabLen/2][0] - tabMove[0][0];
  /*Toutes les cases de depart son successivement traitees*/
  int j;
  for (j=0; j < tabLen/2; j++){
    int originY = c_to_key(tabMove[j][0]), originX =  tabMove[j][1] - '1';
    /*On va derouler la ligne jusqu'au prochain vide*/
    int i = 0;
    char caseActuelle;
    while((b->tab[originY + i*variationY][originX + i*variationX] != '.' && b->tab[originY + i*variationY][originX + i*variationX] != '0') && (originY + i*variationY >= 0 && originY + i*variationY < 9 &&  tabMove[0][1] - '1' >= 0 &&  tabMove[0][1] - '1' < 9)){
      caseActuelle = b->tab[originY + i*variationY][originX + i*variationX];
      i++;
    }
    /*Il ne manque plus qu'a verifier si la derniere case avant un vide contient une bille du joueur*/
    if(caseActuelle == commande->color && (originY + i*variationY > 8 || originY + i*variationY < 0 || originX + i*variationX > 8 || originX + i*variationX < 0 ||b->tab[originY + i*variationY][originX + i*variationX] == '0'))
      return 1;
  }
  return 0;
}

/*Effectue le mouvement decrit par le tableau tabMove EN CONSIDERANT QU'IL EST POSSIBLE*/
void do_move(board *b, p_move* commande){
  int tabLen = commande->length;
  char **tabMove = commande->squares;
  /*On va proceder a une simple substitution des case de la case de depart a la prochaine case vide*/
  int j;
  /*Calcul de la direction du mouvement*/
  int variationX = tabMove[tabLen/2][1] - tabMove[0][1], variationY = tabMove[tabLen/2][0] - tabMove[0][0];
  /*Toutes les casesde depart son successivement geree*/
  for (j=0; j < tabLen/2; j++){
    int originY = c_to_key(tabMove[j][0]), originX =  tabMove[j][1] - '1';
    /*On va derouler la ligne jusqu'au prochain vide*/
    int i = 0;
    char casePrecedente = '.', caseActuelle;
    while((b->tab[originY + i*variationY][originX + i*variationX] != '.' && b->tab[originY + i*variationY][originX + i*variationX] != '0') && (originY + i*variationY >= 0 && originY + i*variationY < 9 &&  tabMove[0][1] - '1' >= 0 &&  tabMove[0][1] - '1' < 9)){
      caseActuelle = b->tab[originY + i*variationY][originX + i*variationX];
      b->tab[originY + i*variationY][originX + i*variationX] = casePrecedente;
      casePrecedente = caseActuelle;
      i++;
    }
    /*Il ne manque plus qu'a verifier si la derniere case a ete ejectee ou atteri dans une case vide*/
    if(b->tab[originY + i*variationY][originX + i*variationX] == '.' && (originY + i*variationY >= 0 && originY + i*variationY < 9 &&  tabMove[0][1] - '1' >= 0 &&  tabMove[0][1] - '1' < 9))
      b->tab[originY + i*variationY][originX + i*variationX] = casePrecedente;
  }
}

/*Fonction qui renvoit un tableau contenant toutes les commandes possibles*/
p_move* possible_movements(board *b, player couleur, int *length){
  int i, j,k;
  int coupsPossibles[6][2] = {{0,1},{1,1},{1,0},{0,-1},{-1,-1},{-1,0}};
  int lignesPossible[3][2] = {{1,0},{0,1},{-1,0}}; /*Les variations de position que l'on va utiliser pour selectionner les billes adjacentes en ligne*/
  int l;

  int tabLen = 0;
  p_move *tab = malloc(sizeof(p_move) * tabLen);/*Contiendra les mouvement possibles*/

  /*DEPLACEMENT D'UNE CASE */
  for(i='A'; i <= 'I'; i++){
    for(j=1; j <= 9; j++){
      if(b->tab[c_to_key(i)][i_to_key(j)] == couleur){/*On selectionne les cases du joueur*/
	for(k=0; k<6; k++){
	  char **tabMouvement = malloc(2 * sizeof(char*));
	  char *caseDepart = malloc(3*sizeof(char));
	  char * caseArrivee = malloc(3*sizeof(char));
	  p_move commande;
	  /*Construction de la case de depart*/
	  caseDepart[0] = i; caseDepart[1] = j + '0'; caseDepart[2] =  '\0';
	  tabMouvement[0] = caseDepart;

	  /*Construction du coup a tester*/ 
	  caseArrivee[0] = i + coupsPossibles[k][0]; caseArrivee[1] = j + '0' + coupsPossibles[k][1]; caseArrivee[2] = '\0';
	  tabMouvement[1] = caseArrivee;
	  /*Construction du mouvement correspondant*/
	  commande.squares = tabMouvement; commande.length = 2; commande.color = couleur;
	  /*On ajoute le coup au tableau s'il est possible*/
	  if(move_is_possible(b, &commande) >0){
	    tabLen++;
	    tab = realloc(tab, sizeof(p_move) * tabLen);
	    tab[tabLen-1] = commande;
	  }
	} 
      }
    }
  }
  /*DEPLACEMENT DE DEUX CASES */
  for(i='A'; i <= 'I'; i++){
    for(j=1; j <= 9; j++){
      for(l = 0; l <= 2; l++){
	int i2 = i+lignesPossible[l][0], j2 = j+lignesPossible[l][1];
	int keyi2 = c_to_key(i)+lignesPossible[l][0], keyj2 = i_to_key(j)+lignesPossible[l][1];
	if(keyi2 < 9 && keyj2 < 9 && b->tab[c_to_key(i)][i_to_key(j)] == couleur && b->tab[keyi2][keyj2] == couleur){/*On selectionne les cases du joueur*/
	  for(k=0; k<6; k++){
	    char **tabMouvement = malloc(4 * sizeof(char*));
	    char *caseDepart1 = malloc(3*sizeof(char));
	    char *caseDepart2 = malloc(3*sizeof(char));
	    char * caseArrivee1 = malloc(3*sizeof(char));
	    char * caseArrivee2 = malloc(3*sizeof(char));
	    p_move commande;

	    /*Construction des cases de depart*/
	    caseDepart1[0] = i; caseDepart1[1] = j + '0'; caseDepart1[2] =  '\0';
	    tabMouvement[0] = caseDepart1;
	    caseDepart2[0] = i2; caseDepart2[1] = j2 + '0'; caseDepart2[2] =  '\0';
	    tabMouvement[1] = caseDepart2;

	    /*Construction du coup a tester*/ 
	    caseArrivee1[0] = i + coupsPossibles[k][0]; caseArrivee1[1] = j + '0' + coupsPossibles[k][1]; caseArrivee1[2] = '\0';
	    tabMouvement[2] = caseArrivee1;
	    caseArrivee2[0] = i2 + coupsPossibles[k][0]; caseArrivee2[1] = j2 + '0' + coupsPossibles[k][1]; caseArrivee2[2] = '\0';
	    tabMouvement[3] = caseArrivee2;
	    /*Construction du mouvement correspondant*/
	    commande.squares = tabMouvement; commande.length = 4; commande.color = couleur;


	    /*On ajoute le coup au tableau s'il est possible*/
	    if(move_is_possible(b, &commande) >0){
	      tabLen++;
	      tab = realloc(tab, sizeof(p_move) * tabLen);
	      tab[tabLen-1] = commande;
	      /*printf("Depart : %s %s, Arrivee : %s %s\n", tabMouvement[0], tabMouvement[1], tabMouvement[2], tabMouvement[3]);*/
	    }
	  } 
	}
      }
    }
  }
  /*DEPLACEMENT DE TROIS CASES */
  for(i='A'; i <= 'I'; i++){
    for(j=1; j <= 9; j++){
      for(l = 0; l <= 2; l++){
	int i2 = i+lignesPossible[l][0], j2 = j+lignesPossible[l][1];
	int keyi2 = c_to_key(i)+lignesPossible[l][0], keyj2 = i_to_key(j)+lignesPossible[l][1];
	int i3 = i2+lignesPossible[l][0], j3 = j2+lignesPossible[l][1];
	int keyi3 = c_to_key(i2)+lignesPossible[l][0], keyj3 = i_to_key(j2)+lignesPossible[l][1];
	if(keyi3 < 9 && keyj3 < 9 && b->tab[c_to_key(i)][i_to_key(j)] == couleur && b->tab[keyi2][keyj2] == couleur && b->tab[keyi3][keyj3] == couleur){/*On selectionne les cases du joueur*/
	  for(k=0; k<6; k++){
	    char **tabMouvement = malloc(6 * sizeof(char*));
	    char *caseDepart1 = malloc(3*sizeof(char));
	    char *caseDepart2 = malloc(3*sizeof(char));
	    char *caseDepart3 = malloc(3*sizeof(char));
	    char * caseArrivee1 = malloc(3*sizeof(char));
	    char * caseArrivee2 = malloc(3*sizeof(char));
	    char * caseArrivee3 = malloc(3*sizeof(char));
	    p_move commande;

	    /*Construction des cases de depart*/
	    caseDepart1[0] = i; caseDepart1[1] = j + '0'; caseDepart1[2] =  '\0';
	    tabMouvement[0] = caseDepart1;
	    caseDepart2[0] = i2; caseDepart2[1] = j2 + '0'; caseDepart2[2] =  '\0';
	    tabMouvement[1] = caseDepart2;
	    caseDepart3[0] = i3; caseDepart3[1] = j3 + '0'; caseDepart3[2] =  '\0';
	    tabMouvement[2] = caseDepart3;

	    /*Construction du coup a tester*/ 
	    caseArrivee1[0] = i + coupsPossibles[k][0]; caseArrivee1[1] = j + '0' + coupsPossibles[k][1]; caseArrivee1[2] = '\0';
	    tabMouvement[3] = caseArrivee1;
	    caseArrivee2[0] = i2 + coupsPossibles[k][0]; caseArrivee2[1] = j2 + '0' + coupsPossibles[k][1]; caseArrivee2[2] = '\0';
	    tabMouvement[4] = caseArrivee2;
	    caseArrivee3[0] = i3 + coupsPossibles[k][0]; caseArrivee3[1] = j3 + '0' + coupsPossibles[k][1]; caseArrivee3[2] = '\0';
	    tabMouvement[5] = caseArrivee3;
	    /*Construction du mouvement correspondant*/
	    commande.squares = tabMouvement; commande.length = 6; commande.color = couleur;

	    /*On ajoute le coup au tableau s'il est possible*/
	    if(move_is_possible(b, &commande) >0){
	      tabLen++;
	      tab = realloc(tab, sizeof(p_move) * tabLen);
	      tab[tabLen-1] = commande;
	    }
	  } 
	}
      }
    }
  }
  *length = tabLen; 
  return tab;
}


int main(){
  board b = create_new_board();
  display_board(&b);

  //Remplissage du damier
  b.tab[c_to_key('E')][i_to_key(3)] = 'B';
  b.tab[c_to_key('D')][i_to_key(3)] = 'B';
  b.tab[c_to_key('F')][i_to_key(3)] = 'B';
  b.tab[c_to_key('G')][i_to_key(3)] = 'B';
  display_board(&b);

  //Test coup
  char *coups2[6] = {"C3","C4","C5","D3","D4","D5"};
  p_move commande2 = {coups2, 6, 'B'};
  int move_possible2 = move_is_possible(&b, &commande2);
  printf("Le coup est est il faisable ? %d\n", move_possible2);
  if(move_possible2 > 0){
    do_move(&b, &commande2);
    display_board(&b);
  }
/*
  //Test
  printf("\nTest des coups possible :\n");
  int taille;
  p_move* moves = possible_movements(&b, 'B', &taille);
  int l, k;
  printf("%d coups trouvés :\n", taille);
  for(l = 0; l < taille; l++){
    for(k=0; k < moves[l].length; k++){
      if(k == moves[l].length/2)
	printf(": ");
      printf("%s ", moves[l].squares[k]);
    }
    putchar('\n');
  }
  */
  return 0;
}

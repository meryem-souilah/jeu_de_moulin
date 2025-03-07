#ifndef PION_H
#define PION_H
#include <stdbool.h>

#include "joueur.h"

#define TAILLE 7
#define NOMBRE_PIONS 9

void afficher_Plateau(char plateau[TAILLE][TAILLE]);
bool est_position_valide(int x, int y, char plateau[TAILLE][TAILLE]);
void capturer_double_moulin(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire);
void placer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire);
bool verifier_double_moulin(int x, int y, char plateau[TAILLE][TAILLE]);
void capturer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire);
bool verifier_moulin(int x, int y, char plateau[TAILLE][TAILLE]);
bool verifier_victoire(Joueur *adversaire);
void deplacer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire);
void tour_de_jeu(Joueur *joueur1, Joueur *joueur2, char plateau[TAILLE][TAILLE]);

#endif

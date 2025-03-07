#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ordinateur.h"

void ia_jouer_coup(char plateau[TAILLE][TAILLE], int joueur) {
    int ligne, colonne;

    // Boucle pour trouver une position valide
    do {
        ligne = rand() % TAILLE;
        colonne = rand() % TAILLE;
    } while (plateau[ligne][colonne] != '*');  // Vérifie si la case est libre et valide

    // Place le pion de l'IA
    plateau[ligne][colonne] = (joueur == 1) ? 'X' : 'O';

    printf("IA Play in (%d, %d)\n", ligne, colonne);
}


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Plateau.h"

void initialiser_Plateau(char plateau[TAILLE][TAILLE]) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            plateau[i][j] = ' ';
        }
    }

    // Place les positions valides pour le plateau
    plateau[0][0] = plateau[0][3] = plateau[0][6] = '*';
    plateau[1][1] = plateau[1][3] = plateau[1][5] = '*';
    plateau[2][2] = plateau[2][3] = plateau[2][4] = '*';
    plateau[3][0] = plateau[3][1] = plateau[3][2] = plateau[3][4] = plateau[3][5] = plateau[3][6] = '*';
    plateau[4][2] = plateau[4][3] = plateau[4][4] = '*';
    plateau[5][1] = plateau[5][3] = plateau[5][5] = '*';
    plateau[6][0] = plateau[6][3] = plateau[6][6] = '*';
}

void afficher_Plateau(char plateau[TAILLE][TAILLE]) {
    printf("\n=== Plateau du Jeu de Moulin ===\n\n");

    // Affiche les indices des colonnes
    printf("  ");
    for (int i = 0; i < TAILLE; i++) {
        printf(" %d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        // Affiche l'indice de la ligne
        printf("%d ", i);

        for (int j = 0; j < TAILLE; j++) {
            printf(" %c ", plateau[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

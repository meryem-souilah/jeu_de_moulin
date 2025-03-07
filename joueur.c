#include <stdio.h>
#include <stdlib.h>
#include "joueur.h"

void initialiser_joueur(Joueur *j1, Joueur *j2) {
    printf("Please enter the name of player 1:");
    scanf(" %49[^\n]", j1->nom);
    getchar();

    printf("Please enter the name of player 2: ");
    scanf(" %49[^\n]", j2->nom);
    getchar(); // Supprime le \n du buffer

    j1->id = 1;
    j2->id = 2;
    j1->symbole = 'X';
    j2->symbole = 'O';
    j1->pions = NOMBRE_PIONS;
    j2->pions = NOMBRE_PIONS;
}

// Retourne aléatoirement le joueur qui commence
Joueur* random_joueur(Joueur *j1, Joueur *j2) {
    return (rand() % 2) ? j1 : j2;
}

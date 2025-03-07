#ifndef JOUEUR_H
#define JOUEUR_H

#define NOMBRE_PIONS 9

typedef struct {
    char nom[50];       // Nom du joueur
    int id;             // ID du joueur (1 ou 2)
    char symbole;       // Symbole du joueur (X ou O)
    int pions;          // Nombre de pions restants
    int estIA;          // 1 si c'est l'IA, 0 si c'est un joueur humain
} Joueur;

void initialiser_joueur(Joueur *j1, Joueur *j2);
Joueur* random_joueur(Joueur *j1, Joueur *j2);

#endif // JOUEUR_H

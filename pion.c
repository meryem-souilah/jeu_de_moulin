#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pion.h"
#include "joueur.h"

bool est_position_valide(int x, int y, char plateau[TAILLE][TAILLE]) {
    return (x >= 0 && x < TAILLE && y >= 0 && y < TAILLE && plateau[x][y] == '*');
}
void placer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire) {
    if (joueur->pions == 0) {
        printf("%s has no more pieces to place.\n", joueur->nom);
        return;
    }

    int x, y;
    bool placementValide = false;

    while (!placementValide) {
        printf("%s, enter the piece coordinates (x,y) : ", joueur->nom);
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (est_position_valide(x, y, plateau)) {
            plateau[x][y] = (joueur->id == 1) ? 'X' : 'O';
            joueur->pions--; // Décrémenter les pions après placement
            placementValide = true;
            afficher_Plateau(plateau);

            bool double_moulin_detecte = verifier_double_moulin(x, y, plateau);
            bool moulin_detecte = verifier_moulin(x, y, plateau);

            if (double_moulin_detecte) {
                printf("Double mill detected! \n");
                capturer_double_moulin(joueur, plateau, adversaire);
            } else if (moulin_detecte) {
                printf("A mill has been formed!\n");
                capturer_pion(joueur, plateau, adversaire);
            }
        } else {
            printf("Invalid position, please try again.\n");
        }
    }
}

bool verifier_moulin(int x, int y, char plateau[TAILLE][TAILLE]) {
    char symbole = plateau[x][y];
    if (symbole == '*') return false;

    int alignements[16][3][2] = {
        {{0, 0}, {0, 3}, {0, 6}}, {{6, 0}, {6, 3}, {6, 6}},
        {{0, 0}, {3, 0}, {6, 0}}, {{0, 6}, {3, 6}, {6, 6}},
        {{1, 1}, {1, 3}, {1, 5}}, {{5, 1}, {5, 3}, {5, 5}},
        {{1, 1}, {3, 1}, {5, 1}}, {{1, 5}, {3, 5}, {5, 5}},
        {{2, 2}, {2, 3}, {2, 4}}, {{4, 2}, {4, 3}, {4, 4}},
        {{2, 2}, {3, 2}, {4, 2}}, {{2, 4}, {3, 4}, {4, 4}},
        {{0, 3}, {1, 3}, {2, 3}}, {{4, 3}, {5, 3}, {6, 3}},
        {{3, 0}, {3, 1}, {3, 2}}, {{3, 4}, {3, 5}, {3, 6}}
    };

    for (int i = 0; i < 16; i++) {
        bool estMoulin = true, appartientMoulin = false;

        for (int j = 0; j < 3; j++) {
            int px = alignements[i][j][0], py = alignements[i][j][1];

            if (plateau[px][py] != symbole) {
                estMoulin = false;
            }
            if (px == x && py == y) {
                appartientMoulin = true;
            }
        }

        if (estMoulin && appartientMoulin) {
            return true;
        }
    }
    return false;
}
bool verifier_double_moulin(int x, int y, char plateau[TAILLE][TAILLE]) {
    char symbole = plateau[x][y];
    if (symbole == '*') return false;

    int alignements[16][3][2] = {
        {{0, 0}, {0, 3}, {0, 6}}, {{6, 0}, {6, 3}, {6, 6}},
        {{0, 0}, {3, 0}, {6, 0}}, {{0, 6}, {3, 6}, {6, 6}},
        {{1, 1}, {1, 3}, {1, 5}}, {{5, 1}, {5, 3}, {5, 5}},
        {{1, 1}, {3, 1}, {5, 1}}, {{1, 5}, {3, 5}, {5, 5}},
        {{2, 2}, {2, 3}, {2, 4}}, {{4, 2}, {4, 3}, {4, 4}},
        {{2, 2}, {3, 2}, {4, 2}}, {{2, 4}, {3, 4}, {4, 4}},
        {{0, 3}, {1, 3}, {2, 3}}, {{4, 3}, {5, 3}, {6, 3}},
        {{3, 0}, {3, 1}, {3, 2}}, {{3, 4}, {3, 5}, {3, 6}}
    };

    int compteurMoulins = 0;

    for (int i = 0; i < 16; i++) {
        bool estMoulin = true, appartientMoulin = false;

        for (int j = 0; j < 3; j++) {
            int px = alignements[i][j][0], py = alignements[i][j][1];

            if (plateau[px][py] != symbole) {
                estMoulin = false;
            }
            if (px == x && py == y) {
                appartientMoulin = true;
            }
        }

        if (estMoulin && appartientMoulin) {
            compteurMoulins++;
        }
    }

    return compteurMoulins >= 2;
}

bool pion_proteger(int row, int col, char player, char plateau[TAILLE][TAILLE]) {
    // Définition des moulins (lignes et colonnes du plateau)
    int moulin[16][3][2] = {
        {{0, 0}, {0, 3}, {0, 6}}, // Ligne 0
        {{1, 1}, {1, 3}, {1, 5}}, // Ligne 1
        {{2, 2}, {2, 3}, {2, 4}}, // Ligne 2
        {{3, 0}, {3, 1}, {3, 2}}, // Ligne 3
        {{3, 4}, {3, 5}, {3, 6}}, // Ligne 3
        {{4, 2}, {4, 3}, {4, 4}}, // Ligne 4
        {{5, 1}, {5, 3}, {5, 5}}, // Ligne 5
        {{6, 0}, {6, 3}, {6, 6}}, // Ligne 6
        {{0, 0}, {3, 0}, {6, 0}}, // Colonne 0
        {{1, 1}, {3, 1}, {5, 1}}, // Colonne 1
        {{2, 2}, {3, 2}, {4, 2}}, // Colonne 2
        {{0, 3}, {1, 3}, {2, 3}}, // Colonne 3
        {{4, 3}, {5, 3}, {6, 3}}, // Colonne 3
        {{2, 4}, {3, 4}, {4, 4}}, // Colonne 4
        {{1, 5}, {3, 5}, {5, 5}}, // Colonne 5
        {{0, 6}, {3, 6}, {6, 6}}  // Colonne 6
    };

    // Parcours des moulins et vérification si le pion fait partie d'un moulin protégé
    for (int i = 0; i < 16; i++) {
        // Vérifier si la case donnée fait partie d'un moulin
        if ((moulin[i][0][0] == row && moulin[i][0][1] == col) ||
            (moulin[i][1][0] == row && moulin[i][1][1] == col) ||
            (moulin[i][2][0] == row && moulin[i][2][1] == col)) {

            // Vérification si le moulin est formé et protégé pour le joueur
            if (verifier_moulin(moulin[i][0][0], moulin[i][0][1], plateau) &&
                verifier_moulin(moulin[i][1][0], moulin[i][1][1], plateau) &&
                verifier_moulin(moulin[i][2][0], moulin[i][2][1], plateau)) {
                return true;
            }
        }
    }

    return false;
}


bool verifier_victoire(Joueur *adversaire) {
    return adversaire->pions < 3;
}

void deplacer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire) {
    int x1, y1, x2, y2;
    bool mouvementValide = false;

    while (!mouvementValide) {
        // Demander les coordonnées de la pièce à déplacer
        printf("%s, enter the coordinates of the piece to move (x, y): ", joueur->nom);
        if (scanf("%d %d", &x1, &y1) != 2) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue;
        }

        // Vérifier si la case est occupée par le pion du joueur
        if (plateau[x1][y1] != ((joueur->id == 1) ? 'X' : 'O')) {
            printf("No piece at this position. Try again.\n");
            continue;
        }

        // Demander les nouvelles coordonnées
        printf("Enter the new coordinates (x, y): ");
        if (scanf("%d %d", &x2, &y2) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        if (est_position_valide(x2, y2, plateau)) {
            // Effectuer le déplacement
            plateau[x2][y2] = plateau[x1][y1];
            plateau[x1][y1] = '*';
            mouvementValide = true;
            afficher_Plateau(plateau);

            if (verifier_moulin(x2, y2, plateau)) {
                printf("A mill has been formed after the move!\n");
                capturer_pion(joueur, plateau, adversaire);
            }

            if (verifier_double_moulin(x2, y2, plateau)) {
                printf("Double mill detected!\n");
                capturer_double_moulin(joueur, plateau, adversaire);
            }
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}


void capturer_pion(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire) {
    if (adversaire->pions < 3) return;

    int x, y;
    bool captureValide = false;
    char pionAdverse = (joueur->id == 1) ? 'O' : 'X';

    while (!captureValide) {
        printf("%s,  enter the coordinates of the opponent's piece to capture (x,y) : ", joueur->nom);
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        // Vérifier si le pion choisi appartient à l'adversaire
        if (plateau[x][y] == pionAdverse) {
            // Vérifier si le pion adverse est protégé par un moulin
            if (pion_proteger(x, y, pionAdverse, plateau)) {
                printf(" This piece is part of a protected mill and cannot be captured..\n");
                captureValide = true;
            } else {
                plateau[x][y] = '*';
                adversaire->pions--;
                captureValide = true;
                printf("the piece (%d, %d) is captured !\n", x, y);
                afficher_Plateau(plateau);
            }
        } else {
            printf("Invalid selection. Choose a valid opponent's piece..\n");
        }
    }
}
void capturer_double_moulin(Joueur *joueur, char plateau[TAILLE][TAILLE], Joueur *adversaire) {
    if (adversaire->pions < 3) return;

    int x, y, captures = 0;
    char pionAdverse = (joueur->id == 1) ? 'O' : 'X';

    printf("\n%s has formed a double mill! Capture two opponent's pieces.\n", joueur->nom);

    while (captures < 2) {
        printf("Enter the coordinates of the opponent's piece to capture (x y) : ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        // Vérifier si la case contient bien un pion adverse
        if (plateau[x][y] == pionAdverse) {
            // Vérifier si le pion adverse est protégé par un moulin
            if (pion_proteger(x, y, pionAdverse, plateau)) {
                printf("This piece is in a protected mill. Choose another one.\n");
            } else {
                plateau[x][y] = '*';
                adversaire->pions--;
                captures++;
                printf("The piece (%d, %d) has been captured!\n", x, y);
                afficher_Plateau(plateau);
            }
        } else {
            printf("Invalid selection. Choose a valid opponent's piece.\n");
        }
    }
}

void tour_de_jeu(Joueur *joueur1, Joueur *joueur2, char plateau[TAILLE][TAILLE]) {
    printf("\nStart of the piece placement phase.\n");

    for (int i = 0; i < 9; i++) {
        placer_pion(joueur1, plateau, joueur2);
        placer_pion(joueur2, plateau, joueur1);
    }

    while (1) {
        deplacer_pion(joueur1, plateau, joueur2);
        if (verifier_victoire(joueur2)) {
            printf("%s has won !\n", joueur1->nom);
            break;
        }

        deplacer_pion(joueur2, plateau, joueur1);
        if (verifier_victoire(joueur1)) {
            printf("%s has won !\n", joueur2->nom);
            break;
        }
    }
}

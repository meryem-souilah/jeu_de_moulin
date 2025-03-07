#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "menu.h"
#include "Plateau.h"
#include "joueur.h"
#include "pion.h"
#include "ordinateur.h"

int main() {
    int choix;
    char plateau[TAILLE][TAILLE];
    Joueur joueur1, joueur2;
    Joueur *joueurActuel, *adversaire;
    bool contreIA = false;

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires

    do {
        afficherMenu();
        if (scanf("%d", &choix) != 1) {
            printf("Invalid entry, Try again.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choix) {
            case 1: {  // Lancer le jeu
                afficherMenuPlay();
                int choixPlay;
                if (scanf("%d", &choixPlay) != 1) {
                    printf("Invalid entry, back to the main menu.\n");
                    while (getchar() != '\n');
                    break;
                }

                if (choixPlay == 1) {
                    printf("'Humain Vs IA'.\n");
                    contreIA = true;
                } else if (choixPlay == 2) {
                    printf(" 'Humain Vs Humain.\n");
                    contreIA = false;
                } else {
                    printf("Back to main menu.\n");
                    break;
                }

                // Initialisation des joueurs
                initialiser_joueur(&joueur1, &joueur2);
                joueur2.estIA = contreIA;  // Marque le joueur 2 comme IA si nécessaire

                // Initialisation du plateau
                initialiser_Plateau(plateau);

                // Affichage du plateau vide
                afficher_Plateau(plateau);

                // Sélection aléatoire du premier joueur
                joueurActuel = random_joueur(&joueur1, &joueur2);
                adversaire = (joueurActuel == &joueur1) ? &joueur2 : &joueur1;
                printf("%s starts the game!\n", joueurActuel->nom);

                // Phase de placement des pions
                for (int i = 0; i < NOMBRE_PIONS * 2; i++) {
                    printf("\n%s, It's your turn to put the pawn\n", joueurActuel->nom);

                    if (joueurActuel->estIA) {
                        ia_jouer_coup(plateau, joueurActuel);
                    } else {
                        placer_pion(joueurActuel, plateau, adversaire);
                    }

                    // Changer de joueur après chaque placement
                    Joueur *temp = joueurActuel;
                    joueurActuel = adversaire;
                    adversaire = temp;
                }

                // Phase de déplacement des pions
                bool jeuEnCours = true;
                while (jeuEnCours) {
                    afficher_Plateau(plateau);

                    printf("\n%s, It's your turn to play.\n", joueurActuel->nom);

                    if (joueurActuel->estIA) {
                        ia_jouer_coup(plateau, joueurActuel);
                    } else {
                        tour_de_jeu(joueurActuel, adversaire, plateau);
                    }

                    // Changer de joueur
                    Joueur *temp = joueurActuel;
                    joueurActuel = adversaire;
                    adversaire = temp;
                }
                break;
            }

            case 2:  // Quitter le jeu
                printf("Goodbye!\n");
                return 0;

            case 3:  // Afficher les règles du jeu
                gererChoixgamerules();
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }

    } while (1);

    return 0;
}

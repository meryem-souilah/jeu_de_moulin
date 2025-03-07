#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
// Fonction pour afficher le menu principal
void afficherMenu() {
    printf("===== MENU =====\n");
    printf("1. Play\n");
    printf("2. Exit\n");
    printf("3. Game rules\n");
    printf("================\n");
    printf("Enter your choice: ");
}

// Fonction pour afficher le sous-menu "Play"
void afficherMenuPlay() {
    printf("=====================================\n");
    printf("              Play           \n");
    printf("=====================================\n");
    printf("1. Play against computer\n");
    printf("2. Two players game\n");
    printf("3. Return to main menu\n");
    printf("=====================================\n");
    printf("Choose an option (1-3): ");
}

void gererChoixgamerules() {
    printf("=====================================\n");
    printf("              Game Rules          \n");
    printf("=====================================\n");
    printf("R1: Players take turns placing their 9 pieces on the board, aiming to form a (mill) (3 pieces in a row).\n");
    printf("R2: Once all pieces are placed, players move their pieces to adjacent empty spaces to form new mills or block the opponent.\n");
    printf("R3: When one of the players forms a mill, they can capture an opponent's piece, provided that it is not part of a protected alignment.\n");
    printf("R4: A player wins by reducing the opponent to 2 pieces or blocking all their moves.\n");
}

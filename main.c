#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_WORDS 1000      // max mots dans la liste
#define MAX_WORD_LENGTH 50  // max taille mot
#define MAX_ERRORS 6

int main() {
    FILE *fichier = fopen("wordlist.txt", "r");
    if (!fichier) {
        printf("Erreur : impossible d'ouvrir wordlist.txt\n");
        return 1;
    }

    char mots[MAX_WORDS][MAX_WORD_LENGTH];
    int nb_mots = 0;

    while (fgets(mots[nb_mots], MAX_WORD_LENGTH, fichier) != NULL) {
        size_t len = strlen(mots[nb_mots]);
        if (len > 0 && mots[nb_mots][len - 1] == '\n') {
            mots[nb_mots][len - 1] = '\0';
        }
        nb_mots++;
        if (nb_mots >= MAX_WORDS) break;
    }
    fclose(fichier);

    if (nb_mots == 0) {
        printf("La liste de mots est vide.\n");
        return 1;
    }

    srand(time(NULL));
    int index = rand() % nb_mots;

    char* mot_secret = mots[index];
    int longueur = strlen(mot_secret);
    char lettres_trouvees[longueur + 1];
    int erreurs = 0;
    int i;
    char lettre;
    int gagne = 0;

    for (i = 0; i < longueur; i++) {
        lettres_trouvees[i] = '_';
    }
    lettres_trouvees[longueur] = '\0';

    printf("Bienvenue dans le jeu du pendu !\n");

    while (erreurs < MAX_ERRORS && !gagne) {
        int trouve = 0;

        printf("\nMot : ");
        for (i = 0; i < longueur; i++) {
            printf("%c ", lettres_trouvees[i]);
        }
        printf("\n");

        printf("Propose une lettre : ");
        scanf(" %c", &lettre);
        lettre = tolower(lettre);

        for (i = 0; i < longueur; i++) {
            if (mot_secret[i] == lettre && lettres_trouvees[i] == '_') {
                lettres_trouvees[i] = lettre;
                trouve = 1;
            }
        }

        if (!trouve) {
            erreurs++;
            printf("Lettre incorrecte ! Erreurs : %d/%d\n", erreurs, MAX_ERRORS);
        } else {
            printf("Bonne lettre !\n");
        }

        gagne = 1;
        for (i = 0; i < longueur; i++) {
            if (lettres_trouvees[i] == '_') {
                gagne = 0;
                break;
            }
        }
    }

    if (gagne) {
        printf("\nFélicitations, tu as gagné ! Le mot était \"%s\".\n", mot_secret);
    } else {
        printf("\nDommage, tu as perdu. Le mot était \"%s\".\n", mot_secret);
    }

    return 0;
}

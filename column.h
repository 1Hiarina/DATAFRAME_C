#ifndef COLUMN_H
#define COLUMN_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REALOC_SIZE 256
#define MAX_COLUMNS 100

// création du type column
typedef struct column {
    char titre[100];
    int *tab;
    int TAILLE_LOGIQUE;
    int TAILLE_PHYSIQUE;
} COLUMN;


// fonction qui crée une colonne
COLUMN* create_column(const char *titre) {

    COLUMN *p = malloc(sizeof(COLUMN));
    strncpy(p->titre, titre, sizeof(p->titre) - 1);
    p->titre[sizeof(p->titre) - 1] = '\0';
    p->tab = calloc(REALOC_SIZE, sizeof(int));
    p->TAILLE_LOGIQUE = 0;
    p->TAILLE_PHYSIQUE = REALOC_SIZE;
    return p;

}

// fonction pour inserer une valeur
int insert_value(COLUMN *col, int value) {
    if (col->TAILLE_LOGIQUE == col->TAILLE_PHYSIQUE) {
        int nv_capacite = col->TAILLE_PHYSIQUE + REALOC_SIZE;
        int* temp = realloc(col->tab, nv_capacite * sizeof(int));
        if (temp == NULL) {
            return 0;
        }
        col->tab = temp;
        col->TAILLE_PHYSIQUE = nv_capacite;
    }
    col->tab[col->TAILLE_LOGIQUE++] = value;
    return 1;
}

// fonction pour supprimer une valeur
void delete_column(COLUMN **col) {
    if ((*col)->tab != NULL) {
        free((*col)->tab);
    }
    free(*col);
    *col = NULL;
}


// fonction qui affiche une valeur
void print_col(COLUMN *col) {
    for (int i = 0; i < col->TAILLE_LOGIQUE; i++) {
        printf("[%d] %d\n", i, col->tab[i]);
    }
}

// fonction qui cherche le nombre d'occurence d'un nombre dans la colonne
int nb_occurence(COLUMN *col, int val) {

    int i;
    int nb = 0;
    for (i=0; i < col->TAILLE_LOGIQUE; i++) {
        if (col->tab[i] == val) {
            nb++;
        }
    }
    if (nb == 0) {
        return printf("No occurence of this value found");
    }
    return nb;
}

// fonction qui cherche une valeure à une position souhaitée

int value_at_position(COLUMN *col, int position) {

    int i;
    if (position > col->TAILLE_LOGIQUE) {
        return 0;
    }
    for (i=0; i < col->TAILLE_LOGIQUE; i++) {
        if (i == position) {
            return col->tab[i];
        }
    }

}

// fonction pour trouver le nombre de valeur plus grande que la valeur rentré
int value_grader(COLUMN *col, int val) {
    int i;
    int nb = 0;
    for (i=0; i < col->TAILLE_LOGIQUE; i++) {
        if (col->tab[i] > val) {
            nb++;
        }
    }

    return nb;
}
// fonction pour trouver le nombre de valeur plus petite que la valeur rentré
int value_lower(COLUMN *col, int val) {
    int i;
    int nb = 0;
    for (i=0; i < col->TAILLE_LOGIQUE; i++) {
        if (col->tab[i] < val) {
            nb++;
        }
    }

    return nb;

}

// fonction pour trouver le nombre de valeur égale à la valeur rentré
int value_equal(COLUMN *col, int val) {
    int i;
    int nb = 0;
    for (i=0; i < col->TAILLE_LOGIQUE; i++) {
        if (col->tab[i] == val) {
            nb++;
        }
    }

    return nb;

}

#endif //COLUMN_H

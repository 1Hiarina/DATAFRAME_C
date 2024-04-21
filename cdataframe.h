#ifndef CDATAFRAME_CDATAFRAME_H
#define CDATAFRAME_CDATAFRAME_H

#include "column.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    COLUMN *colonnes[MAX_COLUMNS];
    int nombre_colonnes;
} CDataframe;

// Crée et initialise un nouveau dataframe
CDataframe *create_dataframe() {
    CDataframe *df = malloc(sizeof(CDataframe));
    df->nombre_colonnes = 0;
    for (int i = 0; i < MAX_COLUMNS; ++i) {
        df->colonnes[i] = NULL;
    }
    return df;
}

// Ajoute une colonne au dataframe
int add_column(CDataframe *df, COLUMN *col) {
    if (df->nombre_colonnes < MAX_COLUMNS) {
        df->colonnes[df->nombre_colonnes++] = col;
        return 1;
    }
    return 0;
}

// Affiche toutes les colonnes et leurs valeurs dans le dataframe
void print_dataframe(CDataframe *df) {
    for (int i = 0; i < df->nombre_colonnes; i++) {
        COLUMN *col = df->colonnes[i];
        printf("Column %d: %s\n", i+1, col->titre);
        printf("Values:\n");
        for (int j = 0; j < col->TAILLE_LOGIQUE; j++) {
            printf("[%d] %d\n", j, col->tab[j]);
        }
    }
}

// Affiche une ligne spécifique jusqu'à une limite donnée pour toutes les colonnes
void print_limited_row(CDataframe *df, int limit_line) {
    for (int i = 0; i < df->nombre_colonnes; i++) {
        COLUMN *col = df->colonnes[i];
        printf("Column %d: %s\n", i+1, col->titre);
        printf("Values:\n");
        for (int j = 0; j < col->TAILLE_LOGIQUE; j++) {
            if (j <= limit_line) {
                printf("[%d] %d\n", j, col->tab[j]);
            }
        }
    }
}

// Affiche toutes les valeurs jusqu'à une colonne spécifique
void print_limited_column (CDataframe *df, int limited_col) {
    for (int i = 0; i < df->nombre_colonnes; i++) {
        if (i <= limited_col) {
            COLUMN *col = df->colonnes[i];
            printf("Column %d: %s\n", i + 1, col->titre);
            printf("Values:\n");
            for (int j = 0; j < col->TAILLE_LOGIQUE; j++) {
                printf("[%d] %d\n", j, col->tab[j]);
            }
        }
    }
}

// Ajoute une ligne de valeurs au dataframe
int add_row(CDataframe *df, int *values) {
    if (df == NULL || values == NULL) {
        return 0;
    }

    for (int i = 0; i < df->nombre_colonnes; i++) {
        if (!insert_value(df->colonnes[i], values[i])) {
            return 0;
        }
    }
    return 1;
}

// Supprime une ligne spécifique du dataframe
int delete_row(CDataframe *df, int row_index) {
    if (df == NULL || row_index < 0) {
        return 0;
    }

    for (int i = 0; i < df->nombre_colonnes; i++) {
        COLUMN *col = df->colonnes[i];
        if (row_index >= col->TAILLE_LOGIQUE) {
            continue;
        }

        for (int j = row_index; j < col->TAILLE_LOGIQUE - 1; j++) {
            col->tab[j] = col->tab[j + 1];
        }
        col->TAILLE_LOGIQUE--;
    }
    return 1;
}

// Renomme une colonne spécifique dans le dataframe
int rename_column(CDataframe *df, int column_index, const char *nw_name) {
    if (df == NULL || nw_name == NULL || column_index < 0 || column_index >= df->nombre_colonnes) {
        return 0;
    }

    COLUMN *col = df->colonnes[column_index];
    if (col == NULL) {
        return 0;
    }

    strncpy(col->titre, nw_name, sizeof(col->titre) - 1);
    col->titre[sizeof(col->titre) - 1] = '\0';
    return 1;
}

// Vérifie si une valeur spécifique existe dans le dataframe
int contains_value(CDataframe *df, int value) {
    for (int i = 0; i < df->nombre_colonnes; i++) {
        COLUMN *col = df->colonnes[i];
        if (col != NULL) {
            for (int j = 0; j < col->TAILLE_LOGIQUE; j++) {
                if (col->tab[j] == value) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Modifie la valeur à un emplacement spécifique dans le dataframe
int change_value_at(CDataframe *df, int column_index, int row_index, int new_value) {
    if (df == NULL || column_index < 0 || column_index >= df->nombre_colonnes) {
        return 0;
    }

    COLUMN *col = df->colonnes[column_index];
    if (col == NULL || row_index < 0 || row_index >= col->TAILLE_LOGIQUE) {
        return 0;
    }

    col->tab[row_index] = new_value;
    return 1;
}

#endif //CDATAFRAME_CDATAFRAME_H

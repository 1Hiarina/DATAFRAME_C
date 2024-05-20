#include "column.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// ***** COLONNE **** //

// Fonction pour créer une colonne
COLUMN *create_column(ENUM_TYPE type, char *col_titre) {

    // Allocation de la mémoire pour la colonne
    COLUMN *col = (COLUMN*) malloc(sizeof(COLUMN));


    // Vérification si malloc a réussi
    if (col == NULL)
        return NULL;

    // Allocation de la mémoire pour le titre de la colonne
    col->titre = (char*) malloc(strlen(col_titre) + 1);

    if (col->titre == NULL) {
        free(col);
        return NULL;
    }

    // Copie du titre dans la mémoire allouée
    strcpy(col->titre, col_titre);

    // Initialisation des autres membres de la structure
    col->data = NULL;
    col->column_type = type;
    col->size = 0;
    col->max_size = 0;

    return col;
}

// IMPORTANT //
// Fonction pour inserer une valeur
int insert_value(COLUMN *col, void *value) {

    if (col->size >= col->max_size) {

        // Augmentation de la capacité de stockage si nécessaire

        col->data = realloc(col->data, (col->max_size + REALOC_SIZE) * sizeof(void *));
        col->max_size += REALOC_SIZE;
    }

    // Détermination de la taille de l'élément à allouer avec un switch case

    if (value == NULL) {
        col->data[col->size] = NULL;

    } else {
        switch (col->column_type) {

            case INT:
                col->data[col->size] = (COL_TYPE *) (int *) malloc(sizeof(int));
                *((int *) col->data[col->size]) = *((int *) value);
                break;

            case UINT:
                col->data[col->size] = (COL_TYPE *)(unsigned int *) malloc(sizeof(unsigned int));
                *((unsigned int *) col->data[col->size]) = *((unsigned int *) value);
                break;

            case CHAR:
                col->data[col->size] = (COL_TYPE *)(char *) malloc(sizeof(char));
                *((char *) col->data[col->size]) = *((char *) value);
                break;

            case FLOAT:
                col->data[col->size] = (COL_TYPE *)(float *) malloc(sizeof(float));
                *((float *) col->data[col->size]) = *((float *) value);
                break;

            case DOUBLE:
                col->data[col->size] = (COL_TYPE *)(double *) malloc(sizeof(double));
                *((double *) col->data[col->size]) = *((double *) value);
                break;

            case STRING:
                col->data[col->size] = (char *)malloc(strlen((char *) value) + 1);
                strcpy((char *) col->data[col->size], (char *) value);
                break;

            default:
                return 0;
        }
    }

    col->size++;

    return 1;
}

// supprimer une colonne
void delete_column(COLUMN **col) {

    for (int i = 0; i < (*col)->size; i++) {
        free((*col)->data[i]);
    }

    if ((*col)->data != NULL) {
        free((*col)->data);
    }

    free((*col)->titre);
    free(*col);
    *col = NULL;
}

// convertir une valeur de n'importe quel type en chaine de caractèere
void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {

    // vérification si col n'est pas null

    if (col->data[i] == NULL) {
        snprintf(str, size, "NULL");
        return;
    }

    // switch case afin d'avoir le bon &
    switch(col->column_type) {
        case INT:
            snprintf(str, size, "%d", *((int *) col->data[i]));
            break;
        case UINT:
            snprintf(str, size, "%u", *((unsigned int*) col->data[i]));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char *) col->data[i]));
            break;
        case FLOAT:
            snprintf(str, size, "%f", *((float *) col->data[i]));
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", *((double *) col->data[i]));
            break;
        case STRING:
            strcpy(str, (char*) col->data[i]);
            break;

        default:
            snprintf(str, size, "Default type");
            break;

    }
}

// print usuel d'affichage  de colonne
void print_col(COLUMN* col){

    printf("\n");
    printf("Titre de la colonne : %s\n", col->titre);
    printf("Contenu : \n");
    printf("\n");


    for (int i = 0; i < col->size; i++){

        char *str;
        int size;

        // ** ATTENTION ** //

        // allocation de la mémoire de la chaine de caractère en deux fois pour éviter d'alouer de la mémoire inutilement

        // => doonc encore un switch case


        if (col->data[i] == NULL) {
            size = 5;
        } else {

            switch(col->column_type) {
                case INT:
                    size = snprintf(NULL, 0, "%d", *((int *) col->data[i])) + 1;
                    break;
                case UINT:
                    size = snprintf(NULL, 0, "%u", *((unsigned int*) col->data[i])) + 1;
                    break;
                case CHAR:
                    size = 2;
                    break;
                case FLOAT:
                    size = snprintf(NULL, 0, "%f", *((float *) col->data[i])) + 1;
                    break;
                case DOUBLE:
                    size = snprintf(NULL, 0, "%lf", *((double *) col->data[i])) + 1;
                    break;
                case STRING:
                    size = strlen((char*) col->data[i]) + 1;
                    break;

                default:
                    size = 13;
                    break;
            }
        }

        str = (char *)malloc(size * sizeof(char));

        convert_value(col, i, str, size);
        printf("[%d] %s\n", i, str);
        free(str);
    }
}

// print avec une limite de ligne pour la fonction print limite ligne du dataframe
void print_limite_col_lig(COLUMN *col, int limite) {

    if (limite > col->size) {
        print_col(col);
    }

    else {

        printf("\n");
        printf("Titre de la colonne : %s\n", col->titre);
        printf("Contenu : \n");
        printf("\n");


        for (int i = 0; i < limite; i++){

            char *str;
            int size;


            if (col->data[i] == NULL) {
                size = 5;
            } else {

                switch(col->column_type) {
                    case INT:
                        size = snprintf(NULL, 0, "%d", *((int *) col->data[i])) + 1;
                        break;
                    case UINT:
                        size = snprintf(NULL, 0, "%u", *((unsigned int*) col->data[i])) + 1;
                        break;
                    case CHAR:
                        size = 2;
                        break;
                    case FLOAT:
                        size = snprintf(NULL, 0, "%f", *((float *) col->data[i])) + 1;
                        break;
                    case DOUBLE:
                        size = snprintf(NULL, 0, "%lf", *((double *) col->data[i])) + 1;
                        break;
                    case STRING:
                        size = strlen((char*) col->data[i]) + 1;
                        break;

                    default:
                        size = 13;
                        break;
                }
            }

            str = (char *)malloc(size * sizeof(char));

            convert_value(col, i, str, size);
            printf("[%d] %s\n", i, str);
            free(str);
        }
    }
}





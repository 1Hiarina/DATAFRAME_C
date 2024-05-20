#include "cdataframe.h"
#include "list.h"
#include "column.h"

// ****** !! FONCTIONALITÉES INTIAL !! ****** //


// création d'un dataframe

CDATAFRAME *create_dataframe(ENUM_TYPE *cdtype, int size) {

    list *lst_dataframe = lst_create_list();

    for (int i = 0; i < size; i++) {
        char *p_titre = (char*) malloc(50);
        COLUMN *col = create_column(*cdtype, p_titre);
        lnode *pnew = lst_create_lnode(col);
        lst_insert_tail(lst_dataframe, pnew);
    }

    return lst_dataframe;
}

// supprimer un dataframe (func déjà fait dans le sujet)

void deletete_dataframe(CDATAFRAME **cdf) {
    lst_delete_list(*cdf);
}

// supprimer une colonne d'un dataframe

void delete_column_dataframe(CDATAFRAME *cdf, char *col_name) {

    lnode *p_col = cdf->head;

    while (p_col->next != NULL) {

        if (p_col->data->titre == col_name) {
            delete_column(&(p_col->data));
        }
        p_col = p_col->next;
    }
}

// func pour avoir le nombre de colonne d'un dataframe

int get_cdataframe_cols_size(CDATAFRAME *cdf) {

    lnode *p_col = cdf->head;

    int nb_col = 0;

    while(p_col->next != NULL){
        p_col = p_col->next;
        nb_col++;
    }

    return (nb_col + 1);
}



// ****** !! AUTRES FONCTIONALITÉES !! ****** //


// ****** ALIMENTATION ****** //

void user_dataframe(CDATAFRAME *cdf) {

    int size_cdf = get_cdataframe_cols_size(cdf);
    lnode *cdataframe = cdf->head;

    for (int i = 0; i < size_cdf; i++) {

        int nb_lig;
        int var_sec = 0;

        printf("Entrez le nom de la colonne [%d] (max 50 caractères): ", i);

        scanf("%s", cdataframe->data->titre);


        // saisie sécurisée pour la saisie de colonne
        while (var_sec == 0) {

            printf("Entrez le nombre de lignes que souhaitez dans votre colonne (nombre positif) : ");

            if (scanf("%d", &nb_lig) == 1 && nb_lig > 0) {
                var_sec = 1;

            } else {
                printf("Saisie invalide. Veuillez réessayer.\n");
                while (getchar() != '\n'); // Efface le buffer jusqu'à la fin de ligne pour éviter une boucle infinie ( copié sur internet)
            }
        }



        for (int k = 0; k < nb_lig; k++) {

            printf("Entrez une valeur pour la ligne [%d][%d]: ", i, k);

            void *value_col;

            switch (cdataframe->data->column_type) {
                case INT:
                    value_col = malloc(sizeof(int));
                    scanf("%d", (int*)value_col);

                    break;
                case UINT:
                    value_col = malloc(sizeof(unsigned int));
                    scanf("%u", (unsigned int*)value_col);

                    break;
                case CHAR:
                    value_col = malloc(sizeof(char));
                    scanf(" %c", (char*)value_col);

                    break;
                case FLOAT:
                    value_col = malloc(sizeof(float));
                    scanf("%f", (float*)value_col);

                    break;
                case DOUBLE:
                    value_col = malloc(sizeof(double));
                    scanf("%lf", (double*)value_col);
                    break;
                case STRING:
                    value_col = malloc(100);
                    scanf("%99s", (char*)value_col);
                    break;
                default:
                    printf("type non supporté.\n");
                    free(value_col);
                    continue;
            }

            insert_value(cdataframe->data, value_col);
            free(value_col);
        }
        cdataframe = cdataframe->next;
    }
}

CDATAFRAME *empty_dataframe(int size) {

    list *lst_dataframe = lst_create_list();

    for (int i=0; i<size; i++){

        char *titre = (char *)malloc(50 * sizeof(char));

        COLUMN *col = create_column(NULLVAL, titre);
        lnode *pnew = lst_create_lnode(col);
        lst_insert_tail(lst_dataframe, pnew);
    }
    return lst_dataframe;
}


// ****** AFFICHAGE ****** //

// print usuel du dataframe
void print_dataframe(CDATAFRAME *cdf) {

    lnode *dataframe = cdf->head;

    while (dataframe->next != NULL) {
        print_col(dataframe->data);
        dataframe = dataframe->next;
    }

    print_col(dataframe->data);
}

// print avec une limite de colonne
void limite_print_col(CDATAFRAME *cdf, int limite) {

    lnode *dataframe = cdf->head;
    int i = 0;

    int size = get_cdataframe_cols_size(cdf);

    if (limite > size) {
        printf("La limite dépasse la taille du dataframe ");
    }
    else {
        while (i < limite) {
            print_col(dataframe->data);
            dataframe = dataframe->next;
            i++;
        }
    }
}

// print avec une limite de ligne
void limite_print_ligne(CDATAFRAME *cdf, int limite) {

    lnode *dataframe = cdf->head;

    while (dataframe != NULL) {
        print_limite_col_lig(dataframe->data, limite);
        dataframe = dataframe->next;
    }

}


// ***** OPERATION USUEL ***** //

// s'aapuie sur la func égale pour trouver l"éxistence d'une valeur
int existence_value(CDATAFRAME *cdf, void *val) {

    lnode *dataframe = cdf->head;
    int equal_val = 0;

    while (dataframe != NULL) {

        for (int i = 0; i < dataframe->data->size; i++) {

            switch (dataframe->data->column_type) {

                case INT:
                    if ( *((int*)(dataframe->data->data[i])) == *(int *)val ) {
                        equal_val ++;
                    }
                    break;

                case UINT:
                    if ( *((unsigned int*)(dataframe->data->data[i])) == *( unsigned int *)val ) {
                        equal_val ++;
                    }
                    break;


                case CHAR:
                    if ( *((char*)(dataframe->data->data[i])) == *(char *)val ) {
                        equal_val ++;
                    }
                    break;

                case FLOAT:
                    if ( *((float *)(dataframe->data->data[i])) == *(float *)val ) {
                        equal_val ++;
                    }
                    break;


                case DOUBLE:
                    if ( *((double *)(dataframe->data->data[i])) == *(double *)val ) {
                        equal_val ++;
                    }
                    break;


                case STRING:
                    if (strcmp((char *)dataframe->data->data[i], (char *) val) == 0) {
                        equal_val ++;
                    }
                    break;

                default:
                    printf("Comparaison impossible.\n");
                    continue;

            }

        }
        dataframe = dataframe->next;
    }


    if (equal_val > 0) {
        return 1;
    }

    return 0;
}

// cherche une valeur puis la remplace
int replace_value(CDATAFRAME *cdf, int col,int lig, void *replace_val) {


    int nombre_lig = nb_lig(cdf);
    int nombre_col = nb_col(cdf);
    int i =0 ;

    // vérification si le nombre de colonne et de ligne correspond bien à la taille du dataframe
    if (col > nombre_col || lig > nombre_lig) {
        return 0;
    }

    lnode *dataframe = cdf->head;

    // ENCORE UN SWITCH CASE
    // chercher la val à changer


    // **ATTENTION **
    // On peut remplacer seulement par le même type, car on a alloué un certain espace pour le pointeur.

    while (dataframe != NULL) {
        for (int j = 0; j < dataframe->data->size; j++) {

            if (i == col && j == lig) {

                switch (dataframe->data->column_type) {
                    case INT:
                        *(int *)(dataframe->data->data[j]) = *(int *)replace_val;

                        break;
                    case UINT:
                        *(unsigned int *)(dataframe->data->data[j]) = *(unsigned int *)replace_val;

                        break;
                    case CHAR:
                        *(char *)(dataframe->data->data[j]) = *(char *)replace_val;

                        break;
                    case FLOAT:
                        *(float *)(dataframe->data->data[j]) = *(float *)replace_val;

                        break;
                    case DOUBLE:
                        *(double *)(dataframe->data->data[j]) = *(double *)replace_val;

                        break;
                    case STRING:
                        free(dataframe->data->data[j]);
                        dataframe->data->data[j] = strdup((char *)replace_val);
                        break;
                    default:
                        printf("Type non pris en charge.\n");
                        continue;
                }
            }

        }
        dataframe = dataframe->next;
    }
    return 1;
}

// affiche le nom d'une colonne
void print_col_nom(CDATAFRAME *cdf) {

    lnode *dataframe = cdf->head;

    while (dataframe != NULL) {
        printf("%s \n", dataframe->data->titre);
        dataframe = dataframe->next;
    }

}

// modifie le nom d'une colonne
void modifier_nom_col(CDATAFRAME *cdf, const char *nv_nom, int index) {

    lnode *dataframe = cdf->head;

    int i = 0;

    // Parcourir la liste jusqu'à l'index désiré
    while (dataframe != NULL) {
        if (i == index) {

            // Libérer l'ancien nom de la colonne
            free(dataframe->data->titre);

            // Allouer de l'espace pour le nouveau nom et copier le nouveau nom
            dataframe->data->titre = strdup(nv_nom);

            break;
        }
        dataframe = dataframe->next;
        i++;
    }
}



void ajouter_lig_user(CDATAFRAME *cdf) {

    lnode *dataframe = cdf->head;
    void *value_col;

    while (dataframe != NULL) {

        printf("Ajouter une valeur: ");
        switch (dataframe->data->column_type) {
            case INT:
                value_col = malloc(sizeof(int));
                scanf("%d", (int*)value_col);
                insert_value(dataframe->data, value_col);

                break;
            case UINT:
                value_col = malloc(sizeof(unsigned int));
                scanf("%u", (unsigned int*)value_col);
                insert_value(dataframe->data, value_col);


                break;
            case CHAR:
                value_col = malloc(sizeof(char));
                scanf(" %c", (char*)value_col);
                insert_value(dataframe->data, value_col);


                break;
            case FLOAT:
                value_col = malloc(sizeof(float));
                scanf("%f", (float*)value_col);
                insert_value(dataframe->data, value_col);


                break;
            case DOUBLE:
                value_col = malloc(sizeof(double));
                scanf("%lf", (double*)value_col);
                insert_value(dataframe->data, value_col);

                break;
            case STRING:
                value_col = malloc(100);
                scanf("%99s", (char*)value_col);
                insert_value(dataframe->data, value_col);

                break;
            default:
                printf("type non supporté.\n");
                free(value_col);
                continue;
        }

        dataframe = dataframe->next;
    }
}

// ajoter une colonne => fonction lst_insert
void ajouter_col_user(CDATAFRAME *cdf) {


    char titre[50];
    int var_sec = 0;
    int nb_lig = 0;

    printf("Entrez un titre: ");
    scanf("%49s", titre);

    while (var_sec == 0) {
        printf("Entrez le nombre de lignes que vous souhaitez dans votre colonne (nombre positif) : ");
        if (scanf("%d", &nb_lig) == 1 && nb_lig > 0) {
            var_sec = 1;
        } else {
            printf("Saisie invalide. Veuillez réessayer.\n");
            while (getchar() != '\n');
        }
    }

    lnode *dataframe = cdf;

    ENUM_TYPE cdftype [] = {STRING,UINT, INT, CHAR, FLOAT, DOUBLE};
    COLUMN *col = create_column(*cdftype, titre);
    lnode *pnew = lst_create_lnode(col);
    lst_insert_tail(dataframe, pnew);
    lnode *new_col = cdf->tail;

    for (int i = 0; i < nb_lig; i++) {
        printf("Entrez une valeur pour la ligne [%d]: ", i);
        void *value_col;

        switch (new_col->data->column_type) {
            case INT:
                value_col = malloc(sizeof(int));
                scanf("%d", (int *)value_col);
                break;
            case UINT:
                value_col = malloc(sizeof(unsigned int));
                scanf("%u", (unsigned int *)value_col);
                break;
            case CHAR:
                value_col = malloc(sizeof(char));
                scanf(" %c", (char *)value_col);
                break;
            case FLOAT:
                value_col = malloc(sizeof(float));
                scanf("%f", (float *)value_col);
                break;
            case DOUBLE:
                value_col = malloc(sizeof(double));
                scanf("%lf", (double *)value_col);
                break;
            case STRING:
                value_col = malloc(100 * sizeof(char));
                scanf("%99s", (char *)value_col);
                break;
            default:
                printf("Type non supporté.\n");
                continue;
        }

        insert_value(new_col->data, value_col);
        free(value_col);
    }

}

// supprimer une colonne avec son index
void sup_col(CDATAFRAME *cdf ,int col) {

    lnode *dataframe = cdf->head;
    int i=0;

    while (dataframe != NULL) {
        if (i == col) {
            delete_column(&(dataframe->data));
        }
        dataframe = dataframe->next;
        i++;
    }

}



// ****** ANALYSE ET STATISTIQUE ****** //

// obtenir le nombre de ligne d'un dataframe
int nb_lig(CDATAFRAME *cdf) {

    lnode *dataframe = cdf->head;
    int nb_lig = 0;

    while (dataframe != NULL) {
        if (dataframe->data->size > nb_lig) {
            nb_lig = dataframe->data->size;
        }
        dataframe = dataframe->next;
    }


    return nb_lig;
}

// obtenir le nombre de col
int nb_col(CDATAFRAME *cdf) {

    lnode *cdataframe = cdf->head;
    int nb_col = 0;

    while (cdataframe != NULL) {
        nb_col ++;
        cdataframe = cdataframe->next;
    }

    return nb_col;

}

// obtenir le nombre de cellule egale
int nb_cellule_egale(CDATAFRAME *cdf, void *val) {

    lnode *dataframe = cdf->head;
    int equal_val = 0;

    // switch case + chercher à trouver toutes les valeurs égale donnée

    while (dataframe != NULL) {
        for (int i = 0; i < dataframe->data->size; i++) {

            switch (dataframe->data->column_type) {

                case INT:
                    if ( *((int*)(dataframe->data->data[i])) == *(int *)val ) {
                        equal_val ++;
                    }
                    break;

                case UINT:
                    if ( *((unsigned int*)(dataframe->data->data[i])) == *( unsigned int *)val ) {
                        equal_val ++;
                    }
                    break;


                case CHAR:
                    if ( *((char*)(dataframe->data->data[i])) == *(char *)val ) {
                        equal_val ++;
                    }
                    break;

                case FLOAT:
                    if ( *((float *)(dataframe->data->data[i])) == *(float *)val ) {
                        equal_val ++;
                    }
                    break;


                case DOUBLE:
                    if ( *((double *)(dataframe->data->data[i])) == *(double *)val ) {
                        equal_val ++;
                    }
                    break;


                case STRING:
                    if (strcmp((char *)dataframe->data->data[i], (char *) val) == 0) {
                        equal_val ++;
                    }
                    break;

                default:
                    printf("Comparaison impossible.\n");
                    continue;

            }

        }
        dataframe = dataframe->next;
    }

    return equal_val;
}

// pareil mais inf
int nb_cellule_inf(CDATAFRAME *cdf, void *val) {

    lnode *dataframe = cdf->head;
    int inf_val = 0;

    // switch case + chercher à trouver toutes les valeurs inferieur donnée
    while (dataframe != NULL) {
        for (int i = 0; i < dataframe->data->size; i++) {

            switch (dataframe->data->column_type) {

                case INT:
                    if ( *((int*)(dataframe->data->data[i])) > *(int *)val ) {
                        inf_val ++;
                    }
                    break;

                case UINT:
                    if ( *((unsigned int*)(dataframe->data->data[i])) > *( unsigned int *)val ) {
                        inf_val ++;
                    }
                    break;


                case CHAR:
                    if ( *((char*)(dataframe->data->data[i])) > *(char *)val ) {
                        inf_val ++;
                    }
                    break;

                case FLOAT:
                    if ( *((float *)(dataframe->data->data[i])) > *(float *)val ) {
                        inf_val ++;
                    }
                    break;


                case DOUBLE:
                    if ( *((double *)(dataframe->data->data[i])) > *(double *)val ) {
                        inf_val ++;
                    }
                    break;


                case STRING:
                    if (strlen((char *)dataframe->data->data[i]) > strlen((char *) val)) {
                        inf_val ++;
                    }
                    break;

                default:
                    printf("Comparaison impossible.\n");
                    continue;

            }

        }
        dataframe = dataframe->next;
    }

    return inf_val;
}

// pareil mais sup
int nb_cellule_sup(CDATAFRAME *cdf, void *val) {

    lnode *dataframe = cdf->head;
    int sup_val = 0;

    // switch case + chercher à trouver toutes les valeurs supérieur donnée

    while (dataframe != NULL) {
        for (int i = 0; i < dataframe->data->size; i++) {

            switch (dataframe->data->column_type) {

                case INT:
                    if ( *((int*)(dataframe->data->data[i])) < *(int *)val ) {
                        sup_val ++;
                    }
                    break;

                case UINT:
                    if ( *((unsigned int*)(dataframe->data->data[i])) < *( unsigned int *)val ) {
                        sup_val ++;
                    }
                    break;


                case CHAR:
                    if ( *((char*)(dataframe->data->data[i])) < *(char *)val ) {
                        sup_val ++;
                    }
                    break;

                case FLOAT:
                    if ( *((float *)(dataframe->data->data[i])) < *(float *)val ) {
                        sup_val ++;
                    }
                    break;


                case DOUBLE:
                    if ( *((double *)(dataframe->data->data[i])) < *(double *)val ) {
                        sup_val ++;
                    }
                    break;


                case STRING:
                    if (strlen((char *)dataframe->data->data[i]) < strlen((char *) val)) {
                        sup_val ++;
                    }
                    break;

                default:
                    printf("Comparaison impossible.\n");
                    continue;

            }

        }
        dataframe = dataframe->next;
    }

    return sup_val;
}



// ***** CSV_C ***** //


 void load_csv() {


    FILE *fp;
    char line[1000];
    char *sp;
    char file[100] = "/Users/hiarina/CLionProjects/Projet_C/test_csv_file.csv";


    int age;
    char name[100];
    char prenom[100];







    fp = fopen(file, "r");
    if (fp == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        exit(0);
    }


    while (fgets(line, sizeof(line), fp) != NULL) {

        sp = strtok(line, ";");
        if (sp != NULL) {
            strcpy(name, sp);
        }
        sp = strtok(NULL, ";");
        if (sp != NULL) {
            strcpy(prenom, sp);
        }

        sp = strtok(NULL, ";");
        if (sp != NULL) {
            age = atoi(sp);
        }

        printf("%s %s %d", name, prenom, age);

    }

    fclose(fp);
}

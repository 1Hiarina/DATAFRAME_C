#ifndef PROJET_C_CDATAFRAME_H
#define PROJET_C_CDATAFRAME_H
#include "list.h"

// ALIMENTATION
CDATAFRAME *create_dataframe(ENUM_TYPE *cdtype, int size);
CDATAFRAME *empty_dataframe(int size);
void deletete_dataframe(CDATAFRAME **cdf);
void user_dataframe(CDATAFRAME *cdf);

// OPERATION USUEL
void delete_column_dataframe(CDATAFRAME *cdf, char *col_name);
int get_cdataframe_cols_size(CDATAFRAME *cdf);
void add_col_dataframe_user(CDATAFRAME *cdf);
void sup_col(CDATAFRAME *cdf ,int col);
void ajouter_col_user(CDATAFRAME *cdf);
void print_col_nom(CDATAFRAME *cdf);
void modifier_nom_col(CDATAFRAME *cdf, const char *nv_nom, int index);


// AFFICHAGE
void print_dataframe(CDATAFRAME *cdf);
void limite_print_col(CDATAFRAME *cdf, int limite);
void limite_print_ligne(CDATAFRAME *cdf, int limite);

// ANALYSE ET STATISTIQUE
int nb_lig(CDATAFRAME *cdf);
int nb_col(CDATAFRAME *cdf);
int nb_cellule_egale(CDATAFRAME *cdf, void *val);
int nb_cellule_inf(CDATAFRAME *cdf, void *val);
int nb_cellule_sup(CDATAFRAME *cdf, void *val);
int existence_value(CDATAFRAME *cdf, void *val);

int replace_value(CDATAFRAME *cdf, int col,int lig, void *replace_val);
void ajouter_lig_user(CDATAFRAME *cdf);

// CSV


void load_csv();

#endif //PROJET_C_CDATAFRAME_H

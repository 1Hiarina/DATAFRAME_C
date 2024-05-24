#include "cdataframe.h"
#include "list.h"
#include "column.h"
#include <stdio.h>

int main() {
    int size;
    int true2 = 1;
    int option;

    printf("Entrez le nombre de colonnes de votre dataframe : ");
    scanf("%d", &size);

    // TEST CRÉATION DU DATAFRAME
    ENUM_TYPE cdftype[] = {STRING, UINT, INT, CHAR, FLOAT, DOUBLE};
    CDATAFRAME *cdf = create_dataframe(cdftype, size);

    printf("Entrez les valeurs de votre dataframe :\n");
    user_dataframe(cdf);

    printf("Voici votre dataframe :\n");
    print_dataframe(cdf);

    while (true2 == 1) {

        printf("****** MENU *******\n");
        printf("Que voulez-vous faire maintenant ? :\n");
        printf("1. Ajouter une colonne\n");
        printf("2. Ajouter une ligne\n");
        printf("3. Supprimer une colonne\n");
        printf("4. Afficher le dataframe selon une limite de colonne\n");
        printf("5. Afficher le dataframe selon une limite de ligne\n");
        printf("6. Sortir du menu\n");

        printf("Choisissez une option : ");
        scanf("%d", &option);

        if (option == 1) {
            ajouter_col_user(cdf);
            print_dataframe(cdf);
        } else if (option == 2) {
            ajouter_lig_user(cdf);
            print_dataframe(cdf);
        } else if (option == 3) {
            printf("Saisir l'index de la colonne à supprimer : \n");

            int size = get_cdataframe_cols_size(cdf);
            int index_col = size + 1;

            while (index_col > size) {
                scanf("%d", &index_col);
            }
            sup_col(cdf, index_col);
            print_dataframe(cdf);
        } else if (option == 4) {
            int limite;
            printf("Saisir selon une limite de colonne : ");
            scanf("%d", &limite);
            limite_print_col(cdf, limite);
        } else if (option == 5) {
            int limite;
            printf("Saisir selon une limite de ligne : ");
            scanf("%d", &limite);
            limite_print_ligne(cdf, limite);
        } else if (option == 6) {
            true2 = 0;
        } else {
            printf("Option invalide, veuillez réessayer.\n");
        }
    }



    return 0;
}

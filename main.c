#include "cdataframe.h"
#include "list.h"
#include "column.h"



int main() {


    // TEST CRÉATION DU DATAFRAME
    ENUM_TYPE cdftype [] = {STRING,UINT, INT, CHAR, FLOAT, DOUBLE};
    CDATAFRAME *cdf = create_dataframe(cdftype, 2);

    // test des fonctions
    user_dataframe(cdf);



    // fonction qui ne marche pas

    //int val2 = 10;
    //replace_value(cdf,0,0,&val2);

    // fonction pour modifier le nom ne marche pas
    //    char nom[10] = "hiarina";
    //    char *p = nom;
    //
    //    modifier_nom_col(cdf,p,1);

    print_dataframe(cdf); // premier print sans la colonne rajoutée


    ajouter_col_user(cdf);
    print_dataframe(cdf); // deuxieme print avec la colonne ajoutée

    ajouter_lig_user(cdf);
    print_dataframe(cdf); // troisieme print avec la ligne ajoutée

    print_col_nom(cdf);

    // fonction limite
    limite_print_col(cdf, 2);
    limite_print_ligne(cdf, 1);





    load_csv();


    deletete_dataframe(cdf);

    // print_dataframe(cdf);




    return 0;
}

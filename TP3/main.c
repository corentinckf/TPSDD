#include "arbre.h"

int main()
{
    //A externaliser sur un autre fichier
    char expression[] = "(a*(b*(i*(m*E*S))+r*b*r*E*S))";
    int i = 0;
    noeud_t * rac = creer_Arbre(expression);

    disp_Mots(rac);
    char mot[7] = "abimEST";
    int test = 0;
    noeud_t ** debug_ddd = recherche_prec_Arbre(&rac,mot,&i);
    printf("%d", i);
    liberer_Arbre(&rac);

    return 0;
}
#include "arbre.h"

int main()
{
    //A externaliser sur un autre fichier
    char expression[] = "(a*(b*(i*(m*E*S))+r*b*r*E*S))";
    int i = 0, code = 0;
    noeud_t * rac = creer_Arbre(expression);

    
    char mot[4] = "abit";

    inserer_mot(&rac, mot, &code);
    disp_Mots(rac);
   // liberer_Arbre(&rac);

    return 0;
}
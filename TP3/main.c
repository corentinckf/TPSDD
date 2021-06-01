#include "arbre.h"

int main()
{
    char expression[] = "(a*(b*(D+(E*S*G)+C))";
    noeud_t * rac = creer_Arbre(expression);

    /*inserer_mot(&rac, "abac");
    disp_motif(&rac, "ab");*/
    disp_Mots(rac, "");
    
    liberer_Arbre(&rac);

    return 0;
}
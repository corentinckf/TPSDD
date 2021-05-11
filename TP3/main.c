#include "pile.h"
#include "arbre.h"
#include "string.h"

noeud_t * creer_Dico(char * string)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * rac, *noeud;
    noeud_t ** prec=&rac; noeud_t * cour = rac;
    int i;
    int empiler_prochain = 1;
    int etat = 0;

    int taille_string = (int) strlen(string);

    //On parcourt toute la string => for
    for(i=0; i < taille_string;++i)
    {
        switch(string[i])
        {
            case '*': 
                prec = &cour->fils;
                break;
            case '+':
                depiler(pile,&cour,&etat);
                prec = &cour->frere;
                empiler_prochain = 1;
                break;
            case '(': //Il faut empiler le prochain
                empiler_prochain = 1;
                break;
            case ')': // On depile
                depiler(pile,&cour,&etat);
                break;
            default: // Cas par defaut est en fait lettre quelconques
                noeud = alloc_noeud(string[i],NULL,NULL);
                *prec = noeud;
                cour = noeud;
                if(empiler_prochain)
                {
                    empiler(pile,cour);
                    empiler_prochain = 0;
                }
                break;     
        }
    }

    return rac;
}


void affichage_Dico(noeud_t * racine)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t ** prec = &racine, * cour = racine;


}
int main()
{
    //A externaliser sur un autre fichier
    char expression[] = "(a*(a*(C+D)+b*E))";

    noeud_t * rac = creer_Dico(expression);

    return 0;
}
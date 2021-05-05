#include "pile.h"
#include "arbre.h"
#include "string.h"



noeud_t ** creer_Dico(char * string)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t ** prec;
    int i;
    int empiler_prochain = 0;
    int etat = 0, * petat = &etat;

    int taille_string = (int) strlen(string);

    //On parcourt toute la boucle => for
    for(i=0; i < taille_string;++i)
    {
        switch(string[i])
        {
            case '*': // Créer lien vertical
                *prec = (*prec)->fils;
                break;
            case '+': // Créer lien horizontal
                depiler(pile,*prec,petat);
                *prec = (*prec)->frere;
                empiler_prochain = 1;
                break;
            case '(': //Il faut empiler le prochain
                empiler_prochain = 1;
                break;
            case ')': // On dépile
                depiler(pile,*prec,petat);
                break;
            default: // Cas par défault est en fait lettre quelconques
                noeud_t * noeud = alloc_noeud(string[i],NULL,NULL);
                *prec = noeud;
                if(empiler_prochain)
                {
                    empiler(pile,*noeud);
                    empiler_prochain = 0;
                }
                    
                break;
        }
    }

    return prec;
}


int main()
{
    return 0;
}
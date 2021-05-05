#include "pile.h"
#include "arbre.h"
#include "string.h"



noeud_t * creer_Dico(char * string)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * rac;
    noeud_t ** prec=&rac; noeud_t* cour;
    int i;
    int empiler_prochain = 0;
    int etat = 0;

    int taille_string = (int) strlen(string);

    //On parcourt toute la boucle => for
    for(i=0; i < taille_string;++i)
    {
        switch(string[i])
        {
            case '*': 
                prec = &(*prec)->fils;
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
            default: // Cas par default est en fait lettre quelconques
            {
                noeud_t * noeud = alloc_noeud(string[i],NULL,NULL);
                *prec = noeud;
                if(empiler_prochain)
                {
                    empiler(pile,*prec);
                    empiler_prochain = 0;
                }
            }
                
        }
    }

    return rac;
}


int main()
{
    char expression[] = "(a*(b*(a*T+i*(m*e)))+(R*(d*u)+(T*S))))";

    noeud_t * rac = creer_Dico(expression);

    return 0;
}
#include "pile.h"
#include "arbre.h"
#include "string.h"
#include <ctype.h>

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
    liberer_Pile(&pile);
    return rac;
}



void disp_Mots(noeud_t * racine)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * cour = racine, * copie[MAX];
    int etat = 0;

    while(cour || ! estVide(pile))
    {
        while(cour)
        {
            empiler(pile, cour);
            if(isupper(cour->valeur)) //Si lettre maj, on a un mot
            {
                //Faire une fonction
                for(int i = 0; i <= pile->sommet;++i)
                    copie[i] = pile->base[i];
                //Faire une fonction
                for(int i = 0; i <= pile->sommet;++i)
                    printf("%c", copie[i]->valeur);
                printf("\n");
            }   
            cour = cour->fils;
        }
        while(cour == NULL && !estVide(pile))
            depiler(pile, &cour, &etat);
        if(cour)
            cour = cour->frere;
        
    }
    liberer_Pile(&pile);


}
int main()
{
    //A externaliser sur un autre fichier
    char expression[] = "(a*(a*(C+D)+b*E))";

    noeud_t * rac = creer_Dico(expression);

    disp_Mots(rac);

    return 0;
}
#include "arbre.h"
#include "pile.h"
#include <string.h>
#include <ctype.h>

noeud_t * alloc_noeud(char valeur,noeud_t * fils, noeud_t * frere)
{
    noeud_t * element = (noeud_t *) malloc(sizeof(noeud_t));
    if(element)
    {
        element->valeur = valeur;
        element->fils = fils;
        element->frere = frere;
    }

    return element;   
}

void liberer_Arbre(noeud_t ** racine)
{
    while(*racine)
    {
        supprimer_noeud(racine);
    }
}

void supprimer_noeud(noeud_t ** prec)
{
    noeud_t * temp = *prec;
    *prec=(*prec)->frere;
    free(temp);
}

noeud_t * creer_Arbre(char * string)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * rac, *noeud;
    noeud_t ** prec=&rac; noeud_t * cour = rac;
    int i;
    int empiler_prochain = 1;
    int etat = 0;

    int taille_string = (int) strlen(string);

    //On parcour toute la string => for
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
                // On cree une copie de la pile
                    //Faire une fonction
                for(int i = 0; i < pile->sommet + 1;++i)
                    copie[i] = pile->base[i];
                
                //On l'affiche
                    //Faire une fonction
                for(int i = 0; i < pile->sommet + 1;++i)
                    printf("%c", tolower(copie[i]->valeur)); 
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

noeud_t ** recherche_prec_triee(noeud_t ** tete, char valeur)
{
    noeud_t ** prec = tete;
    noeud_t  * courant = *tete;
    while (courant && courant->valeur < valeur)
    {
        prec = &(courant->frere);
        courant = courant->frere;
    }
    return(prec);
}

noeud_t ** recherche_prec_Arbre(noeud_t ** rac, char * mot, int * i)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t ** prec=rac; noeud_t * cour = *rac;
    int traitement_fini = 0, i = 0;

    while(!traitement_fini )
    {
        prec = recherche_prec_triee(prec, mot[i]);
        if(*prec && (*prec)->valeur == mot[i])
        {
            if(mot[i+1] == '\0')
                traitement_fini = 1;
            prec = &cour->fils;
            cour = *prec;
            ++i;
            
        }else
        {
            traitement_fini = 1;
        }
        
        
    }

    liberer_Pile(&pile);
    return prec;
}

/*void inserer_lettre()
{

}*/

void inserer_mot(noeud_t ** racine, char * mot,int * code_retour){
    int i = 0;
    noeud_t ** prec = recherche_prec_Arbre(racine, mot, &i);
    //Boucle pour insérer les lettres restantes.
}

 
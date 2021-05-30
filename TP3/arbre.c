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
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t ** prec = racine;
    noeud_t * cour = *racine;
    int etat = 0;

    while(cour || !estVide(pile))
    {
        while(cour)
        {
            empiler(pile, cour);
            cour = cour->fils;
        }
        while(cour == NULL && !estVide(pile))
        {
            depiler(pile,&cour,&etat);
        }
        if(cour)
        {
            prec = &cour;
            cour = cour->frere;
            free(prec);
        }
    }

    liberer_Pile(&pile);

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
    while (courant && tolower(courant->valeur) < tolower(valeur))
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
    int traitement_fini = 0;
    *i = 0;

    while(!traitement_fini)
    {
        prec = recherche_prec_triee(prec, mot[*i]);
        cour = *prec;
        if(*prec && (*prec)->valeur == mot[*i])
        {
            if(mot[(*i)+1] == '\0')
                traitement_fini = 1;
            prec = &cour->fils;
            cour = *prec;
            (*i)++;
            
        }else
        {
            traitement_fini = 1;
        }     
    }
    liberer_Pile(&pile);
    return prec;
}

noeud_t * creerNoeud(char valeur) {
	noeud_t * noeud = (noeud_t *) malloc(sizeof(noeud_t));
	noeud->valeur = valeur;
	noeud->frere = NULL;
	noeud->fils = NULL;
	return noeud;
}

void inserer_Lettre(noeud_t ** prec, char valeur)
{
    noeud_t * noeud = creerNoeud(valeur);
    if(noeud)
    {
        noeud->frere = *prec;
        *prec = noeud;
    }

}

void inserer_mot(noeud_t ** racine, char * mot,int * code_retour){

    int i = 0;

    noeud_t ** prec = recherche_prec_Arbre(racine, mot, &i);
    noeud_t *  cour = *prec;

    while(mot[i] != '\0')
    {
        prec = recherche_prec_triee(prec, mot[i]);
        inserer_Lettre(prec, mot[i]);
        cour = *prec;
        prec = &((*prec)->fils);
        ++i;
    }

    //printf("%c",cour->valeur);
}

 
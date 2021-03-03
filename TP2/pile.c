#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

pile_t * initialiser_Pile(int taille_pile)
{
    pile_t * pile = (pile_t *) malloc(sizeof(pile_t));
    if(pile)
    {
        pile->taille = taille_pile;
        pile->sommet = -1;
        pile->base = (element_t *) malloc(taille_pile * sizeof(element_t));

//Si l'allocation échoue
        if(pile->base)
        {
            free(pile);
            pile = NULL;
        }
            
    }
    return pile;
}

void liberer_Pile(pile_t ** p_pile)
{

//On libère la "vraie" partie pile
    free((*p_pile)->base);

//On libère la structure de la pile
    free(*p_pile);
    *p_pile = NULL;

}

int estVide(pile_t * pile)
{
    return (pile->sommet == -1);
}

int estPleine(pile_t * pile)
{
    return (pile->sommet == (pile->taille - 1));
}

void sommet(pile_t * pile, element_t * resultat, int * retour)
{
    *retour = 1;
    if(!estVide(pile))
    {
        *resultat = (pile->base)[pile->sommet];
        *retour = 0;
    }
}

int empiler(pile_t * pile, element_t element)
{
    int retour = 1;
    if(!estPleine(pile))
    {
//Incrémentation du sommet
        ++(pile->sommet);
//Ajout de l'élement à la pile
        (pile->base)[pile->sommet] = element;
        retour = 0;
    }

    return retour;
}

void depiler(pile_t * pile, element_t * resultat, int * retour)
{
    *retour = 1;
    if(!estVide(pile))
    {
//On garde le sommet
        *resultat = (pile->base)[pile->sommet];
//Décremente le sommet, car un élement en moins
        --pile->sommet;
        *retour = 0;
    }
}
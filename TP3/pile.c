#include "pile.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------- */
/* initialiser_Pile: Alloue l'espace mémoire à la pile                  */
/*                                                                      */
/* En entrée: La taille maximale de la pile                             */
/*                                                                      */
/* En sortie: Un pointeur sur la "tête" de la pile                      */
/* -------------------------------------------------------------------- */

pile_t * initialiser_Pile(int taille_pile)
{
    pile_t * pile = (pile_t *) malloc(sizeof(pile_t));
    if(pile)
    {
        pile->taille = taille_pile;
        pile->sommet = -1;
        pile->base = (element_t *) malloc(taille_pile * sizeof(element_t));

//Si l'allocation échoue
        if(pile->base == NULL)
        {
            free(pile);
            pile = NULL;
        }
            
    }
    return pile;
}

/* -------------------------------------------------------------------- */
/* liberer_Pile: Libère l'espace mémoire à la pile                      */
/*                                                                      */
/* En entrée: un double pointeur sur la pile                            */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void liberer_Pile(pile_t ** p_pile)
{

//On libère la "vraie" partie pile
    free((*p_pile)->base);

//On libère la structure de la pile
    free(*p_pile);
    *p_pile = NULL;

}

/* -------------------------------------------------------------------- */
/* estVide: Indique si la pile est vide                                 */
/*                                                                      */
/* En entrée: un pointeur sur la pile                                   */
/*                                                                      */
/* En sortie: 0 si la pile n'est pas Vide, 1 sinon                      */
/* -------------------------------------------------------------------- */
int estVide(pile_t * pile)
{
    return (pile->sommet == -1);
}

/* -------------------------------------------------------------------- */
/* estPleine: Indique si la pile est pleine                             */
/*                                                                      */
/* En entrée: un pointeur sur la pile                                   */
/*                                                                      */
/* En sortie: 0 si la pile n'est pas pleine, 1 sinon                    */
/* -------------------------------------------------------------------- */
int estPleine(pile_t * pile)
{
    return (pile->sommet == (pile->taille - 1));
}

/* ----------------------------------------------------------------------------------*/
/* sommet: Récuperer l'element au sommet de la pile                                  */
/*                                                                                   */
/* En entrée: un pointeur sur la pile                                                */
/*            un pointeur sur element (element que l'on récupere de la pile)         */
/*            un pointeur sur entier (qui indique le succès ou non de l'opération)   */
/*                                                                                   */
/* En sortie: void                                                                   */
/* ----------------------------------------------------------------------------------*/
void sommet(pile_t * pile, element_t * resultat, int * retour)
{
    *retour = 1;
    if(!estVide(pile))
    {
        *resultat = (pile->base)[pile->sommet];
        *retour = 0;
    }
}

/* -------------------------------------------------------------------- */
/* empiler: empiler un élément à la pile                                */
/*                                                                      */
/* En entrée: un pointeur sur la pile                                   */
/*            un element (l'element que l'on empile)                    */
/*                                                                      */
/* En sortie: 0 si l'on a réussi l'empilement, 1 sinon                  */
/* -------------------------------------------------------------------- */
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

/* -----------------------------------------------------------------------------------*/
/* depiler: depiler un élément de la pile                                             */
/*                                                                                    */
/* En entrée: un pointeur sur la pile                                                 */
/*            un pointeur sur element (pour garder l'élément au sommet de la pile)    */
/*            un pointeur entier (pour indiquer si succès ou non)                     */
/*                                                                                    */
/* En sortie: void                                                                    */
/* -----------------------------------------------------------------------------------*/
void depiler(pile_t * pile, element_t *resultat, int * retour)
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
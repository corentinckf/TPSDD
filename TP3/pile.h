#ifndef __PILE_H__
#define __PILE_H__

#include <stdio.h>
#include <stdlib.h>

#define FORMAT %d

//Définition des structures nécessaires à la gestion de la pile
typedef int element_t;
typedef struct pile
{

    element_t * base;
    int sommet;
    int taille;

}pile_t;

//Prototypes des fonctions sur la pile
pile_t * initialiser_Pile(int);
void liberer_Pile(pile_t **);
int estVide(pile_t *);
int estPleine(pile_t *);
void sommet(pile_t *, element_t *, int *);
int empiler(pile_t *,element_t);
void depiler(pile_t *, element_t *, int *);

#endif

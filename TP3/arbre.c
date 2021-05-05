#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

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
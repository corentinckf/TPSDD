#include "arbre.h"
#include <stdio.h>
#include <stdlib.h>

noeud * alloc_noeud(char valeur,noeud * fils, noeud * frere)
{
    noeud * element = (noeud *) malloc(sizeof(cellule));
    if(element)
    {
        element->valeur = valeur;
        element->fils = fils;
        element->frere = frere;
    }

    return element;   
}
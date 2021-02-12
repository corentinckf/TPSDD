#include "lch.h"

#include <stdio.h>
#include <stdlib.h>

cellule * alloc_cellule(int valeur,int periode, int num_usine,cellule * suivant)
{
    cellule * element = (cellule *) malloc(sizeof(cellule));
    if(element)
    {
        element->valeur = valeur;
        element->periode = periode;
        element->num_usine = num_usine;
        element->suivant = suivant;
    }

    return element;
    
}

cellule * initialisation_lch(int valeur, int num_usine)
{
    cellule      * block = (cellule *) malloc(sizeof(cellule));
    //On vérifie que l'allocation ai fonctionnée
    if(block != NULL)
    {
        block->valeur = valeur;
        block->num_usine = num_usine;
        block->suivant = NULL;
    }
    return block;
}


void ajouter_cellule(cellule ** prec, cellule * block)
{
    block->suivant = *prec;
    *prec = block;
}

void supprimer_cellule(cellule ** prec)
{
     cellule * temp = *prec;
    *prec=(*prec)->suivant;
     free(temp);
}

cellule ** recherche_prec_triee(cellule ** tete, int valeur)
{
    cellule ** prec = tete;
    cellule  * courant = *tete;

    while (courant && courant->valeur > valeur)
    {
        prec = &(courant->suivant);
        courant = courant->suivant;
    }
    return(prec);

}


cellule ** recherche_prec(cellule ** tete, int valeur)
{
    cellule ** prec = tete;
    cellule  * courant = *tete;

    while (courant && courant->num_usine != valeur)
    {
        prec = &(courant->suivant);
        courant = courant->suivant;
    }
    return(prec);

}

void afficher_lch(cellule * tete)
{
    cellule * courant = tete;

    while(courant)
    {
        fprintf(stdout, "%d ", courant->valeur);
        courant = courant->suivant;
    }

    fprintf(stdout, "\n");

}

//TODO
/*void liberer_lch(cellule ** tete)
{

}*/

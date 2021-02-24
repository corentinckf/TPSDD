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

void afficher_lch(cellule * tete, FILE * flux)
{
    cellule * courant = tete;

    while(courant)
    {
        fprintf(flux, "%d ", courant->valeur);
        courant = courant->suivant;
    }

    fprintf(flux, "\n");

}

void liberer_lch(cellule ** tete)
{
    while(*tete)
    {
        supprimer_cellule(tete);
    }

}

void supprimer_occurence(cellule ** tete, int num_usine)
{
    cellule ** prec = NULL;
    while((prec = recherche_prec(tete,num_usine)) && *prec)
    {
        supprimer_cellule(prec);
    }
}

void sauvegarder_liste(cellule * tete, const char * nom_fichier)
{
    FILE * fichier;

    if((fichier = fopen(nom_fichier, "w+")))
    {
        afficher_lch(tete,fichier);
        fclose(fichier);
    }else{
        fprintf(stdout, "Erreur : Impossible de sauvegarder la liste chaine dans un fichier !");
    }
    
}

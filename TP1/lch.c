#include "lch.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------- */
/* alloc_cellule: Alloue l'espace mémoire et initialise une cellule et  */
/*                la renvoie                                            */
/*                                                                      */
/* En entrée: valeur, periode, num_usine des entiers nécessaires à      */
/*            l'initialisation de la cellule                            */
/*            Et suivant un pointeur sur la cellule suivante            */
/*                                                                      */
/* En sortie: Un pointeur sur une cellule                               */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* ajouter_cellule: Ajoute une cellule à l'addresse prec de la lch      */
/*                                                                      */
/* En entrée: Un double pointeur sur la cellule précédente              */
/*            Un pointeur sur la cellule à rajouter                     */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void ajouter_cellule(cellule ** prec, cellule * block)
{
    block->suivant = *prec;
    *prec = block;
}

/* -------------------------------------------------------------------- */
/* supprimer_cellule: Supprime une cellule d'adresse donnée en paramètre*/
/*                                                                      */
/* En entrée: Un double pointeur sur la cellule précédente              */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void supprimer_cellule(cellule ** prec)
{
    cellule * temp = *prec;
    *prec=(*prec)->suivant;
    free(temp);
}

/* -------------------------------------------------------------------- */
/* recherche_prec_triee: recherche le précedent où placer               */
/*(dans l'ordre décroissant dans le contexte de cet exercice) un entier */                                       
/*                                                                      */
/* En entrée: Un double pointeur sur une cellule (tête de liste)        */
/*            Un entier (l'entier dont on recherche le précedent)       */
/*                                                                      */
/* En sortie: Un pointeur sur une cellule (le précedent ou NULL)        */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* recherche_prec: recherche du précedent de l'entier en paramètre      */
/*                                                                      */
/* En entrée: valeur, periode, num_usine des entiers nécessaires à      */
/*               à l'initialisation de la cellule                       */
/*            Et suivant un pointeur sur la cellule suivante            */
/*                                                                      */
/* En sortie: Un pointeur sur une cellule                               */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* afficher_cellule: Affiche un liste chaînée                           */
/*                                                                      */
/* En entrée: Un pointeur sur une cellule (la tête de la lch)           */
/*            Un pointeur sur un stream (pour spécifier là où on veut   */
/*               qu'il y ai affichage)                                  */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* liberer_lch: Libère l'espace mémoire de la liste chaînée             */
/*                                                                      */
/* En entrée: Un double pointeur sur une cellule (la tête de la lch)    */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void liberer_lch(cellule ** tete)
{
    while(*tete)
    {
        supprimer_cellule(tete);
    }
}

/* -------------------------------------------------------------------- */
/* supprimer_occurence: Supprime les valeurs liés à un numéro d'usine   */
/*                         donné en paramètre                           */
/*                                                                      */
/* En entrée: Un double pointeur sur une cellule (la tête de la lch)    */
/*            Un entier (numéro d'usine souhaité)                       */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void supprimer_occurence(cellule ** tete, int num_usine)
{
/*Version pas optimale, car on repart à chaque fois du début*/
/*cellule ** prec = NULL;
while((prec = recherche_prec(tete,num_usine)) && *prec)
{
    supprimer_cellule(prec);
}*/

/*Version plus optimale, on part de la tête au début*/
    cellule ** prec = tete;

/*à chaque appel de recherche_prec, on repart au prec trouvé avant
S'il n'existe pas, pas de soucis, on sort du while                */
    while (*(prec = recherche_prec(prec,num_usine)))
    {
        supprimer_cellule(prec);
    }

}

/* -------------------------------------------------------------------- */
/* sauvegarde_liste: Sauvegarde la liste chaînée dans un fichier        */
/*                                                                      */
/* En entrée: Un pointeur sur une cellule (la tête de la lch)           */
/*            Un pointeur sur une chaîne de char (nom du fichier)       */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
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

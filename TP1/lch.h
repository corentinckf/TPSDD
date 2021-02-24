#ifndef __CELLULE_H__
#define __CELLULE_H__

#include <stdio.h>
#include <stdlib.h>

//Définition de la structure cellule pour la liste chaînée
typedef struct cellule
{

    int valeur;
    int num_usine;
    int periode;
    struct cellule * suivant;

}cellule;

//Prototypes des fonctions sur les listes chaînées
cellule * alloc_cellule(int, int, int, cellule *);
void ajouter_cellule(cellule ** , cellule *);
void supprimer_cellule(cellule **);
cellule ** recherche_prec_triee(cellule **, int);
cellule ** recherche_prec(cellule **, int);
void afficher_lch(cellule *, FILE *);
void liberer_lch(cellule **);
void supprimer_occurence(cellule **, int);
void sauvegarder_liste(cellule *, const char *);

#endif

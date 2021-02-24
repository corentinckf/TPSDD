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
cellule * alloc_cellule(int valeur,int periode, int num_usine,cellule * suivant);
cellule * initialisation_lch(int valeur, int num_usine);
void ajouter_cellule(cellule ** prec, cellule * block);
void supprimer_cellule(cellule ** prec);
cellule ** recherche_prec_triee(cellule ** tete, int valeur);
cellule ** recherche_prec(cellule ** tete, int valeur);
void afficher_lch(cellule * tete, FILE * flux);
void liberer_lch(cellule ** tete);
void supprimer_occurence(cellule ** tete, int num_usine);
void sauvegarder_liste(cellule * tete, const char * nom_fichier);
#endif

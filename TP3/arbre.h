#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>
#include <stdlib.h>

//Définition des structures nécessaires à la gestion de l'arbre
typedef struct noeud {
    char valeur;
    struct noeud * fils;
    struct noeud * frere;
} noeud_t;

//Prototypes des fonctions sur l'arbre
noeud_t * alloc_noeud(char,noeud_t *, noeud_t *);
void liberer_Arbre(noeud_t **);
noeud_t * creer_Arbre(char *);
void disp_Mots(noeud_t *, char *);
noeud_t ** recherche_prec_triee(noeud_t **, char);
noeud_t ** recherche_prec_Arbre(noeud_t **, char *, int *);
void inserer_Lettre(noeud_t **, char );
void inserer_mot(noeud_t **, char *);
void disp_motif(noeud_t **, char *);
#endif
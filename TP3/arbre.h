#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    char valeur;
    struct noeud * fils;
    struct noeud * frere;
} noeud_t;

noeud_t * alloc_noeud(char,noeud_t *, noeud_t *);
void liberer_Arbre(noeud_t **);
void supprimer_noeud(noeud_t **);
noeud_t * creer_Arbre(char *);
void disp_Mots(noeud_t *, char *);
noeud_t ** recherche_prec_triee(noeud_t **, char);
noeud_t ** recherche_prec_Arbre(noeud_t **, char *, int *);
noeud_t * creerNoeud(char);
void inserer_Lettre(noeud_t **, char );
void inserer_mot(noeud_t **, char *);
void disp_motif(noeud_t **, char *);
#endif
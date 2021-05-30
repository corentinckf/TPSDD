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
void disp_Mots(noeud_t *);
noeud_t ** recherche_prec_triee(noeud_t ** tete, char valeur);
noeud_t ** recherche_prec_Arbre(noeud_t ** rac, char * mot, int *);
#endif
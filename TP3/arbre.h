#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    char valeur;
    struct noeud * fils;
    struct noeud * frere;
} noeud_t;

noeud_t * alloc_noeud(char valeur,noeud_t * fils, noeud_t * frere);

#endif
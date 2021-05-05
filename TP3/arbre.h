#ifndef __ARBRE_H__
#define __ARBRE_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct noeud {
    char valeur;
    struct noeud * fils;
    struct noeud * frere;
} noeud_t;

noeud * alloc_noeud(char valeur,noeud * fils, noeud * frere);

#endif
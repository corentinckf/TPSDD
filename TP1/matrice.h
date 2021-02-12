#ifndef __MATRICE_H__
#define __MATRICE_H__

#include <stdio.h>
#include <stdlib.h>

//Prototypes des fonctions sur les matrices
int ** initialisation_matrice(int * , int *);
void liberer_matrice(int **, int *);
void afficher_matrice(int **, int *, int *);
int ** creer_matrice(const char *,int *, int *);
#endif


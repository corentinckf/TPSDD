#ifndef __FILE_H__
#define __FILE_H__

#include <stdio.h>
#include <stdlib.h>

#define FORMAT %d

//Définition des structures nécessaires à la gestion de la file
typedef int element_t;
typedef struct file
{

    element_t * base;
    int taille;
    int nb;
    int rang_deb;
    int rang_fin;

}file_t;

//Prototypes des fonctions sur la pile
file_t * initialiser_File(int);
void liberer_File(file_t **);
int estVideF(file_t *);
int estPleineF(file_t *);
int enfiler(file_t *,element_t);
void defiler(file_t *, int *);

#endif

#include "file.h"
#include <stdio.h>
#include <stdlib.h>


file_t * initialiser_File(int taille_file)
{
    file_t * file = (file_t *) malloc(sizeof(file_t));
    if(file)
    {
        file->taille = taille_file;
        file->nb = 0;
        file->rang_deb = 0;
        file->rang_fin = taille_file - 1;
        file->base = (element_t *) malloc(taille_file * sizeof(element_t));

//Si l'allocation échoue
        if(file->base)
        {
            free(file);
            file = NULL;
        }
            
    }
    return file;
}

void liberer_File(file_t ** p_file)
{
//On libère la "vraie" partie file
    free((*p_file)->base);

//On libère la structure de la pile
    free(*p_file);
    *p_file = NULL;
}

int estVideF(file_t * file)
{
    return file->nb;
}

int estPleineF(file_t * file)
{
    return (file->rang_fin == (file->taille - 1));
}

int enfiler(file_t * file,element_t element)
{
    int retour = 1;
    if(!estPleineF(file))
    {
//Incrémentation du rang de fin
        file->rang_fin = (file->rang_fin + 1) % file->taille;
//Incrémentation du compteur d'éléments
        ++(file->nb);
//Ajout de l'élement à la file
        (file->base)[file->rang_fin] = element;
        retour = 0;
    }

    return retour;
}

void defiler(file_t * file, int * retour)
{
    *retour = 1;
    if(!estVideF(file))
    {
//Décrémentation du compteur d'éléments
        ++(file->nb);
//On Incrémente le rang de début
        file->rang_deb = (file->rang_deb + 1) % file->taille;
        *retour = 0;
    }
}

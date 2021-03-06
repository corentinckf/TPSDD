#include "file.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------- */
/* initialiser_File: Alloue l'espace mémoire et la file                 */
/*                                                                      */
/* En entrée: La taille maximale de la file                             */
/*                                                                      */
/* En sortie: Un pointeur sur la "tête" de la file                      */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* liberer_File: Libère l'espace mémoire et la file                     */
/*                                                                      */
/* En entrée: un double pointeur sur la file                            */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void liberer_File(file_t ** p_file)
{
//On libère la "vraie" partie file
    free((*p_file)->base);

//On libère la structure de la pile
    free(*p_file);
    *p_file = NULL;
}

/* -------------------------------------------------------------------- */
/* estVideF: Indique si la file est vide                                */
/*                                                                      */
/* En entrée: un pointeur sur la file                                   */
/*                                                                      */
/* En sortie: 0 si la file n'est pas Vide, 1 sinon                      */
/* -------------------------------------------------------------------- */
int estVideF(file_t * file)
{
    return file->nb;
}

/* -------------------------------------------------------------------- */
/* estPleineF: Indique si la file est pleine                            */
/*                                                                      */
/* En entrée: un pointeur sur la file                                   */
/*                                                                      */
/* En sortie: 0 si la file n'est pas pleine, 1 sinon                    */
/* -------------------------------------------------------------------- */
int estPleineF(file_t * file)
{
    return (file->rang_fin == (file->taille - 1));
}

/* -------------------------------------------------------------------- */
/* enfiler: enfiler un élément à la file                                */
/*                                                                      */
/* En entrée: un pointeur sur la file                                   */
/*            un element (l'element que l'on enfile)                    */
/*                                                                      */
/* En sortie: 0 si l'on a réussi l'enfilement, 1 sinon                  */
/* -------------------------------------------------------------------- */
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

/* -------------------------------------------------------------------- */
/* defiler: defiler un élément à la file                                */
/*                                                                      */
/* En entrée: un pointeur sur la file                                   */
/*            un pointeur sur entier (succés ou non de l'opération)     */
/*                                                                      */
/* En sortie: 0 si l'on a réussi l'dé-enfilement, 1 sinon               */
/* -------------------------------------------------------------------- */
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

#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

/* -------------------------------------------------------------------- */
/* initialisation_matrice: Alloue l'espace mémoire necéssaire pour une  */
/*                          matrice                                     */
/*                                                                      */
/* En entrée: Un pointeur sur un entier(taille en terme de ligne)       */
/*            Un pointeur sur un entier (taille en terme de colonne)    */
/*                                                                      */
/* En sortie: Un double pointeur sur un entier                          */
/* -------------------------------------------------------------------- */
int ** initialisation_matrice(int * taille_ligne, int * taille_colonne)
{

    int         ** matrice = (int **) malloc(*(taille_ligne) * sizeof(int *));
    int            i = 0, j;

    if(matrice)
    {
        while(i < *taille_ligne && (matrice[i] = (int *) malloc(*taille_colonne * sizeof(int))))
            ++i;

        if(i < *taille_ligne)
        {
            for(j = i; j >= 0;--j)
                free(matrice[i]);
        }
    }
    
    return matrice;

}

/* -------------------------------------------------------------------- */
/* liberer_matrice: Libère l'espace mémoire alloué à la matrice         */
/*                                                                      */
/* En entrée: Un double pointeur sur un entier (Sur la matrice)         */
/*            Un pointeur sur un entier (taille en terme de ligne)      */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void liberer_matrice(int ** matrice, int * taille_ligne)
{
    int           i;

    for(i = 0; i < *(taille_ligne);++i)
    {
        free(matrice[i]);
    }

    free(matrice);
}

/* -------------------------------------------------------------------- */
/* afficher_matrice: Affiche la matrice                                 */
/*                                                                      */
/* En entrée: Un double pointeur sur un entier (Sur la matrice)         */
/*            Un pointeur sur un entier (taille en terme de ligne)      */
/*            Un pointeur sur un entier (taille terme de colonne)       */
/*                                                                      */
/* En sortie: Void                                                      */
/* -------------------------------------------------------------------- */
void afficher_matrice(int ** matrice, int * taille_ligne, int * taille_colonne)
{

    int         i, j;
    for(i = 0; i < *(taille_ligne);++i)
    {
        for(j = 0; j < *(taille_colonne);++j)
        {
            fprintf(stdout,"%d ",matrice[i][j]);
        }
        fprintf(stdout, "\n");
    }
}

/* -------------------------------------------------------------------- */
/* creer_matrice: Crée la matrice à partir d'un fichier en paramètre    */
/*                                                                      */
/* En entrée: Un pointeur sur un char (Sur le nom du fichier)           */
/*            Un pointeur sur un entier (taille en terme de ligne)      */
/*            Un pointeur sur un entier (taille en terme de colonne)    */
/*                                                                      */
/* En sortie: Un double pointeur sur un entier (sur la matrice)         */
/* -------------------------------------------------------------------- */
int ** creer_matrice(const char * nom_fichier,int * taille_ligne, int * taille_colonne)
{
    FILE      * fichier_matrice;
    int      ** matrice;
    int         i, j;
    //On ouvre le fichier matrice
    if((fichier_matrice = fopen(nom_fichier, "r")) != NULL)
    {

        //On récupère les dimensions de la matrice sur la première ligne
            //L'énoncé stipule que le fichier est correct => pas de vérification supplémentaire
        fscanf(fichier_matrice,"%d %d", taille_ligne, taille_colonne);

        //On alloue de la mémoire pour la matrice
        matrice = initialisation_matrice(taille_ligne, taille_colonne);
        //On vérifie que l'allocation se soit bien passée
        if(matrice != NULL)
        {
            //On récupère dans la suite du fichier les éléments matrice(i,j)
            for(i = 0; i < *(taille_ligne);++i)
            {
                for(j = 0; j < *(taille_colonne);++j)
                {
                    fscanf(fichier_matrice,"%d",&matrice[i][j]);
                }
            }

        }
        else{
            fprintf(stdout, "Erreur : Allocation mémoire pour la matrice impossible !\n");
        }

        //On libère le pointeur sur le fichier matrice en fin de traitement
        fclose(fichier_matrice);
    }
    else
    {
        fprintf(stdout, "Erreur : Impossible d'ouvrir le fichier %s\n", nom_fichier);
    }
    return matrice;
}

#include "matrice.h"

#include <stdio.h>
#include <stdlib.h>

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

void liberer_matrice(int ** matrice, int * taille_ligne)
{
    int           i;

    for(i = 0; i < *(taille_ligne);++i)
    {
        free(matrice[i]);
    }

    free(matrice);
}

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

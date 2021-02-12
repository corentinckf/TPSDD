#include "matrice.h"
#include "lch.h"

int main(int argc, char * argv[])
{
    //Initialisation des variables
    int         ** matrice;
    cellule      * lch = NULL, ** prec;
    int            i = 0, j = 0,taille_ligne = 0, taille_colonne = 0, num_element = 0;
    int          * p_taille_colonne = &taille_colonne, * p_taille_ligne = &taille_ligne;
    int            k = atoi(argv[2]);
    //On procède au traitement uniquement si K et le nom du fichier sont donnés
    if(argc >=3)
    {

        matrice = creer_matrice(argv[1], p_taille_ligne, p_taille_colonne);
        //On affiche sur la sortie standard la matrice, pour vérifier que ça marche
        afficher_matrice(matrice, p_taille_ligne, p_taille_colonne);
        prec = &lch;
        //On crée la liste chaînée à partir de la matrice
        for(i = 0; i < taille_ligne;++i)
        {
            for(j = 0; j < taille_colonne;++j)
            {
                if(num_element < k)
                {
                    prec = recherche_prec_triee(&lch, matrice[i][j]);
                    cellule * element = alloc_cellule(matrice[i][j],j,i,NULL);
                    if(element)
                    {                        
                        ajouter_cellule(prec,element);
                        ++num_element;
                    }
                }else
                {
                    if(matrice[i][j] < lch->valeur)
                    {
                        supprimer_cellule(&lch);
                        prec = recherche_prec_triee(&lch, matrice[i][j]);
                        cellule * element = alloc_cellule(matrice[i][j],j,i,NULL);
                        if(element)
                        {
                            ajouter_cellule(prec,element);
                        }

                    }
                }

            }
        }

        printf("\n");
        afficher_lch(lch);

        //Et on libère l'espace mémoire alloué à la matrice en fin de traitement, en vérifiant que l'allocation de la matrice ai marchée
        if(matrice!=NULL)
            liberer_matrice(matrice, p_taille_ligne);

    }
    else
    {
        fprintf(stdout,"Erreur : Veuillez entrer K et un fichier matrice !\n");
    }

    return 0;
}

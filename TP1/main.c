#include "matrice.h"
#include "lch.h"

int main(int argc, char * argv[])
{
//Initialisation des variables
    int         ** matrice;
    cellule      * lch = NULL, ** prec;
    int            i = 0, j = 0,taille_ligne = 0, taille_colonne = 0, num_element = 0;
    int          * p_taille_colonne = &taille_colonne, * p_taille_ligne = &taille_ligne;
    int            k, u;
//On procède au traitement uniquement si K et le nom du fichier sont donnés
    if(argc >=3)
    {
        k = atoi(argv[2]);
        if(k < 0)
        {
            fprintf(stdout, "K doit-être au moins égal à 0 !\n");
            exit(0);
        }
        matrice = creer_matrice(argv[1], p_taille_ligne, p_taille_colonne);
//On affiche sur la sortie standard la matrice, pour vérifier que ça marche
        fprintf(stdout, "Matrice :\n");
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
//Affichage de la liste chaînée avant suppression des occurences
        fprintf(stdout, "Liste chaînée avant suppression :\n");
        afficher_lch(lch,stdout);

//Suppression des coûts de l'usine u (que si u est donné en argument)
        if(argc >= 4 && argv[3])
        {
            u = atoi(argv[3]);

            if(u >= 0 && u <= taille_ligne)
            {
                supprimer_occurence(&lch,u);
            }
            else{
                fprintf(stdout, "Le numéro d'usine ne peut-être négatif ou supérieur au nombre d'usine !\n");
                exit(0);
            }
        } 

            
//Affichage de la liste chaînée après suppression des occurences
        fprintf(stdout, "Liste chaînée après suppression :\n");
        afficher_lch(lch,stdout);
//On sauvegarde la liste dans un fichier
        sauvegarder_liste(lch,"sauvegarde.txt");

//Et on libère l'espace mémoire alloué à la matrice en fin de traitement, en vérifiant que l'allocation de la matrice ai marchée
        if(matrice)
            liberer_matrice(matrice, p_taille_ligne);
        
//En fin de traitement on libère la liste chaînée
        if(lch)
            liberer_lch(&lch);

    }
    else
    {
        fprintf(stdout,"Erreur : Veuillez entrer K et un fichier matrice !\n");
    }

    return 0;
}

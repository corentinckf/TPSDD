#include "arbre.h"
#include "pile.h"
#include <string.h>
#include <ctype.h>

/* -------------------------------------------------------------------- */
/* alloc_noeud: Crée un noeud et le renvoie                             */
/*                                                                      */
/* En entrée: la valeur du noeud, les adresses fils et frere            */
/*                                                                      */
/* En sortie: pointeur sur le noeud                                     */
/* -------------------------------------------------------------------- */
noeud_t * alloc_noeud(char valeur,noeud_t * fils, noeud_t * frere)
{
    noeud_t * element = (noeud_t *) malloc(sizeof(noeud_t));
    if(element)
    {
        element->valeur = valeur;
        element->fils = fils;
        element->frere = frere;
    }

    return element;   
}

/* -------------------------------------------------------------------- */
/* liberer_Arbre: Libere la mémoire allouée à l'arbre                   */
/*                                                                      */
/* En entrée: adresse pointeur sur la racine de l'arbre                 */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void liberer_Arbre(noeud_t ** racine)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * cour = *racine, * prec;
    int etat = 0, termine = 0;

    while(!termine)
    {
        while(cour)
        {
            empiler(pile, cour);  
            cour = cour->fils;
        }
            
        if(!estVide(pile))
        {
            depiler(pile, &cour, &etat);
            prec = cour;
            cour = cour->frere;
            free(prec);
        }else{
            termine = 1;
        }
        
    }
    liberer_Pile(&pile);

}

/* -------------------------------------------------------------------- */
/* creer_Arbre: Créee l'abre à partir de l'exp algèbrique               */
/*                                                                      */
/* En entrée: la chaîne de l'exp algèbrique                             */
/*                                                                      */
/* En sortie: pointeur sur le noeud racine                              */
/* -------------------------------------------------------------------- */
noeud_t * creer_Arbre(char * string)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * rac, *noeud;
    noeud_t ** prec=&rac; noeud_t * cour = rac;
    int i;
    int empiler_prochain = 1;
    int etat = 0;

    int taille_string = (int) strlen(string);

    //On parcour toute la string => for
    for(i=0; i < taille_string;++i)
    {
        switch(string[i])
        {
            case '*': 
                prec = &cour->fils;
                break;
            case '+':
                depiler(pile,&cour,&etat);
                prec = &cour->frere;
                empiler_prochain = 1;
                break;
            case '(': //Il faut empiler le prochain
                empiler_prochain = 1;
                break;
            case ')': // On depile
                depiler(pile,&cour,&etat);
                break;
            default: // Cas par defaut est en fait lettre quelconques
                noeud = alloc_noeud(string[i],NULL,NULL);
                *prec = noeud;
                cour = noeud;
                if(empiler_prochain)
                {
                    empiler(pile,cour);
                    empiler_prochain = 0;
                }
                break;     
        }
    }
    liberer_Pile(&pile);
    return rac;
}


/* -------------------------------------------------------------------- */
/* disp_Mots: Affiche les mots de l'arbre dans l'ordre alpha            */
/*                                                                      */
/* En entrée: le noeud racine de l'arbre, un préfixe à afficher         */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void disp_Mots(noeud_t * racine, char * motif)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t * cour = racine, * copie[MAX];
    int etat = 0;

    while(cour || ! estVide(pile))
    {
        
        while(cour)
        {
            empiler(pile, cour);
            if(isupper(cour->valeur)) //Si lettre maj, on a un mot
            {
                // On cree une copie de la pile
                    //Faire une fonction
                for(int i = 0; i < pile->sommet + 1;++i)
                    copie[i] = pile->base[i];
                
                //On l'affiche
                    //Faire une fonction
                printf("%s", motif);
                for(int i = 0; i < pile->sommet + 1;++i)
                    printf("%c", tolower(copie[i]->valeur)); 
                printf("\n");
            }   
            cour = cour->fils;
        }
        while(cour == NULL && !estVide(pile))
            depiler(pile, &cour, &etat);
        if(cour)
            cour = cour->frere;
        
    }
    liberer_Pile(&pile);
}

/* -------------------------------------------------------------------- */
/* recherche_prec_triee: Renvoie le prec où placer l'élement            */
/*                                                                      */
/* En entrée: le noeud "tête", la valeur recherchée                     */
/*                                                                      */
/* En sortie: Double pointeur sur un noeud                              */
/* -------------------------------------------------------------------- */
noeud_t ** recherche_prec_triee(noeud_t ** tete, char valeur)
{
    noeud_t ** prec = tete;
    noeud_t  * courant = *tete;
    while (courant && tolower(courant->valeur) < tolower(valeur))
    {
        prec = &(courant->frere);
        courant = courant->frere;
    }
    return(prec);
}

/* -------------------------------------------------------------------- */
/* recherche_prec_Arbre:Renvoie le prec où placer l'élement dans l'arbre*/
/*                                                                      */
/* En entrée: le noeud racine, la valeur recherchée , l'indice du mot   */
/*                                                                      */
/* En sortie: Double pointeur sur un noeud                              */
/* -------------------------------------------------------------------- */
noeud_t ** recherche_prec_Arbre(noeud_t ** rac, char * mot, int * i)
{
    pile_t * pile = initialiser_Pile(MAX);
    noeud_t ** prec=rac; noeud_t * cour = *rac;
    int traitement_fini = 0;
    *i = 0;

    while(!traitement_fini)
    {
        prec = recherche_prec_triee(prec, mot[*i]);
        cour = *prec;
        if(*prec && tolower((*prec)->valeur) == tolower(mot[*i]))
        {
            if(mot[(*i)+1] == '\0')
                traitement_fini = 1;
            prec = &cour->fils;
            cour = *prec;
            (*i)++;
            
        }else
        {
            traitement_fini = 1;
        }     
    }
    liberer_Pile(&pile);
    return prec;
}

/* -------------------------------------------------------------------- */
/* inserer_Lettre :Insérer une lettre dans l'arbre dans prec            */
/*                                                                      */
/* En entrée: le noeud prec, la lettre à insérer                        */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void inserer_Lettre(noeud_t ** prec, char valeur)
{
    noeud_t * noeud = alloc_noeud(valeur, NULL, NULL);
    if(noeud)
    {
        noeud->frere = *prec;
        *prec = noeud;
    }

}


/* -------------------------------------------------------------------- */
/* inserer_Mot :Insérer un mot dans l'arbre dans prec                   */
/*                                                                      */
/* En entrée: le noeud prec, le mot à insérer                           */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void inserer_mot(noeud_t ** racine, char * mot){

    int i = 0;

    noeud_t ** prec = recherche_prec_Arbre(racine, mot, &i);
    noeud_t *  cour = *prec;

    while(mot[i] != '\0')
    {
        prec = recherche_prec_triee(prec, mot[i]);
        inserer_Lettre(prec, mot[i]);
        cour = *prec;
        prec = &cour->fils;      
        ++i;
    }

    cour->valeur = toupper(cour->valeur);
}

/* -------------------------------------------------------------------- */
/* disp_motif :Afficher mot commencant par motif                        */
/*                                                                      */
/* En entrée: le noeud racine, le motif                                 */
/*                                                                      */
/* En sortie: void                                                      */
/* -------------------------------------------------------------------- */
void disp_motif(noeud_t ** racine, char * motif)
{
    int i = 0;
    noeud_t ** prec = recherche_prec_Arbre(racine, motif, &i);
    int longueur_motif = (int) strlen(motif);

    if(i==longueur_motif)
        disp_Mots(*prec, motif);

}

 
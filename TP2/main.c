#include "pile.h"
#include "file.h"

#define MAX 100000

/*Définition récursive de la fonction CNP*/
int CNP(int n, int p)
{
    int retour;
    if(n==p || !p)
        retour = 1;
    else
        retour = CNP(n-1,p) + CNP(n-1,p-1);
    return retour;
}

/*Traduction itérative de la fonction CNP*/
int CNP_IT(int n, int p)
{
    pile_t * pile = initialiser_Pile(MAX);
    element_t pi = p, *ppi = &pi;
    element_t ni = n, *pni = &ni;
    int etat = 0, * petat = &etat;
    int fin = 0,res = 0;
    while (!fin)
    {
        if(!(ni == pi || pi == 0))
        {
            empiler(pile,ni);
            empiler(pile,pi);
            --ni;
            
        }
        else
        {
            ++res;
            if(!estVide(pile))
            {
                depiler(pile, ppi, petat);
                depiler(pile, pni, petat);
                --ni;
                --pi;
            }else{
                fin = 1;
            }
        }
    }
    liberer_Pile(&pile);
    return res;
    
}

int main()
{
    printf("CNP(%d,%d) récursif = %d\n",5,3, CNP(5,3));
    printf("CNP(%d,%d) itératif = %d\n",5,3,CNP_IT(5,3));
    return 0;
}
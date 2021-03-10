#include "pile.h"
#include "file.h"

#define MAX 100000

int CNP(int n, int p)
{
    int retour;
    if(n==p || !p)
        retour = 1;
    else
        retour = CNP(n-1,p) + CNP(n-1,p-1);
    return retour;
}



int CNP_IT(int n, int p)
{
    pile_t * pile = initialiser_Pile(MAX);
    element_t ni = n, * pni = &ni;
    element_t pi = p, * ppi = &pi;
    int etat = 0, * petat = &etat, res = 0;
    int fin = 0;

    while (!fin)
    {
        while(ni == pi || !pi)
        {
            empiler(pile,ni);
            ++res;
            --ni;
        }
        if(!estVide(pile))
        {
            depiler(pile,pni,petat);
            depiler(pile,ppi,petat);
            --ni;
            --pi;
        }
        else
        {
            fin = 1;
        }
        
    }

    liberer_Pile(&pile);
    return res;
    
}

int main()
{
    printf("CNP(%d,%d) récursif = %d\n",5,3, CNP(5,3));
    printf("CNP(%d,%d) itératif = %d\n",5,3,CNP_IT(5,3));
    pile_t * pile = initialiser_Pile(MAX);
    element_t test = 2;
    printf("%d\n", estVide(pile));
    int oui = empiler(pile,test);
    printf("%d\n", estVide(pile));

    return 0;
}
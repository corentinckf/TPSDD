#include "pile.h"
#include "file.h"

int CNP(int n, int p)
{
    int retour;
    if(n==p || !p)
        retour = 1;
    else
        retour = CNP(n-1,p) + CNP(n-1,p-1);
    return retour;
}

int main()
{
    printf("%d", CNP(5,3));
    return 0;
}
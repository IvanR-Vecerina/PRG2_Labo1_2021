#include <stdio.h>
#include "listes_dynamiques.h"

int main() {
    Liste* l = initialiser();
    //afficher(l, FORWARD);
    insererEnTete(l, (Info) 1);
    afficher(l, FORWARD);
    insererEnQueue(l, (Info) 2);
    afficher(l, FORWARD);
    Info* i;
    supprimerEnQueue(l,i);
    afficher(l, FORWARD);
    printf(i);
    supprimerEnTete(l,i);
    afficher(l, FORWARD);
    printf(i);
    return 0;
}

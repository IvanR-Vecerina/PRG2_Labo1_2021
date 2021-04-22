#include <stdio.h>
#include "listes_dynamiques.h"

int main() {
    Liste* l = initialiser();
    //afficher(l, FORWARD);
    Info i1 = 1;
    insererEnTete(l,  &i1);
    afficher(l, FORWARD);
    i1 = 2;
    insererEnQueue(l,  &i1);
    afficher(l, FORWARD);

    return 0;
}

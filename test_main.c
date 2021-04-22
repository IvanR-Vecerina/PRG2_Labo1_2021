#include "listes_dynamiques.h"

#include <stdlib.h>
#include <stdio.h>
int main(){
    Liste * l = initialiser();
    afficher(l,FORWARD);
    int a = 10;
    insererEnTete(l,&a);
    ++a;
    afficher(l,FORWARD);
    size_t n = 10;
    while(n--){
        insererEnQueue(l,&n);
        
        //afficher(l,FORWARD);
    }
    n = 10;
    while(n--) {
        afficher(l,FORWARD);
        supprimerEnTete(l, &a);
    }
    
//    Element* e = calloc(1,sizeof (Element));
//    Element* e1 = calloc(1,sizeof (Element));
//    e1->info = 2;
//    e->info = 1;
//    e->suivant = e1;
//    e1->precedent = e;
//    
//    l->queue = e1;
//    l->tete = e;
//    afficher(l,BACKWARD);
//    printf("%s\n",estVide(l)?"true":"false");
//    printf("%d\n",longueur(l));
//    
//    free(e1);
//    e1=NULL;
//    free(e);
//    e=NULL;
//    free(l);
//    l=NULL;
}
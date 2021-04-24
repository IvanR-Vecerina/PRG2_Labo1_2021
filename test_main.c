#include "listes_dynamiques.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

bool crit(size_t position, const Info *info){
    int min = 1;
    int max = 3;
    return (position%2) && (*info) >=min && (*info) <= max;
}
void generate(Liste* l, size_t n){
    while(n--)
        insererEnTete(l,(Info*)&n);
}
int main(){
    sleep(10); //to attach pid
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
    n = 15;//call to suprimerEnTete more time than there is element
    while(n--) {
        afficher(l,FORWARD);
        supprimerEnTete(l, &a);
    }
    
    Element* e = calloc(1,sizeof (Element));
    Element* e1 = calloc(1,sizeof (Element));
    e1->info = 2;
    e->info = 1;
    e->suivant = e1;
    e1->precedent = e;

    l->queue = e1;
    l->tete = e;
    afficher(l,BACKWARD);
    printf("%s\n",estVide(l)?"true":"false");
    printf("%zu\n",longueur(l));

    free(l);
    l = initialiser();
    n = 10;
    while( n--){
        insererEnQueue(l, (const Info *) &n);
    }
    n=10;
    while(n--){
        afficher(l,FORWARD);
        supprimerEnQueue(l,&a);
    }
    afficher(l,FORWARD);
    generate(l,10);
    afficher(l,FORWARD);
    supprimerSelonCritere(l,crit);
    afficher(l,FORWARD);
    vider(l,0);
    afficher(l,FORWARD);
    generate(l,10);
    Liste *ll = initialiser();
    generate(ll,10);
    printf("\n\n");
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("%s\n",sontEgales(l,ll)?"true":"false");

    vider(l,0);
    afficher(l,FORWARD);
    generate(l,10);
    afficher(l,FORWARD);
     vider(ll,0);
    printf("----------------------------------------------------------------------\n");
    n = 10;
    
    while(n--) {
        afficher(l, FORWARD);
        vider(l, n);
    }
    afficher(l,FORWARD);
    vider(l,0);
    vider(ll,0);
    generate(l,10);
    generate(ll,10);
    vider(ll,0);
    printf("%s",sontEgales(ll,l)?"true":"false");
    vider(l,0);
    free(e);
    free(e1);
    free(l);
    free(ll);
    
    
    sleep(10);
}

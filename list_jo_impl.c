//
//
#import "stdio.h"
#include "stdlib.h"
#import "listes_dynamiques.h"

// Initialisation de la liste.
// NB Cette fonction doit obligatoirement être utilisée pour se créer une liste
// car elle garantit la mise à NULL des champs tete et queue de la liste
Liste* initialiser(){
    Liste *l = calloc(1,sizeof(Liste));
    return l;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste* liste){
    return !(liste->tete) || !(liste->queue); //or or and, because if empty
    
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste* liste){
    Element * ptr = liste->tete;
    if(!ptr)
        return 0;
    size_t i = 0;
    while(ptr){
        ptr = ptr->suivant;
        ++i;
    }
    return i;
}
// ----------------------------------------------

// ------------------------------------------------------------------------------
// Affiche le contenu intégral de liste sous la forme : [info_1,info_2,...]
// Dans le cas d'une liste vide, affiche : []
// En mode FORWARD, resp. BACKWARD, l'affichage se fait en parcourant liste
// dans le sens tete -> queue, resp. queue -> tete.
void afficher(const Liste* liste, Mode mode){
    printf("%c",'[');
    Element* e = NULL;
    if(mode == FORWARD){
        e = liste->tete;
        while(e){
            printf("%d",e->info);
            e = e->suivant;
            if(e)
                printf(", ");
        }
    }else{
        e = liste->queue;
        while(e){
            printf("%d",e->info);
            e = e->precedent;
            if(e)
                printf(", ");
        }
    }
    printf("%c",']');

}

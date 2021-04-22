//
//
#import "stdio.h"
#include "stdlib.h"
#import "listes_dynamiques.h"

// Initialisation de la liste.
// NB Cette fonction doit obligatoirement être utilisée pour se créer une liste
// car elle garantit la mise à NULL des champs tete et queue de la liste
Liste *initialiser() {
    Liste *l = calloc(1, sizeof(Liste));
    return l;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste est vide, false sinon.
bool estVide(const Liste *liste) {
    return !(liste->tete) || !(liste->queue); //or or and, because if empty

}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste *liste) {
    Element *ptr = liste->tete;
    if (!ptr)
        return 0;
    size_t i = 0;
    while (ptr) {
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
void afficher(const Liste *liste, Mode mode) {
    printf("%c", '[');
    Element *e = NULL;
    if (mode == FORWARD) {
        e = liste->tete;
        while (e) {
            printf("%d", e->info);
            e = e->suivant;
            if (e)
                printf(", ");
        }
    } else {
        e = liste->queue;
        while (e) {
            printf("%d", e->info);
            e = e->precedent;
            if (e)
                printf(", ");
        }
    }
    printf("%c\n", ']');
}
/*
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément. 
Status insererEnTete(Liste *liste, const Info *info) {
    Element *e = calloc(1, sizeof(Element));
    if (!e) {
        return MEMOIRE_INSUFFISANTE;
    }
    e->info = *info; //deep copy

    if (estVide(liste)) {
        liste->tete = e;
        liste->queue = e;
        return OK;
    }

    Element *ex = liste->tete;
    liste->tete = e;
    e->suivant = ex;
    ex->precedent = e;
    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément. 
Status insererEnQueue(Liste *liste, const Info *info) {
    Element *e = calloc(1, sizeof(Element));
    if (!e) {
        return MEMOIRE_INSUFFISANTE;
    }
    e->info = *info; //deep copy

    if (estVide(liste)) {
        liste->tete = e;
        liste->queue = e;
        return OK;
    }

    Element *ex = liste->queue;
    liste->queue = e;
    e->precedent = ex;
    ex->suivant = e;
    return OK;
}


// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste *liste, Info *info) {
    if (estVide(liste)) {
        return LISTE_VIDE;
    }
    Element *e = liste->tete;
    *info = e->info;
    if (!(e->suivant)) {//there is only one element
        liste->tete = liste->queue = NULL;
        return OK;
    }
    e->suivant->precedent = NULL;
    liste->tete = liste->tete->suivant;
    free(e);
    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste *liste, Info *info) {
    if (estVide(liste)) {
        return LISTE_VIDE;
    }
    Element *e = liste->queue;
    *info = e->info;
    if (!(e->precedent)) {//there is only one element
        liste->tete = liste->queue = NULL;
        return OK;
    }
    e->precedent->suivant = NULL; //last ptr doesn't have a next node
    liste->queue = liste->queue->precedent;
    free(e);
    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
bool crit(size_t position, const Info *info){
    int min = 1;
    int max = 3;
    return position%2 && (*info) >=min && (*info) <= max;
}
void deleteNode(Liste* l,Element *n);
void supprimerSelonCritere(Liste *liste,
                           bool (*critere)(size_t position, const Info *info)) {
    size_t i = 0;
    Element *ptr = liste->tete;
    while(ptr){
        Element *ex = ptr; 
        ptr = ptr->suivant;
        if(critere(i, &(ex->info))){
            deleteNode(liste,ex);
        }
    }
    
}
//4 cas a considerer : en tete, en queue, au milieu, au milieu mais seul 
void deleteNode(Liste* l,Element *n){
    if (n == l->tete) 
        l->tete = n->suivant;
    if (n == l->queue) 
        l->queue = n->precedent;
    if (n->suivant)
        n->suivant->precedent = n->precedent;
    if (n->precedent)
        n->precedent->suivant = n->suivant;
    free(n);
    
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// NB Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste *liste, size_t position) {
    //max en O(N)
    if (estVide(liste))
        return;
    size_t i = 0;
    Element *ptr = liste->tete;
    while (ptr && i != position) {
        ++i;
        ptr = ptr->suivant;
    }        
    while (ptr != liste->queue) {
        Element *e = liste->queue;
        liste->queue = liste->queue->precedent;
        free(e);
    }
    if (position == 0)
        liste->tete = NULL;
    liste->queue->suivant = NULL;
}

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// NB 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2);
// ------------------------------------------------------------------------------
*/


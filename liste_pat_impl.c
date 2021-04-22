#include "listes_dynamiques.h"
#include <stdlib.h>

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnTete(Liste* liste, const Info* info){
    Element* newElement = calloc(1,sizeof(Element));
    if(newElement == NULL) return MEMOIRE_INSUFFISANTE;
    newElement->info      = info;
    newElement->suivant   = liste->tete;
    newElement->precedent = NULL;
    liste->tete           = newElement;

    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Insère un nouvel élément (contenant info) en queue de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément.
Status insererEnQueue(Liste* liste, const Info* info) {
    Element* newElement = calloc(1,sizeof(Element));
    if(newElement == NULL) return MEMOIRE_INSUFFISANTE;
    newElement->info      = info;
    newElement->suivant   = NULL;
    newElement->precedent = liste->queue;
    liste->queue           = newElement;

    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en tête de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnTete(Liste* liste, Info* info) {
    if(estVide(liste)) return LISTE_VIDE;
    Element* newHead = liste->tete->suivant;
    free(liste->tete);
    newHead->precedent = NULL;
    liste->tete = newHead;
    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie, via le paramètre info, l'info stockée dans l'élément en queue de liste,
// puis supprime, en restituant la mémoire allouée, ledit élément.
// Renvoie LISTE_VIDE si la liste passée en paramètre est vide, OK sinon.
Status supprimerEnQueue(Liste* liste, Info* info) {
    if(estVide(liste)) return LISTE_VIDE;
    Element* newTail = liste->queue->precedent;
    free(liste->queue);
    newTail->suivant = NULL;
    liste->tete = newTail;
    return OK;
}
// ------------------------------------------------------------------------------

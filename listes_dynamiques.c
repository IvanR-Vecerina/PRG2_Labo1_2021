/*
-----------------------------------------------------------------------------------
Nom du fichier : listes_dynamiques.c
Nom du labo    : labo 1 : liste doublement chainee
Auteur(s)      : Patrick Furrer, Joris Schaller, Ivan Vecerina
Date creation  : 27.04.2021.
Description    : implementation de la librairie permettant la gestion de listes doublement chaînées
                  non circulaires

 Remarque(s)    : -

 Compilateur    : Apple clang version 12.0.0 (clang-1200.0.32.2)/Mingw-w64 gcc 8.1.0
-----------------------------------------------------------------------------------
*/



#include "stdio.h"
#include "stdlib.h"
#include "listes_dynamiques.h"

//4 cas a considerer : n = tete, n = queue, n = un maillon au hasard ou un element seul dans la liste
void deleteNode(Liste *l, Element *n) {
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
    return !(liste->tete) || !(liste->queue); // Si seulement un des ptr est a NULL, nous avons une liste malformee
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie combien il y a d'éléments dans liste.
size_t longueur(const Liste *liste) {
    Element *ptr = liste->tete;
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
    if (estVide(liste)) {
        printf("[]\n");
        return;
    }
    printf("[");
    Element *e = mode == FORWARD ?     //prend le prochain element en fonction du mode
                 liste->tete : liste->queue;
    while (e) {
        printf("%d, ", e->info);
        e = mode == FORWARD ?
            e->suivant : e->precedent;
    }
    printf("\b\b]\n");//supprime les derniers ,<space> chars
}

// Insère un nouvel élément (contenant info) en tête de liste.
// Renvoie OK si l'insertion s'est déroulée avec succès et MEMOIRE_INSUFFISANTE
// s'il n'y a pas assez de mémoire pour créer le nouvel élément. 
Status insererEnTete(Liste *liste, const Info *info) {
    Element *e = calloc(1, sizeof(Element));
    if (!e) {
        return MEMOIRE_INSUFFISANTE;
    }
    e->info = *info; // copie profonde

    if (estVide(liste)) {       //pas suffisament de code pour extraire dans sa propre fonction
        liste->tete = liste->queue = e;
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
    e->info = *info;

    if (estVide(liste)) {
        liste->tete = liste->queue = e;
        return OK;
    }

    Element *ex = liste->queue; //cas courant
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
    *info = liste->tete->info;
    deleteNode(liste,liste->tete);//supprime l'élément de tete
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
    *info = liste->tete->info;
    deleteNode(liste,liste->queue);//supprime l'élément de queue

    return OK;
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs


void supprimerSelonCritere(Liste *liste,
                           bool (*critere)(size_t position, const Info *info)) {
    //le parametre position est utilisée dans la fonction critere a l'interne
    size_t i = 0;
    Element *ptr = liste->tete;
    while (ptr) {
        Element *ex = ptr;
        ptr = ptr->suivant;
        if (critere(i, &(ex->info))) {
            deleteNode(liste, ex);
        }
        ++i;
    }
}


// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// NB Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste *liste, size_t position) {
    //Θ(N)
    size_t i = 0;
    Element *ptr = liste->tete;
    while (ptr) {
        if (i >= position) {//on supprime le ptr courant et on avance au suivant
            Element *e = ptr;
            ptr = ptr->suivant;
            deleteNode(liste, e);
        } else
            ptr = ptr->suivant;//si on ne supprime pas on avance quand meme
        ++i;
    }
}

// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// NB 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste *liste1, const Liste *liste2) {
    if (liste1->tete == liste2->tete && liste1->queue == liste2->queue) //handle ptr to the same list and 2 empty list
        return true;
    Element *e1 = liste1->tete;
    Element *e2 = liste2->tete;

    while (e1 && e2) {
        if (e1->info != e2->info)
            return false;

        if (!e1->suivant != !e2->suivant) { // if ONLY one of the pointer is null 
            return false;
        }
        e1 = e1->suivant;
        e2 = e2->suivant;
    }
    return !e1 == !e2;//handle the case were liste1 or liste2 is empty but not the other (and we didn't enter in the while)
}

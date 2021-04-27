/*
-----------------------------------------------------------------------------------
Nom du fichier : main.c
Nom du labo    : labo 1 : liste doublement chainee
Auteur(s)      : Patrick Furrer, Joris Schaller, Ivan Vecerina
Date creation  : 27.04.2021.
Description    : Programme de teste qui utilise l'ensemble des fonctionnalites offertes par la liste doublement chainee
                 et verifie son bon fonctionnement.

 Remarque(s)    : -

 Compilateur    :  Compilateur    : Apple clang version 12.0.0 (clang-1200.0.32.2)/Mingw-w64 gcc 8.1.0
-----------------------------------------------------------------------------------
*/

#include "listes_dynamiques.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define DIX  10

void test_initialiser();

void test_estVide();

void test_insererEtSupprimerEnChangeLongeur();

void test_vider();

void test_sontEgales();

bool crit(size_t position, const Info *info) {
    int min = 1;
    int max = 5;
    return (position % 2) && (*info) >= min && (*info) <= max;
}

void generate(Liste *l, size_t n) {
    while (n--)
        insererEnTete(l, (Info *) &n);
}

int main() {
    printf("Unit test ...\n");

    test_initialiser();
    test_insererEtSupprimerEnChangeLongeur();
    test_estVide();
    test_sontEgales();
    test_vider();
    printf("Unit test ...OK\n");

    printf("Running tests ...\n");


    Liste *l = initialiser();
    printf("Affichage d'un liste vide \n");
    afficher(l, FORWARD);
    int a = DIX;
    printf("inserer en tete \n");
    insererEnTete(l, &a);
    ++a;
    afficher(l, FORWARD);
    Info n = DIX;
    printf("\ninserer en queue\n");
    while (n--) {
        insererEnQueue(l, &n);
        afficher(l,FORWARD);
    }
    n = DIX + 5;//call to suprimerEnTete more time than there is element
    printf("\nsupprimer en tete 15X\n");

    while (n--) {
        afficher(l, FORWARD);
        supprimerEnTete(l, &a);
    }
    //list is now empty

    //create two nodes
    printf("\nInsertion manuel dans une liste vide et affichage a l'envers\n");

    Element *e = calloc(1, sizeof(Element));
    Element *e1 = calloc(1, sizeof(Element));
    e1->info = 2;
    e->info = 1;
    e->suivant = e1;
    e1->precedent = e;

    //insert nodes
    l->queue = e1;
    l->tete = e;

    //print the two nodes
    afficher(l, BACKWARD);
    printf("la liste est vide ? : %s\n", estVide(l) ? "true" : "false");//false because we inserted two nodes
    printf("la longueur de la liste vaut : %zu\n", longueur(l));//2
    assert(longueur(l) == 2);

    free(l);
    l = initialiser();
    n = DIX;
    printf("\nGeneration d'une liste de longeur 10...\n");

    while (n--) {
        insererEnQueue(l, (const Info *) &n); // insert ten nodes
    }
    n = DIX;
    printf("\naffichage a l'endroit puis a l'envers des suppressions en queue de la liste\n");
    while (n--) {
        afficher(l, FORWARD);
        afficher(l, BACKWARD);
        supprimerEnQueue(l, &a); //delete the previously inserted nodes
    }

    //list is now empty
    printf("\nGeneration d'une liste de longeur 10...\n");
    Info z = 1;
    n = DIX;
    while(n--) {
        insererEnQueue(l, &z);
        z *= 2;
    }
    afficher(l, FORWARD);

    printf("Suppression des elements à position impaire et qui ont des valeures comprises entre 1 et 5 (inclus) \n");
    supprimerSelonCritere(l, crit);
    assert(longueur(l) == 9); //Seulement 1 element retourne true avec notre fonction critere la valeur 2
    afficher(l, FORWARD);

    printf("\nAffichage de la liste apres vidage\n");
    vider(l, 0);
    assert(longueur(l) == 0);
    afficher(l, FORWARD);

    printf("\nGeneration de deux listes de longeurs 10");
    generate(l, DIX);
    assert(longueur(l) == DIX);
    Liste *ll = initialiser();
    generate(ll, DIX);
    assert(longueur(ll) == DIX);
    printf("\n");
    afficher(l, FORWARD);
    afficher(ll, FORWARD);
    printf("les deux list sont egales : %s\n", sontEgales(l, ll) ? "true" : "false");

    printf("\nSituation apres suppresion d'un element de la liste 1\n");
    vider(l, longueur(l)-1);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("les deux list sont egales : %s\n", sontEgales(l, ll) ? "true" : "false");

    printf("\nSituation apres vidage de la liste 1\n");
    vider(l, 0);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("les deux list sont egales : %s\n", sontEgales(l, ll) ? "true" : "false");
    assert(longueur(l) == 0);
    assert(!sontEgales(l, ll));

    printf("\nSituation apres vidage de la liste 2\n");
    vider(ll, 0);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("les deux list sont egales : %s\n", sontEgales(l, ll) ? "true" : "false");


    printf("\nRemplissage de la liste 1\n");
    generate(l, DIX);
    afficher(l, FORWARD);
    vider(ll, 0);

    n = DIX;
    printf("\nVidage incremental de la liste 1\n");
    while (n--) {
        afficher(l, FORWARD);
        assert(longueur(l) == n + 1);//longueur is one greater than n ie: 9th element means 10 element in total
        vider(l, n);
        assert(longueur(l) == n);
    }
    afficher(l, FORWARD);

    vider(l, 0);
    vider(ll, 0);
    assert(longueur(l) == 0);
    assert(longueur(ll) == 0);

    free(e);
    free(e1);
    free(l);
    free(ll);

    printf("Running tests ...OK\n");
}

void test_initialiser() {
    Liste *l = initialiser();
    if (!l) {
        printf("Unable to allocate memory for the list");
        exit(-1);
    }
    assert(l->tete == NULL);
    assert(l->queue == NULL);
    free(l);
}

void test_estVide() {
    Liste *l = initialiser();
    assert(estVide(l));
    Element *e = calloc(1, sizeof(Element));
    l->tete = l->queue = e;
    assert(!estVide(l));
    assert(longueur(l) == 1);

    free(e);
    free(l);
}

void test_insererEtSupprimerEnChangeLongeur() {
    Liste *l = initialiser();
    assert(longueur(l) == 0);
    Info a = 0;
    if (insererEnTete(l, &a) == OK) {
        assert(longueur(l) == 1);
    }
    supprimerEnTete(l, &a);
    assert(longueur(l) == 0);
    assert(supprimerEnTete(l,&a) == LISTE_VIDE);
    assert(estVide(l));

    if (insererEnQueue(l, &a) == OK) {
        assert(longueur(l) == 1);
    }
    supprimerEnQueue(l, &a);
    assert(longueur(l) == 0);
    assert(supprimerEnQueue(l,&a) == LISTE_VIDE);
    assert(estVide(l));


    size_t n = DIX;
    generate(l, DIX);
    assert(longueur(l) == DIX);
    while (n--) {
        assert(longueur(l) == (size_t) (n + 1));
        supprimerEnTete(l, &a);
    }
    n = 0;
    while (n < DIX) {
        insererEnTete(l, &a);
        assert(longueur(l) == n + 1);
        ++n;
    }
    vider(l, 0);
    free(l);
}

void test_vider() {
    Liste *l = initialiser();
    int n = DIX;
    while (n--) {
        insererEnTete(l, &n);
    }
    int c = DIX * DIX;
    while (c--) {
        vider(l, (size_t) c);
        if (c >= DIX) {
            assert(longueur(l) == DIX);
        } else {
            assert(longueur(l) == (size_t) c);
        }
    }
    free(l);
}

void test_sontEgales() {
    Liste *l = initialiser();
    Liste *ll = initialiser();
    Info a = 0;
    assert(sontEgales(l, ll)); //equal is commutative
    assert(sontEgales(ll, l));

    insererEnTete(l, &a);
    insererEnTete(ll, &a);
    assert(sontEgales(ll, l));
    assert(sontEgales(l, ll));
    supprimerEnTete(l, &a);
    assert(!sontEgales(l, ll));
    assert(!sontEgales(ll, l));
    supprimerEnTete(ll, &a);
    generate(ll, 10);
    generate(l, 10);
    supprimerEnTete(l, &a);
    assert(!sontEgales(l, ll));//tete is differente
    vider(l, 0);
    vider(ll, 0);
    free(ll);
    ll = l;
    assert(sontEgales(ll, l));
    insererEnTete(l, &a);
    assert(sontEgales(ll, l));
    vider(l, 0);
    free(l);
}

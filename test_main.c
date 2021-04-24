#include "listes_dynamiques.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#define DIX  10

void test_initialiser();

void test_estVide();

void test_insererEtSupprimerEnTeteChangeLongeur();

void test_vider();

void test_sontEgales();

bool crit(size_t position, const Info *info) {
    int min = 1;
    int max = 3;
    return (position % 2) && (*info) >= min && (*info) <= max;
}

void generate(Liste *l, size_t n) {
    while (n--)
        insererEnTete(l, (Info *) &n);
}

int main() {
    //sleep(10); //to attach pid

    Liste *l = initialiser();
    afficher(l, FORWARD);
    int a = DIX;
    insererEnTete(l, &a);
    ++a;
    afficher(l, FORWARD);
    size_t n = DIX;
    while (n--) {
        insererEnQueue(l, &n);

        //afficher(l,FORWARD);
    }
    n = DIX + 5;//call to suprimerEnTete more time than there is element
    while (n--) {
        afficher(l, FORWARD);
        supprimerEnTete(l, &a);
    }

    Element *e = calloc(1, sizeof(Element));
    Element *e1 = calloc(1, sizeof(Element));
    e1->info = 2;
    e->info = 1;
    e->suivant = e1;
    e1->precedent = e;

    l->queue = e1;
    l->tete = e;
    afficher(l, BACKWARD);
    printf("%s\n", estVide(l) ? "true" : "false");
    printf("%zu\n", longueur(l));
    assert(longueur(l) == 2);

    free(l);
    l = initialiser();
    n = DIX;
    while (n--) {
        insererEnQueue(l, (const Info *) &n);
    }
    n = DIX;
    while (n--) {
        afficher(l, FORWARD);
        supprimerEnQueue(l, &a);
    }
    afficher(l, FORWARD);
    afficher(l, BACKWARD);
    generate(l, DIX);
    afficher(l, FORWARD);
    supprimerSelonCritere(l, crit);
    assert(longueur(l) == 8); //there is only 1 and 3 returning true with crit
    afficher(l, FORWARD);
    vider(l, 0);
    assert(longueur(l) == 0);
    afficher(l, FORWARD);
    generate(l, DIX);
    assert(longueur(l) == DIX);
    Liste *ll = initialiser();
    generate(ll, DIX);
    assert(longueur(ll) == DIX);
    printf("\n\n");
    afficher(l, FORWARD);
    afficher(ll, FORWARD);
    printf("les deux list sont egales : %s\n", sontEgales(l, ll) ? "true" : "false");

    vider(l, 0);
    assert(longueur(l) == 0);

    afficher(l, FORWARD);
    generate(l, DIX);
    afficher(l, FORWARD);
    vider(ll, 0);
    printf("----------------------------------------------------------------------\n");
    n = DIX;

    while (n--) {
        afficher(l, FORWARD);
        assert(longueur(l) == n + 1);//longueur is one greater than n ie: 9th element means 10 element in total
        vider(l, n);
        assert(longueur(l) == n);

    }
    afficher(l, FORWARD);
    vider(l, 0);
    assert(longueur(l) == 0);
    vider(ll, 0);
    assert(longueur(ll) == 0);

    generate(l, 10);
    assert(longueur(l) == 10);

    generate(ll, 10);
    assert(longueur(ll) == 10);

    vider(ll, 0);
    printf("%s", sontEgales(ll, l) ? "true" : "false");
    vider(l, 0);
    free(e);
    free(e1);
    free(l);
    free(ll);

    test_initialiser();
    test_insererEtSupprimerEnTeteChangeLongeur();
    test_estVide();
    test_sontEgales();
    test_vider();
    sleep(10);
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

    free(e);
    free(l);
}

void test_insererEtSupprimerEnTeteChangeLongeur() {
    Liste *l = initialiser();
    assert(longueur(l) == 0);
    Info a = 0;
    if (insererEnTete(l, &a) == OK) {
        assert(longueur(l) == 1);
    }
    supprimerEnTete(l, &a);
    assert(longueur(l) == 0);
    assert(estVide(l));

    size_t n = 10;
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
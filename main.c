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
#define MSG "Impossible d'allouer de la memoire, fermeture..."
#define NETTOIE(l) \
    do{ \
    printf("%s",MSG); \
    vider(l,0); \
    free(l);   \
    }while(0)
#define EG "les deux list sont egales :"
#define MIN 1
#define MAX 5
#define GENERATION "Generation d'une liste de longeur 10..."
#define SITUATION "Situation apres vidage de la liste "

void test_initialiser();

void test_estVide();

void test_insererEtSupprimerEnChangeLongeur();

void test_vider();

void test_sontEgales();

bool crit(size_t position, const Info *info) {
    
    return (position % 2) && (*info) >= MIN && (*info) <= MAX;
}
bool criter2(size_t position, const Info *info) {
    return true;
}
//generate retourne 1 si une erreur est arrive lors de l'execution 0 sinon
bool generate(Liste *l, size_t n) {
    bool flag = 0;
    while (n--)
        flag |= insererEnTete(l, (Info *) &n) == OK ? 0 : 1;
    return flag;
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
    n = DIX + 5;//appel a  suprimerEnTete plus de fois qu'il n'existe d'element
    printf("\nsupprimer en tete 15X\n");
    while (n--) {
        afficher(l, FORWARD);
        supprimerEnTete(l, &a);
    }
    //la liste est desormais vide

    //generation de deux element 
    printf("\nInsertion manuel dans une liste vide et affichage a l'envers\n");

    Element *e = calloc(1, sizeof(Element));
    if(!e){
        NETTOIE(l);
        exit(-1);
    }
    Element *e1 = calloc(1, sizeof(Element));
    if(!e1){
        NETTOIE(l);
        free(e);
        exit(-1);
    }
    
    e1->info = 2;
    e->info = 1;
    e->suivant = e1;
    e1->precedent = e;

    //insert nodes
    l->queue = e1;
    l->tete = e;

    //affiche les deux noeuds
    afficher(l, BACKWARD);
    printf("la liste est vide ? : %s\n", estVide(l) ? "vrai" : "faux");//faux car deux noeuds ont été insérer
    printf("la longueur de la liste vaut : %zu\n", longueur(l));//2
    assert(longueur(l) == 2);
    free(e);
    free(e1);
    free(l);
    l = initialiser();
    if(!l){
        printf("%s",MSG);
        exit(-1);
    }
    n = DIX;
    printf("\n%s\n", GENERATION);

    while (n--) {
        if(insererEnQueue(l, (const Info *) &n) != OK){
            NETTOIE(l);
            exit(-1);
        }
    }
    n = DIX;
    printf("\nAffichage a l'endroit puis a l'envers des suppressions en queue de la liste\n");
    while (n--) {
        afficher(l, FORWARD);
        afficher(l, BACKWARD);
        supprimerEnQueue(l, &a); //supprime les noeuds inserer
        printf("\nValeur supprimee: %d\n",a);
    }

    //liste est vide
    printf("\n%s\n", GENERATION);
    Info z = 1;
    n = DIX;
    while(n--) {
        if(insererEnQueue(l, &z) != OK){
            NETTOIE(l);
            exit(-1);
        }
        z *= 2;
    }
    afficher(l, FORWARD);

    printf("Suppression des elements à position impaire et qui ont des valeures comprises entre %d et %d (inclus) \n",MIN, MAX);
    supprimerSelonCritere(l, crit);
    assert(longueur(l) == 9); //Seulement 1 element retourne true : la valeur 2
    afficher(l, FORWARD);

    printf("\nAffichage de la liste apres vidage\n");
    supprimerSelonCritere(l,criter2);//critere2 retourn vrai pour tous les elements
    assert(longueur(l) == 0);
    afficher(l, FORWARD);

    printf("\n%s", GENERATION);
    if(generate(l, DIX)){
        printf("%s",MSG);
        NETTOIE(l);
        exit(-1);
    }
    
    printf("\n%s", GENERATION);
    assert(longueur(l) == DIX);
    Liste *ll = initialiser();
    if(generate(ll, DIX)){
        printf("%s",MSG);
        NETTOIE(l);
        NETTOIE(ll);
        exit(-1);
    }
    assert(longueur(ll) == DIX);
    printf("\n");
    afficher(l, FORWARD);
    afficher(ll, FORWARD);
    printf("%s%s\n", EG,sontEgales(l, ll) ? "true" : "false");

    printf("\nSituation apres suppresion d'un element de la liste 1\n");
    vider(l, longueur(l)-1);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("%s%s\n", EG,sontEgales(l, ll) ? "true" : "false");

    printf("\n%s %d\n",SITUATION,1);
    vider(l, 0);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("%s%s\n", EG,sontEgales(l, ll) ? "true" : "false");
    assert(longueur(l) == 0);
    assert(!sontEgales(l, ll));

    printf("\n%s %d\n",SITUATION,2);
    vider(ll, 0);
    afficher(l,FORWARD);
    afficher(ll,FORWARD);
    printf("%s%s\n", EG,sontEgales(l, ll) ? "true" : "false");


    printf("\nRemplissage de la liste 1\n");
    if(generate(l, DIX)){
        
    }
    afficher(l, FORWARD);

    n = DIX;
    printf("\nVidage incremental de la liste 1\n");
    while (n--) {
        afficher(l, FORWARD);
        assert(longueur(l) == (size_t)(n + 1));//longueur est plus grand de 1 que n
        vider(l, (size_t)n);
        assert(longueur(l) == (size_t)n);
    }
    afficher(l, FORWARD);

    vider(l, 0);
    vider(ll, 0);
    assert(longueur(l) == 0);
    assert(longueur(ll) == 0);

    
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
    if(!l){
        printf("%s",MSG);
        exit(-1);
    }
    assert(estVide(l));
    Element *e = calloc(1, sizeof(Element));
    if(!e){
        printf("%s",MSG);
        exit(-1);
    }
    l->tete = l->queue = e;
    assert(!estVide(l));
    assert(longueur(l) == 1);

    free(e);
    free(l);
}

void test_insererEtSupprimerEnChangeLongeur() {
    Liste *l = initialiser();
    if(!l){
        printf("%s",MSG);
        exit(-1);
    }
    assert(longueur(l) == 0);
    Info a = 0;
    if (insererEnTete(l, &a) == OK) {
        assert(longueur(l) == 1);
    }else{
        NETTOIE(l);
        exit(-1);
    }
    supprimerEnTete(l, &a);
    assert(longueur(l) == 0);
    assert(supprimerEnTete(l,&a) == LISTE_VIDE);
    assert(estVide(l));

    if (insererEnQueue(l, &a) == OK) {
        assert(longueur(l) == 1);
    }else{
        NETTOIE(l);
        exit(-1);
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
        if(insererEnTete(l, &a) != OK){
            NETTOIE(l);
            exit(-1);
        }
        assert(longueur(l) == n + 1);
        ++n;
    }
    vider(l, 0);
    free(l);
}

void test_vider() {
    Liste *l = initialiser();
    if(!l){
        printf("%s",MSG);
        exit(-1);
    }
    int n = DIX;
    while (n--) {
        if(insererEnTete(l, &n) != OK){
            NETTOIE(l);
            exit(-1);
        }
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
    if(!l){
        printf("%s",MSG);
        exit(-1);
    }
    Liste *ll = initialiser();
    if(!ll){
        printf("%s",MSG);
        NETTOIE(l);
        exit(-1);
    }
    Info a = 0;
    assert(sontEgales(l, ll)); //equal is commutative
    assert(sontEgales(ll, l));

    if(insererEnTete(l, &a) != OK){
        printf("%s",MSG);
        NETTOIE(l);
        NETTOIE(ll);
        exit(-1);
    }
    if(insererEnTete(ll, &a) != OK){
        printf("%s",MSG);
        NETTOIE(l);
        NETTOIE(ll);
        exit(-1);
    }
    assert(sontEgales(ll, l));
    assert(sontEgales(l, ll));
    supprimerEnTete(l, &a);
    assert(!sontEgales(l, ll));
    assert(!sontEgales(ll, l));
    supprimerEnTete(ll, &a);
    if(generate(ll, 10)){
        NETTOIE(l);
        NETTOIE(ll);
        exit(-1);
    }
    if(generate(l, 10)){
        NETTOIE(l);
        NETTOIE(ll);
        exit(-1);
    }
    supprimerEnTete(l, &a);
    assert(!sontEgales(l, ll));//tete is differente
    vider(l, 0);
    vider(ll, 0);
    free(ll);
    ll = l;
    assert(sontEgales(ll, l));
    if(insererEnTete(l, &a) != OK){
        NETTOIE(l); //ll pointe sur l, on ne le nettoie pas sinon on a double free
        exit(-1);
    }
    assert(sontEgales(ll, l));
    vider(l, 0);
    free(l);
}

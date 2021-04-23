/*
-----------------------------------------------------------------------------------
Nom du fichier : main.c
Nom du labo    : ASD-L2-Recursivite
Auteur(s)      : Patrick Furrer, Tobie Praz, Damiano Mondaini, Ivan Vecerina
Date creation  : 08.03.2021
But            : le but du programme est de résoudre le "Scramble Squares" puzzle 3x3.
Description    : On devait afficher toutes les solutions du puzzle, ainsi que le nombre de tentatives à
                 placer une pièce et d'appels de la fonction récursive.

Remarque(s)    : Voici la solution complète que nous avons utilisé. Le main_alt.cpp contient une alternative
                 sur laquelle nous avons aussi travaillé en parallèle. Nous avons choisi celle-ci
                 pour sa manière un peu plus simple de visualiser les pièces et leur placement.

Compilateur    : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------
*/


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

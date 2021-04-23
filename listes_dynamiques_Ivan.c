#include <stdio.h>
#include "listes_dynamiques.h"


// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste qui
// vérifient le critère passé en second paramètre.
// Exemple: on souhaite supprimer de la liste tous les éléments dont la position est
// impaire et pour lesquels info est compris dans un certain intervalle de valeurs
void supprimerSelonCritere(Liste* liste,
                           bool (*critere)(size_t position, const Info* info));
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Supprime, en restituant la mémoire allouée, tous les éléments de la liste
// à partir de la position position
// NB Vider à partir de la position 0 signifie vider toute la liste.
void vider(Liste* liste, size_t position){
    for (size_t i = liste-) {

    }
}
// ------------------------------------------------------------------------------

// ------------------------------------------------------------------------------
// Renvoie true si liste1 et liste2 sont égales (au sens mêmes infos et infos
// apparaissant dans le même ordre), false sinon.
// NB 2 listes vides sont considérées comme égales.
bool sontEgales(const Liste* liste1, const Liste* liste2){
    if (longueur(liste1) != longueur(liste2))
            return false;

    Element* e1 = NULL;
    Element* e2 = NULL;

    e1 = liste1->tete;
    e2 = liste2->tete;

    while(e1 && e2) {
        if (e1->info != e2->info)
            return false;

        e1 = e1->suivant;
        e2 = e2->suivant;
    }
    return true;



}
// ------------------------------------------------------------------------------
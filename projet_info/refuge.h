#ifndef REFUGE_H
#define REFUGE_H

#include "util.h"

// Structure de l'animal
typedef struct {
  int id;
  char nom[TAILLE_MAX];
  char espece[TAILLE_MAX];
  int annee;
  float poids;
  char commentaire[TAILLE_MAX];
} Animal;

// Fonctions principales du refuge
void ajouter_animal(Animal t_animaux[], int *nb_animaux);
void afficher_animaux(Animal t_animaux[], int nb_animaux);
void rechercher_animal(Animal t_animaux[], int nb_animaux);
void adopter_animal(Animal t_animaux[], int *nb_animaux);
void calculer_charge_nettoyage(Animal t_animaux[], int nb_animaux);

// Fonctions de gestion de fichiers
int fic_to_struct(Animal t_animaux[]);
void ajt_animal_fic(Animal t_animaux[], int nb_animaux);

#endif // REFUGE_H

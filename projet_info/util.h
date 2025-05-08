#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAILLE_MAX 150
#define MAX_ANIMAL 50
#define MAX_CHAINE 256
#define YEAR 2025

// Fonctions de vérification
void verif_scanf_entier();
void verif_scanf_flottant();
int est_entier(char *caract);
float est_flottant(char *caract);
int est_entier_choix(int min, int max);
float est_flottant_choix(int min, int max);

// Fonctions de manipulation de chaînes
void en_minuscule(char *chaine);
int en_lettre(char *chaine);
void lettre_minuscule(char *caract, char *chaine);
int verif_taille_char(char *chaine);

// Fonctions diverses
int alea_id();
void convertir_secondes(int t_secondes);
void clean_stdin();
int est_entier_annee(char *caract);
#endif // UTIL_H

#include "util.h"
#include "refuge.h"

// Vérifie et nettoie le buffer après un scanf d'entier
void verif_scanf_entier() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Vérifie et nettoie le buffer après un scanf de flottant
void verif_scanf_flottant() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Vérifie si une chaîne est composée uniquement de lettres
int en_lettre(char *chaine) {
  int i = 0;
  while (*(chaine + i) != '\0') {
    if (!isalpha(*(chaine + i)) && *(chaine + i) != '-' &&
        *(chaine + i) != ' ' && *(chaine + i) != '_') {
      return 0;
    }
    i++;
  }
  return 1;
}

// Convertit une chaîne en minuscules
void en_minuscule(char *chaine) {
  while (*chaine != '\0') {
    *chaine = tolower(*chaine);
    chaine++;
  }
}

// Lecture sécurisée d'une chaîne en minuscules
void lettre_minuscule(char *caract, char *chaine) {
  int taille;
  do {
    printf("Donner votre %s: ", caract);

    if (fgets(chaine, MAX_CHAINE, stdin) != NULL) {
      taille = strlen(chaine);
      if (taille > 0 && chaine[taille - 1] == '\n') {
        chaine[taille - 1] = '\0'; // Retirer le saut de ligne
      }
      if (strlen(chaine) == 0) {
        printf("Erreur: saisie vide, veuillez réessayer.\n");
      }
    }
  } while (!en_lettre(chaine) || strlen(chaine) == 0);
  en_minuscule(chaine);
}

int est_entier(char *caract) {
  int nb;
  printf("Donner son %s: ", caract);
  if (scanf("%d", &nb) != 1) {
    printf("Erreur: saisie invalide pour un entier.\n");
    clean_stdin(); // Nettoyer après scanf
    return -1;
  }
  clean_stdin(); // Nettoyer après une saisie correcte aussi
  return nb;
}

int est_entier_choix(int min, int max) {
  int choix;
  do {
    choix = est_entier("choix");
    if (choix < min || choix > max) {
      printf("Choix invalide. Veuillez entrer une valeur entre %d et %d.\n",
             min, max);
    }
  } while (choix < min || choix > max);
  return choix;
}

float est_flottant(char *caract) {
  float nb;
  printf("Donner son %s: ", caract);
  if (scanf("%f", &nb) != 1) {
    printf("Erreur: saisie invalide pour un nombre flottant.\n");
    verif_scanf_flottant();
    return -1;
  }
  return nb;
}

// Vérifie si l'entrée est un entier compris entre min et max

// Vérifie si l'entrée est un flottant compris entre min et max
float est_flottant_choix(int min, int max) {
  float choix;
  do {
    choix = est_flottant("choix");
    if (choix < min || choix > max) {
      printf("Choix invalide. Veuillez entrer une valeur entre %d et %d.\n",
             min, max);
    }
  } while (choix < min || choix > max);
  return choix;
}

// Vérifie si la longueur de la chaîne est suffisante
int verif_taille_char(char *chaine) { return (strlen(chaine) > 2); }

int alea_id(Animal t_animaux[], int nb_animaux) {
  int id;
  int unique;
  do {
    id = 1 + rand() % 50;
    unique = 1;
    for (int i = 0; i < nb_animaux; i++) {
      if (t_animaux[i].id == id) {
        unique = 0;
        break;
      }
    }
  } while (!unique);
  return id;
}
// Convertit des secondes en heures, minutes et secondes
void convertir_secondes(int t_secondes) {
  int heures = t_secondes / 3600;
  int minutes = (t_secondes % 3600) / 60;
  int secondes = t_secondes % 60;
  printf("%d heure(s), %d minute(s), %d seconde(s)\n", heures, minutes,
         secondes);
}

// Fonction pour nettoyer le buffer stdin après un scanf
void clean_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int est_entier_annee(char *caract) {
  int nb;
  do {
    printf("Donner son %s: ", caract);
    if (scanf("%d", &nb) != 1) {
      printf("Erreur: saisie invalide pour un entier.\n");
      clean_stdin();
      continue;
    }
    clean_stdin();
    if (nb <= 0 || nb > YEAR) {
      printf("Erreur: l'année doit être comprise entre 1 et %d.\n", YEAR);
    }
  } while (nb <= 0 || nb > YEAR);
  return nb;
}

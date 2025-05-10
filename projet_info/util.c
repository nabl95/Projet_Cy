#include "util.h"
#include "refuge.h"

// Vérifie et nettoie le buffer apres une saisie
void clean_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
    
}

// Vérifie si une chaîne est composée uniquement de lettres
int en_lettre(char *chaine) {
  int i = 0;
  while (*(chaine + i) != '\0') {
    if (!isalpha(*(chaine + i)) && *(chaine + i) != '-' && *(chaine + i) != ' ' && *(chaine + i) != '_') {
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
// Lecture securisee d'une chaine en minuscules
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
  en_minuscule(chaine); // placement important
}
// verifie que l'entree est bien un int
int est_entier(char *caract) {
  char buffer[MAX_CHAINE];
  int nb;
  int flag;

  do {
    flag = 1;
    printf("Donner son %s: ", caract);

    if (fgets(buffer, MAX_CHAINE, stdin) != NULL) {
      buffer[strcspn(buffer, "\n")] = '\0';
      for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ',' || (isdigit(buffer[i]) == 0)) {
          flag = 0;
          break;
        }
      }

      if (flag) {
        nb = atoi(buffer);
        return nb;
      }
    } else {
      printf("Erreur de saisie\n");
      clean_stdin();
    }
  } while (!flag);
  return -1; // car return dans le if juste pour eviter un bug on n'arrivera jamais au -1 sauf erreur
}
// verifie que l'entree est un int compris entre deux valeurs
int est_entier_choix(int min, int max) {
  int choix;
  do {
    choix = est_entier("choix");
    if (choix < min || choix > max) {
      printf("Choix invalide. Veuillez entrer une valeur entre %d et %d.\n", min, max);
    }
  } while (choix < min || choix > max);
  return choix;
}
// verifie que l'entree est bien un float
float est_flottant(char *caract) {
  char buffer[MAX_CHAINE];
  float nb;
  int flag;

  do {
    flag = 1;
    printf("Donner son %s: ", caract);

    if (fgets(buffer, MAX_CHAINE, stdin) != NULL) {
      for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ',' || buffer[i] == '?' || buffer[i] == ';' || buffer[i] == '!' || buffer[i] == '/' || buffer[i] == ':') {
          flag = 0;
          break;
        }
      }

      if (flag) {
        nb = atof(buffer);
        return nb;
      }
    } else {
      printf("Erreur de saisie\n");
      clean_stdin();
    }
  } while (!flag);
  return -1; // car return dans le if juste pour eviter un bug on n'arrivera jamais au -1 sauf erreur 
}

// Vérifie si l'entrée est un flottant compris entre min et max
float est_flottant_choix(int min, int max) {
  float choix;
  do {
    choix = est_flottant("choix");
    if (choix < min || choix > max) {
      printf("Choix invalide. Veuillez entrer une valeur entre %d et %d.\n",min, max);
    }
  } while (choix < min || choix > max);
  return choix;
}

// Vérifie si la longueur de la chaîne est suffisante
int verif_taille_char(char *chaine) { return (strlen(chaine) > 2); }

//creation / verification d'une valeur unique pour notre id
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

// verifie que l'entree est une annee possible
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
    if (nb <= (YEAR - 70) || nb > YEAR) {
      printf("Erreur: l'année doit être comprise entre 1 et %d.\n", YEAR);
    }
  } while (nb <= (YEAR - 70) || nb > YEAR);
  return nb;
}

#include "refuge.h"

// fonction de depart pour passer tous les infos du fichier dans une structure animal
int fic_to_struct(Animal t_animaux[]) {
  int nb_animaux = 0;
  FILE *fichier = fopen("animal.txt", "r");
  if (fichier == NULL) {
    printf("Erreur d'ouverture du fichier");
    return 0;
  }

  if (fscanf(fichier, "%d\n", &nb_animaux) !=1)// Si ce n'est pas un chiffre/nombre
  { 
    printf("Erreur de lecture du nombre d'animaux.\n");
    fclose(fichier);
    return 0;
  }

  for (int i = 0; i < nb_animaux; i++) { //^\n lit toute la ligne meme les espaces != de %s
    int result = fscanf(fichier, "%d %s %s %d %f %[^\n]", &t_animaux[i].id, t_animaux[i].nom,t_animaux[i].espece, &t_animaux[i].annee, &t_animaux[i].poids,t_animaux[i].commentaire); 
    if (result != 6) {
      printf("Erreur de lecture pour l'animal %d.\n", i + 1);
      fclose(fichier);
      return nb_animaux;
    }
  }

  fclose(fichier);
  printf("Animaux chargés depuis le fichier animal.txt\n");
  return nb_animaux;
}

// Fonction pour ajouter les animaux dans le fichier animal.txt
void ajt_animal_fic(Animal t_animaux[], int nb_animaux) {
  FILE *fichier = fopen("animal.txt", "w"); // Mode écriture pour écraser l'ancien contenu
  if (fichier == NULL) {
    printf("Erreur d'ouverture du fichier");
    return;
  }

  // Écrire le nombre d'animaux en première ligne
  fprintf(fichier, "%d\n", nb_animaux);

  // Parcourir les animaux et les écrire dans le fichier
  for (int i = 0; i < nb_animaux; i++) {
    if (strlen(t_animaux[i].commentaire) == 0) {
      strcpy(t_animaux[i].commentaire, "Aucun");
    }
    fprintf(fichier, "%d %s %s %d %.2f %s\n", t_animaux[i].id, t_animaux[i].nom,t_animaux[i].espece, t_animaux[i].annee, t_animaux[i].poids,t_animaux[i].commentaire);
  }

  fclose(fichier);
  printf("Animaux enregistrés dans le fichier animal.txt\n");
}

// Ajouter un animal dans le tableau de structure animal
void ajouter_animal(Animal t_animaux[], int *nb_animaux) {

  int tl;
  Animal a;
  if (*nb_animaux >= MAX_ANIMAL) {
    printf("Le refuge est plein, impossible d'ajouter un nouvel animal.\n");
    return;
  }

  lettre_minuscule("nom", a.nom);
  lettre_minuscule("espece", a.espece);
  a.annee = est_entier_annee("année de naissance");
  a.poids = est_flottant("poids");
  a.id = alea_id(t_animaux, *nb_animaux); // Génération d'un ID unique

  // Gestion du commentaire
  printf("Voulez-vous ajouter un commentaire ? (0 = Oui, 1 = Non) : ");
  int choix = est_entier_choix(0, 1);
  if (choix == 0) {
    printf("Entrez un commentaire (plusieurs mots possibles) : ");
    fgets(a.commentaire, TAILLE_MAX, stdin);
    tl = strlen(a.commentaire);
    if (tl > 0 && a.commentaire[tl - 1] == '\n') { //remplace le \n par \0 pour eviter les erreur par la suite
      a.commentaire[tl - 1] = '\0';
    }
    if (strlen(a.commentaire) == 0) { // si il decide de mettre un commentaire mais n'ecrit rien
      strcpy(a.commentaire, "Aucun");
    }
  } else {
    strcpy(a.commentaire, "Aucun");
  }

  t_animaux[(*nb_animaux)++] = a;
  printf("Animal ajouté avec succès !\n");
}

// Afficher tous les animaux
void afficher_animaux(Animal t_animaux[], int nb_animaux) {
  if (nb_animaux == 0) {
    printf("Aucun animal dans le refuge.\n");
    return;
  }

  for (int i = 0; i < nb_animaux; i++) {
    printf("ID: %d\n", t_animaux[i].id);
    printf("Nom: %s\n", t_animaux[i].nom);
    printf("Espèce: %s\n", t_animaux[i].espece);
    printf("Année de naissance: %d\n", t_animaux[i].annee);
    printf("Poids: %.2f kg\n", t_animaux[i].poids);
    if (strcmp(t_animaux[i].commentaire, "Aucun") == 0) {
      printf("Commentaire: Pas de commentaire\n");
    } else {
      printf("Commentaire: %s\n", t_animaux[i].commentaire);
    }

    printf("-------------------------------\n");
  }
}

// affiche un animal en particulier
void afficher_animal(Animal a) {
  printf("\n-------Animal trouvé -------\n");
  printf("ID: %d\n", a.id);
  printf("Nom: %s\n", a.nom);
  printf("Espèce: %s\n", a.espece);
  printf("Année de naissance: %d\n", a.annee);
  printf("Poids: %.2f kg\n", a.poids);
  printf("Commentaire: %s\n", a.commentaire);
}

// Rechercher un animal avec different critere
void rechercher_animal(Animal t_animaux[], int nb_animaux) {
  char nom[TAILLE_MAX], espece[TAILLE_MAX];
  Animal tab_nom[MAX_ANIMAL];
  int nb_tab_nom = 0, choix;

  lettre_minuscule("Prénom ", nom);

  // Étape 1 : recherche par nom
  for (int i = 0; i < nb_animaux; i++) {
    if (strcmp(t_animaux[i].nom, nom) == 0) {
      tab_nom[nb_tab_nom++] = t_animaux[i];
    }
  }

  if (nb_tab_nom == 0) {
    printf("Aucun animal trouvé avec ce nom.\n");
    return;
  }

  // Affichage si un seul meme nom
  if (nb_tab_nom == 1) {
    printf("Animal trouvé :\n");
    afficher_animal(tab_nom[0]);
    return;
  }

  // Étape 2 : filtrer par espece si plusieurs meme nom
  lettre_minuscule("Espece ", espece);
  Animal tab_espece[MAX_ANIMAL];
  int nb_tab_espece = 0;

  for (int i = 0; i < nb_tab_nom; i++) {
    if (strcmp(tab_nom[i].espece, espece) == 0) {
      tab_espece[nb_tab_espece++] = tab_nom[i];
    }
  }

  if (nb_tab_espece == 0) {
    printf("Aucun animal trouvé avec ce nom et cette espèce.\n");
    return;
  }

  // Étape 3 : filtrer par age si plusieurs resultats
  if (nb_tab_espece > 1) {
    printf("Quel type d'âge recherchez-vous ?\n");
    printf("0 = jeune (<2 ans), 1 = adulte (2-10 ans), 2 = senior (>10 ans)\n");
    choix = est_entier("Votre choix");

    Animal tab_age[MAX_ANIMAL];
    int nb_tab_age = 0;

    for (int i = 0; i < nb_tab_espece; i++) {
      int age = YEAR - tab_espece[i].annee; // 1µ

      if ((choix == 0 && age < 2) || (choix == 1 && age >= 2 && age <= 10) || (choix == 2 && age > 10)) {
        tab_age[nb_tab_age++] = tab_espece[i];
      }
    }

    if (nb_tab_age == 0) {
      printf("Aucun animal correspondant à ce critère d'âge.\n");
    } else {
      for (int i = 0; i < nb_tab_age; i++) {
        afficher_animal(tab_age[i]);
      }
    }
  } else {
    afficher_animal(tab_espece[0]);
  }
}

// Adopter un animal
void adopter_animal(Animal t_animaux[], int *nb_animaux) {
  int id, choix, find = 0, z = 0, flag;
  Animal temp_animaux[MAX_ANIMAL];

  do {
    printf("\n");
    afficher_animaux(t_animaux, *nb_animaux);

    printf("\n--- Adopter un animal ---\n");
    id = est_entier("id ");
    for (int i = 0; i < *nb_animaux; i++) {

      if (t_animaux[i].id == id) {
        find = 1;
        printf("Tres bon choix !\n Vous avez choisis %s\n", t_animaux[i].nom);
        printf("Confirmez vous l'adoption  0=oui     1=Non\n");
        choix = est_entier_choix(0, 1); // 0=oui     1=Non
        if (choix == 0) {
          printf("Felicitations %s est a vous!\n Prenez bien soin de lui \n",
                 t_animaux[i].nom);
        } else {
          printf("Adoption annule\n");
          temp_animaux[z] = t_animaux[i]; // important car on ne rentrera pas dans le 2eme else si on decide de na pas adopter finalement
          z++;
        }
      } else {
        temp_animaux[z] = t_animaux[i];
        z++;
      }
    }

    if (!find) {
      printf("Cet animal n'existe pas\n");
      return;
    }

    for (int i = 0; i < z; i++) // on copie le tableau temp dans le tableu de base
    {
      t_animaux[i] = temp_animaux[i];
    }
    *nb_animaux = z;

    ajt_animal_fic(t_animaux, *nb_animaux);
    printf("Adopter un autre animal ? 0= oui  1= Non\n");
    flag = est_entier_choix(0, 1); // 0= oui  1= Non
  } while (flag == 0);
}

// Calcul de la charge de nettoyage
void calculer_charge_nettoyage(Animal t_animaux[], int nb_animaux) {
  int charge_tr, quotidien = 0, hebdo = 0, total_minute = 0;
  printf("\n========= CHARGE DE NETTOYAGE HEBDOMADAIRE =========\n");

  for (int i = 0; i < nb_animaux; i++) {
    quotidien = 0;
    hebdo = 0;
    if (strcmp(t_animaux[i].espece, "hamster") == 0 ||
        strcmp(t_animaux[i].espece, "chat") == 0) {
      quotidien = 10;
      hebdo = 20;
    } else if (strcmp(t_animaux[i].espece, "autruche") == 0) {
      quotidien = 20;
      hebdo = 45;
    } else if (strcmp(t_animaux[i].espece, "chien") == 0) {
      quotidien = 5;
      hebdo = 20;
    }

    else {
      quotidien = 2;
      hebdo = 0;
    }
    charge_tr = (quotidien * 7) + hebdo; // charge par animal
    total_minute += charge_tr;           // incrementation du temps total
    printf("%-12s (%-8s) : %2d min/jour + %2d min/sem = %3d min/sem\n",t_animaux[i].nom, t_animaux[i].espece, quotidien, hebdo, charge_tr);
  }
  printf("-----------------------------------------------------\n");
  printf(" Temps total de nettoyage hebdomadaire : %d heures et %d minutes\n",total_minute / 60, total_minute % 60);
}
void nb_par_espece_dec(Animal t_animaux[], int nb_animaux) {
  if (nb_animaux == 0) {
    printf("Il n'y a pas d'animaux\n");
    return;
  }

  typedef struct {
    char espece[TAILLE_MAX];
    int cpt;
  } Nb_espece;

  Nb_espece tab_espece[MAX_ANIMAL];
  int nb = 0;

  // Comptage des espece
  for (int i = 0; i < nb_animaux; i++) {
    int found = 0;

    // Vérifier si l'espece est deja dans le tableau
    for (int j = 0; j < nb; j++) {
      if (strcmp(tab_espece[j].espece, t_animaux[i].espece) == 0) {
        tab_espece[j].cpt++; // Augmenter le compteur si trouve
        found = 1;
        break;
      }
    }

    // Si l'espece n'est pas encore enregistree, on l'ajoute
    if (!found) {
      strcpy(tab_espece[nb].espece, t_animaux[i].espece);
      tab_espece[nb].cpt = 1;
      nb++;
    }
  }

  // Tri par ordre decroissant du nombre d'animaux
  for (int i = 0; i < nb - 1; i++) {
    for (int j = i + 1; j < nb; j++) {
      if (tab_espece[j].cpt > tab_espece[i].cpt) {
        Nb_espece temp = tab_espece[i];
        tab_espece[i] = tab_espece[j];
        tab_espece[j] = temp;
      }
    }
  }

  // Affichage des resultats
  printf("\n=== Nombre d'animaux par espèce (ordre décroissant) ===\n");
  for (int i = 0; i < nb; i++) {
    printf("Espèce : %s - %d\n", tab_espece[i].espece, tab_espece[i].cpt);
  }
}

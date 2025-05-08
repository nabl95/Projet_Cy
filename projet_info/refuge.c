#include "refuge.h"

int fic_to_struct(Animal t_animaux[]) {
  int nb_animaux = 0;
  FILE *fichier = fopen("animal.txt", "r");
  if (fichier == NULL) {
    perror("Erreur d'ouverture du fichier");
    return 0;
  }

  if (fscanf(fichier, "%d\n", &nb_animaux) != 1) {
    printf("Erreur de lecture du nombre d'animaux.\n");
    fclose(fichier);
    return 0;
  }

  for (int i = 0; i < nb_animaux; i++) {
    int result = fscanf(
        fichier, "%d %s %s %d %f %[^\n]", &t_animaux[i].id, t_animaux[i].nom,
        t_animaux[i].espece, &t_animaux[i].annee, &t_animaux[i].poids,
        t_animaux[i].commentaire); //^\n evite de regarder si commentaire pas la
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
  FILE *fichier =
      fopen("animal.txt", "w"); // Mode écriture pour écraser l'ancien contenu
  if (fichier == NULL) {
    perror("Erreur d'ouverture du fichier");
    return;
  }

  // Écrire le nombre d'animaux en première ligne
  fprintf(fichier, "%d\n", nb_animaux);

  // Parcourir les animaux et les écrire dans le fichier
  for (int i = 0; i < nb_animaux; i++) {
    if (strlen(t_animaux[i].commentaire) == 0) {
      strcpy(t_animaux[i].commentaire, "Aucun");
    }
    fprintf(fichier, "%d %s %s %d %.2f %s\n", t_animaux[i].id, t_animaux[i].nom,
            t_animaux[i].espece, t_animaux[i].annee, t_animaux[i].poids,
            t_animaux[i].commentaire);
  }

  fclose(fichier);
  printf("Animaux enregistrés dans le fichier animal.txt\n");
}

// Ajouter un animal
void ajouter_animal(Animal t_animaux[], int *nb_animaux) {
  if (*nb_animaux >= MAX_ANIMAL) {
    printf("Le refuge est plein, impossible d'ajouter un nouvel animal.\n");
    return;
  }

  Animal a;
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
    size_t len = strlen(a.commentaire);
    if (len > 0 && a.commentaire[len - 1] == '\n') { //?
      a.commentaire[len - 1] = '\0';
    }
    if (strlen(a.commentaire) ==
        0) { // si il decide de mettre un comentaire mais n ecrit rien
      strcpy(a.commentaire, "Aucun");
    }
  } else {
    strcpy(a.commentaire, "Aucun"); //?
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

// Rechercher un animal par son nom
void rechercher_animal(Animal t_animaux[], int nb_animaux) {
  char nom[TAILLE_MAX];
  int trouve = 0;
  lettre_minuscule("nom de l'animal à rechercher", nom);

  for (int i = 0; i < nb_animaux; i++) {
    if (strcmp(t_animaux[i].nom, nom) == 0) {
      printf("Animal trouvé:\n");
      printf("ID: %d, Nom: %s, Espèce: %s, Année: %d, Poids: %.2f kg, "
             "Commentaire: %s\n",
             t_animaux[i].id, t_animaux[i].nom, t_animaux[i].espece,
             t_animaux[i].annee, t_animaux[i].poids, t_animaux[i].commentaire);
      trouve = 1;
    }
  }
  if (!trouve) {
    printf("Aucun animal avec le nom '%s' trouvé.\n", nom);
  }
}

// Adopter un animal
void adopter_animal(Animal t_animaux[], int *nb_animaux) {
  int id = est_entier("ID de l'animal à adopter");

  for (int i = 0; i < *nb_animaux; i++) {
    if (t_animaux[i].id == id) {
      printf("Vous avez adopté l'animal %s (ID: %d)\n", t_animaux[i].nom,
             t_animaux[i].id);
      for (int j = i; j < *nb_animaux - 1; j++) {
        t_animaux[j] = t_animaux[j + 1];
      }
      (*nb_animaux)--;
      return;
    }
  }
  printf("Animal avec ID %d non trouvé.\n", id);
}

// Calcul de la charge de nettoyage
void calculer_charge_nettoyage(Animal t_animaux[], int nb_animaux) {
  int total_minutes = 0;

  for (int i = 0; i < nb_animaux; i++) {
    int temps_journalier = 0;
    int temps_hebdomadaire = 0;

    if (strcmp(t_animaux[i].espece, "chien") == 0) {
      // Chien : 5 minutes par jour + 20 minutes par semaine
      temps_journalier = 5;
      temps_hebdomadaire = 20;
    } else if (strcmp(t_animaux[i].espece, "chat") == 0 ||
               strcmp(t_animaux[i].espece, "hamster") == 0) {
      // Chat ou Hamster : 10 minutes par jour + 20 minutes par semaine
      temps_journalier = 10;
      temps_hebdomadaire = 20;
    } else if (strcmp(t_animaux[i].espece, "autruche") == 0) {
      // Autruche : 20 minutes par jour + 45 minutes par semaine
      temps_journalier = 20;
      temps_hebdomadaire = 45;
    } else {
      // Cas d'une cage vide ou d'un animal non répertorié
      temps_journalier = 2;   // Dépoussiérage
      temps_hebdomadaire = 0; // Pas de nettoyage supplémentaire
    }

    int temps_total = (temps_journalier * 7) + temps_hebdomadaire;
    total_minutes += temps_total;

    printf("Animal: %s, Espèce: %s, Temps de nettoyage: %d min/sem\n",
           t_animaux[i].nom, t_animaux[i].espece, temps_total);
  }

  int heures = total_minutes / 60;
  int minutes = total_minutes % 60;
  printf(
      "Charge de nettoyage totale: %d heure(s) et %d minute(s) par semaine\n",
      heures, minutes);
}

#include "refuge.h"

void afficher_menu() {
  printf("\n=== MENU DU REFUGE ===\n");
  printf("1. Ajouter un animal\n");
  printf("2. Afficher les animaux\n");
  printf("3. Rechercher un animal\n");
  printf("4. Adopter un animal\n");
  printf("5. Calculer la charge de nettoyage\n");
  printf("0. Quitter\n");
  printf("Choisissez une option : ");
}

int main() {
  Animal t_animaux[MAX_ANIMAL];
  int nb_animaux;

  // Charger les animaux depuis le fichier au démarrage
  nb_animaux = fic_to_struct(t_animaux);

  int choix;
  srand(time(NULL));

  do {
    afficher_menu();
    choix = est_entier("choix");
    switch (choix) {
    case 1:
      ajouter_animal(t_animaux, &nb_animaux);
      ajt_animal_fic(t_animaux, nb_animaux);
      break;

    case 2:
      afficher_animaux(t_animaux, nb_animaux);
      break;

    case 3:
      rechercher_animal(t_animaux, nb_animaux);
      break;

    case 4:
      adopter_animal(t_animaux, &nb_animaux);
      ajt_animal_fic(t_animaux, nb_animaux);
      break;

    case 5:
      calculer_charge_nettoyage(t_animaux, nb_animaux);
      break;

    case 0:
      printf("Données enregistrées. Au revoir !\n");
      break;

    default:
      printf("Option invalide. Veuillez réessayer.\n");
    }
  } while (choix != 0);

  return 0;
}

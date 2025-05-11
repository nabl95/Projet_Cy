#include "refuge.h"

void afficher_menu() {
  printf("\n");
  printf("============================================================\n");
  printf("                MENU PRINCIPAL - LE REFUGE ANIMALIER          \n");
  printf("============================================================\n\n");
  printf("    1. AFFICHER TOUS LES ANIMAUX\n");
  printf("       -> Vous etre peut-etre a la recherche de votre prochaine "
         "animal\n\tOn vous propose de les voir virtuellement\n\n");
  printf("    2. AJOUTER UN NOUVEL ANIMAL\n");
  printf(
      "       -> Vous venez de trouver un animal ? Ajoute le chez nous.\n\n");
  printf("    3. RECHERCHER UN ANIMAL\n");
  printf("       -> Vous avez perdu votre animal ou souhaitez vous "
         "renseigner sur un animal de notre refuge ?\n\tRecherche le !\n\n");
  printf("    4. ADOPTER UN ANIMAL\n");
  printf("       -> Vous avez eu un coup de coeur ? Passer a la vitesse "
         "superieur en l'adoptant\n\n");
  printf("    5. VOIR LA CHARGE DE NETTOYAGE\n");
  printf("       -> Un animal vous interrese et vous souhaitez vous "
         "renseigner sur son temps de netoyage ?\n\n");
  printf("    6. INVENTAIRE PAR ESPECE\n");
  printf("       -> AFFICHAGE DES ANIMAUX PAR RACE\n\n");
  printf("    0. QUITTER\n");
  printf("       -> Ferme le programme.\n\n");
  printf("============================================================\n");
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
      afficher_animaux(t_animaux, nb_animaux);
      break;

    case 2:
      ajouter_animal(t_animaux, &nb_animaux);
      ajt_animal_fic(t_animaux, nb_animaux);
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

    case 6:
      nb_par_espece_dec(t_animaux, nb_animaux);
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

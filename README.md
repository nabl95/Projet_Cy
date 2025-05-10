# Refuge Animalier (Projet ChenYl-Tech)

Une application console en C pour gérer un chenil :
- code final : projet info 
- ajout, recherche, modification et suppression de fiches animales  
- calcul de la charge de nettoyage  
- stockage persistant dans un fichier `animal.txt`

---
## Descriptif fichier
main.c
Point d’entrée principal du programme.
Gère l’affichage du menu principal et la boucle d’exécution utilisateur.

### refuge.c
Implémente les fonctions principales de gestion des animaux :
ajout, suppression, recherche, modification, affichage et sauvegarde.

### refuge.h
Contient les définitions des structures (ex : Animal)
et les prototypes des fonctions utilisées dans refuge.c.

### util.c
Contient les fonctions utilitaires :
saisie sécurisée, mise en minuscules, validation de types, nettoyage de buffer, etc.

### util.h
Déclarations des fonctions utilitaires partagées dans tout le projet.

### Makefile
Fichier d’automatisation de la compilation.
Permet de générer l’exécutable refuge à partir des fichiers .c.

### animal.txt
Fichier texte contenant la liste des animaux enregistrés.
La premiere ligne contient le nombre total d'animaux du refuge
Chaque ligne représente un animal avec ses attributs, séparés par des espace
exemple : 6 titi chat 2022 3.90 timide


## Compilation & exécution

1. Ouvrez un terminal à la racine du projet.  
2. Lancez la commande :
   ```bash
   make
   ```
3. executer le programme : 
    ```bash 
    ./refuge
    ```
## trinome :

Nabil Touat    
Zinedine Zouini    
Ikram-fatima azzi



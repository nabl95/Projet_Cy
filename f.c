#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "ctype.h"
#define TAILLE_MAX 150
#define MAX_ANIMAL 50
#define YEAR    2025
typedef struct{

    char espece[60];
    int nombre;
}Nb_espece;

typedef struct{
    int id;
    char nom[TAILLE_MAX];
    char espece[TAILLE_MAX];
    int annee;
    float poids;
    char commentaire[TAILLE_MAX];

}Animal;

void verif_scanf_entier()
{
    int c;
    while((c= getchar()) !='\n' && c!=EOF);// getchar lit char par char, donc la fct s art quand char =fin de ligne ou fin de fichier(EOF) si il n'y pas de saut de ligne
}
void verif_scanf_flottant()
{
    float c;
    while((c= getchar()) !='\n' && c!=EOF);

}
void en_minuscule(char *chaine)
{
    while(*chaine!='\0')
    {
        if(*chaine>='A' && *chaine<='Z')
        {
            *chaine+=32;
        }
        chaine++;
    }
}
int en_lettre(char * chaine)
{
    int i=0;
    while(*(chaine+i)!='\0')
    {
       if (!isalpha(*(chaine + i)) && *(chaine + i) != '-' && *(chaine + i) != ' ' && *(chaine+i) != '_')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

char * lettre_minuscule(char * caract)
{
    char *chaine;
    int taille;
    chaine=malloc(255*sizeof(char));
    do{
        printf("donner votre %s",caract);
        fgets(chaine,255,stdin);//on utlise sa car le scanf s art si il y a un espace
        taille = strlen(chaine);
        if (taille> 0 && chaine[taille- 1] == '\n') {//permet d enlever le '\n' si il existe
            chaine[taille- 1] = '\0';//explique ca 
        }
        en_lettre(chaine);
    } while(en_lettre(chaine)!=1);
    en_minuscule(chaine);
    return chaine;//free() ?
    
}
int est_entier(char *caract)
{
    int nb,verif_s;
    
    do{
        printf("Donner son %s\n",caract);
        verif_s=scanf("%d",&nb);
        if(verif_s !=1 )
        {
            printf("Erreur !!\n Rentrer un entier valide\n");
            verif_scanf_entier();
        }
    }while(verif_s!=1);
    return nb;
}
int est_entier_choix(int min,int max)
{
    int choix,verif_s;
    do{
        printf("Selectionner : \n %d : OUI\n %d : NON\n",min,max);
        verif_s=scanf("%d",&choix);
        if(verif_s !=1 )
        {
            printf("Erreur !!\n Rentrer un entier valide\n");
            verif_scanf_entier();
        }
        else if( choix != min && choix != max)// else if car sa peut etre un entier mais pas compris entre les deux valeur impose
        {
            printf("Choix poissible %d ou %d uniquement",min,max);
        }
    }while(verif_s != 1 || (choix != min && choix != max));
    return choix;
}
float est_flottant(char *caract)
{
    float nb;
    int verif_s;
    do{
        printf("Donner son %s\n",caract);
        verif_s=scanf("%f",&nb);
        if(verif_s !=1 )
        {
            printf("Erreur !!\n Rentrer un floattant valide\n");
            verif_scanf_flottant();
        }
    }while(verif_s!=1);
    return nb;
}
float est_flottant_choix(int min,int max)
{
   float choix;
   int verif_s;
    do{
        printf("Selectionner : \n %d : OUI\n %d : NON\n",min,max);
        verif_s=scanf("%f",&choix);
        if(verif_s !=1 )
        {
            printf("Erreur !!\n Rentrer un flottant valide\n");
            verif_scanf_flottant();
        }
        else if( choix != min && choix != max)// else if car sa peut etre un float mais pas compris entre les deux valeur impose
        {
            printf("Choix possible %d ou %d uniquement",min,max);
        }
    }while(verif_s != 1 || (choix != min && choix != max));
    return choix;
}
int alea_id()
{
    //genere un id aleatoire
    return 1+rand()%(50);
}
int id_unique(Animal t_animaux[],int *nb_animaux)
{
    //verifie et genere un id unique
    int unique;
    int id=alea_id();
    while(!unique)
    {
        unique=1;//on suppose au depart que c'est unique
        for(int i=0;i<*nb_animaux;i++)
        {
            if(t_animaux[i].id == id)
            {
                unique=0;//pas unique
                id=alea_id();//on lui donne une nouvelle valeur
                break;
            }
        }
    }
    return id;

}
int verif_taille_char(char *chaine)
{
    if(strlen(chaine)>2)
    {
        return 1;
    }
    else return 0;
}
void convertir_secondes(int t_secondes)
{
    int heures = t_secondes / 3600;
    int minutes = (t_secondes % 3600) / 60;
    int secondes = t_secondes % 60;

    printf("%d heure(s), %d minute(s), %d seconde(s)\n", heures, minutes, secondes);
}
void aff(Animal t_animaux[],int *nb_animaux)
{
    printf("\n--- Le Refuge ---\n");
    for(int i = 0; i < *nb_animaux; i++)
    {
        printf("ID : %d\n", t_animaux[i].id);
        printf("Nom : %s\n", t_animaux[i].nom);
        printf("Espece : %s\n", t_animaux[i].espece);
        printf("Annee de naissance : %d\n", t_animaux[i].annee);
        printf("Poids : %.2f kg\n", t_animaux[i].poids);

        if(verif_taille_char(t_animaux[i].commentaire))
        {
            printf("Commentaire : %s\n", t_animaux[i].commentaire);
        }

        printf("-----------------------------\n");
    }
}

int fic_to_struct(Animal tab_animaux[])
{//fonction de depart pour mettre tous les animaux du fichier dans la tabl struct
    char ligne[256],espece[256],nom[256],commentaire[256];
    int nb_animaux,n,id,annee,i=0;
    float poids;

    FILE *fic=fopen("animal.txt","r");
    if(fic == NULL)
    {
        printf("Erreur d'ouverture du fichierhhhh\n");
        exit(1);
    }
    if (fscanf(fic, "%d\n", &nb_animaux) != 1) {
        printf("❌ Erreur : première ligne invalide.\n");
        fclose(fic);
        exit(1);
    } 

    while (fgets(ligne, sizeof(ligne)-1, fic) != NULL && i<MAX_ANIMAL)
    {
        n = sscanf(ligne, "%d %s %s %d %f %s",&id, nom, espece, &annee, &poids, commentaire);

        if(n==5)
        {
            strcpy(tab_animaux[i].nom, nom);
            strcpy(tab_animaux[i].espece, espece);
            tab_animaux[i].annee = annee;
            tab_animaux[i].poids = poids;
            tab_animaux[i].id = id;
            i++;
        }
        if(n==6)
        {
        strcpy(tab_animaux[i].nom, nom);
            strcpy(tab_animaux[i].espece, espece);
            tab_animaux[i].annee = annee;
            tab_animaux[i].poids = poids;
            tab_animaux[i].id = id;
            strcpy(tab_animaux[i].commentaire, commentaire);
            i++;
        }
    }
    fclose(fic);
    return i;
}
void ajt_animal_strt(Animal t_animaux[],int *nb_animaux)
{ //permet d'ajouter un animal dans  le tab structure animal(Pas dans le fichier)

    Animal a;
    int verif_s;
    int choix_c;
    printf("\n--- Ajouter un nouvel animal ---\n");

    strcpy(a.nom,lettre_minuscule("nom "));
    strcpy(a.espece,lettre_minuscule("espece "));

    a.annee=est_entier("annee_de_naissance ");
    a.poids=est_flottant("poids ");
    a.id=id_unique(t_animaux,nb_animaux);
    choix_c=est_entier_choix(0,1);// 0=oui     1=Non
    if(choix_c == 0)
    {
        strcpy(a.commentaire,lettre_minuscule("commentaire "));
    }
    
    t_animaux[*nb_animaux] = a;
    (*nb_animaux)++;  // ou (*nb_animaux) ????
}
void ajt_animal_fic(Animal t_animaux[],int *nb_animaux)
{//permet d'ajouter tous les animaux dans le fichier

    FILE *fichier = fopen("animal.txt", "w");  // 
    if (fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    fprintf(fichier, "%d\n", nb_animaux);

    for(int i=0;i<*nb_animaux;i++)//attention si pas de commentaire a modifier
    {
        fprintf(fichier, "%d %s %s %d %.2f", t_animaux[i].id, t_animaux[i].nom, t_animaux[i].espece,t_animaux[i].annee, t_animaux[i].poids);
        if(verif_taille_char(t_animaux[i].commentaire))// fct qu verifie que la taille du commentaire >2 autrement dit qu'il y a bien un commentaire
        {
            fprintf(fichier, " %s\n",t_animaux[i].commentaire);
        }
    }
fclose(fichier);
}
void recherche_animal(Animal t_animaux[],int *nb_animaux)
{
    char nom[256],espece[256];
    int age,choix_a,find=0,flag;
    do{
        printf("\n--- RECHERCHER UN ANIMAL ---\n");
        strcpy(nom,lettre_minuscule("nom "));
        strcpy(espece,lettre_minuscule("espece "));
        choix_a=est_entier_choix(0,1);//0= age<2      1= age>10
    
        if(choix_a==0)
        {
            do{
                age=est_entier("age ");
                if(age < 0 || age > 2)
                {
                    printf("Rappel !!\n L'age >0 et <2\n");
                }
            }while(age< 0 || age >2);
        }
        if(choix_a==1)
        {
            do{
                age=est_entier("age ");
                if(age < 10)
                {
                    printf("Rappel !!\n L'age >10\n");
                }
            }while(age < 10);
        }
    
        for(int i=0;i<*nb_animaux;i++)//Recherche de l'animal dans le tableau
        {
            if(strcmp(t_animaux[i].nom,nom) == 0 && strcmp(t_animaux[i].espece,espece) == 0 && (YEAR - t_animaux[i].annee) == age)
            {
                printf("Super!\n Votre animal est au refuge\n");
                printf("%d %s %s %d %f",t_animaux[i].id ,t_animaux[i].nom,t_animaux[i].espece,t_animaux[i].annee,t_animaux[i].poids);
                if(verif_taille_char(t_animaux[i].commentaire))// fct qu verifie que la taille du commentaire >2 autrement dit qu'il y a bien un commentaire
                {
                    printf("%s\n",t_animaux[i].commentaire);
                }
                find=1;
            }
        }
        if(!find)
        {
            printf("OUPS !\n Votre animal n'est pas ici\n");
        }
        flag=est_entier_choix(0,1);// 0= oui  1= Non
    }while(flag == 0);
   
}

void adoption(Animal t_animaux[],int *nb_animaux)
{
    int id,choix,find,z=0;
    Animal temp_animaux[50];

    aff(t_animaux,nb_animaux);

    printf("\n--- Adopter un animal ---\n");
    id=est_entier("id ");
    for(int i=0;i<*nb_animaux;i++)
    {
        
        if(t_animaux[i].id == id)
        {
            find=1;
            printf("Très bon choix !\n Vous avez choissi %s\n",t_animaux[i].nom);
            printf("Confirmer vous l'adoption\n");
            choix=est_entier_choix(0,1);//0=oui     1=Non
            if(choix == 0)
            {
                printf("Felicitation %s est a vous!\n Prenez bien soin de lui \n",t_animaux[i].nom);
                continue;//Pas ajouter dans tabl temp
            }
            else{
                printf("Adoption annule\n");
            }
        }
        else{
            temp_animaux[z]=t_animaux[i];
            z++;
        }
    }

    if(!find){
        printf("Cette animal n'existe pas\n");
        return;
    }

    for(int i=0;i<z;i++)//on copie le tabl temp dans le tableu de base
    {
        t_animaux[i]=temp_animaux[i];
    }
    *nb_animaux=z;

    ajt_animal_fic(t_animaux,nb_animaux);
}

void day_clean(Animal t_animaux[],int *nb_animaux)
{
    
    int charge_tr,quotidien=0,hebdo=0,t_minute=0;
    printf("\n========= CHARGE DE NETTOYAGE HEBDOMADAIRE =========\n");
 
    for(int i=0;i<*nb_animaux;i++)
    {
        if(strcmp(t_animaux[i].espece,"hamster") == 0 ||  strcmp(t_animaux[i].espece, "chat") == 0)
        {
            quotidien =10;
            hebdo =20;
        }
        else if(strcmp(t_animaux[i].espece,"autruche"))
        {
            quotidien =20;
            hebdo =45;
        }
        else if(strcmp(t_animaux[i].espece,"chien"))
        {
            quotidien =5;
            hebdo = 20;
        }
        else{
            quotidien=2;
            hebdo=0;
        }
    charge_tr=(quotidien*7)+hebdo;
    t_minute+=charge_tr;
    printf("%-12s (%-8s) : %2d min/jour + %2d min/sem = %3d min/sem\n",t_animaux[i].nom,t_animaux[i].espece,quotidien,hebdo,charge_tr);
}

printf("-----------------------------------------------------\n");
printf(" Temps total de nettoyage hebdomadaire : %d heures et %d minutes\n",t_minute / 60, t_minute % 60);
}
int main(){
    srand(time(NULL));
    Animal t_animaux[50];
    int nb_animaux=0;
    nb_animaux=fic_to_struct(t_animaux);
    aff(t_animaux, &nb_animaux);
    day_clean(t_animaux, &nb_animaux);
}






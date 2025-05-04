#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "ctype.h"
#define TAILLE_MAX 150
#define MAX_ANIMAL 50

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
            chaine[taille- 1] = '\0';
        }
        en_lettre(chaine);
    } while(en_lettre(chaine)!=1);
    en_minuscule(chaine);
    return chaine;
    
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
int est_entier_choix(char *caract,int min,int max)
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
float est_flottant_choix(char *caract,int min,int max)
{
   float choix;
   int verif_s;
    do{
        printf("Ajoutez un %s",caract);
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

void aff(Animal t_animaux[],int *nb_animaux)
{
    printf("\n--- Le Refuge ---\n");
    for(int i=0;i<*nb_animaux;i++)
    {
        printf("%d %s %s %d %f",t_animaux[i].id,t_animaux[i].nom,t_animaux[i].espece,t_animaux[i].annee,t_animaux[i].poids);

        if(strlen(t_animaux[i].commentaire)>2){//probleme rencontre dans le cas ou il 'ny a pas de commentaire puisque optionnel
            printf("%s\n",t_animaux[i].commentaire);
        }
    }
    
}
void fic_to_struct(Animal tab_animaux[])
{//fonction de depart pour mettre tous les animaux du fichier dans la tabl struct
    char ligne[256],espece[256],nom[256],commentaire[256];
    int n,id,annee,i=0;
    float poids;

    FILE *fic=fopen("animal.txt","r");
    if(fic == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    while (fgets(ligne, sizeof(ligne)-1, fic) != NULL)
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
    }// y a t-il un *nb_animaux a ajt ???
}
void ajt_animal_strt(Animal t_animaux[],int *nb_animaux)
{ //permet d'ajouter un animal dans  le tab structure animal(Pas dans le fichier)

    Animal a;
    int verif_s;
    int choix_c;
    printf("\n--- Ajouter un nouvel animal ---\n");

    strcpy(a.nom,lettre_minuscule("nom"));
    strcpy(a.espece,lettre_minuscule("espece"));

    a.annee=est_entier("annee_de_naissance ");
    a.poids=est_flottant("poids ");
    choix_c=est_entier_choix("commentaire",0,1);
    if(choix_c == 0)
    {
        strcpy(a.commentaire,lettre_minuscule("commentaire "));
    }
    
    t_animaux[*nb_animaux] = a;
    *(nb_animaux)++;  // ou (*nb_animaux) ????
}
void ajt_animal_fic(Animal t_animaux[],int *nb_animaux)
{//permet d'ajouter tous les animaux dans le fichier
    FILE *fichier=fopen("animal.txt","a");
    if(fichier == NULL)
    {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }
    for(int i=0;i<*nb_animaux;i++)//attention si pas de commentaire a modifier
    {
        fprintf(fichier, "%d %s %s %d %.2f", t_animaux[i].id, t_animaux[i].nom, t_animaux[i].espece,t_animaux[i].annee, t_animaux[i].poids);
        if(strlen(t_animaux[i].commentaire>2))
        {
            fprintf(fichir, "%s\n",t_animaux[i].commentaire);
        }
    }
fclose(fichier);
}

int main(){
    srand(time(NULL));
}






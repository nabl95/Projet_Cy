#include "stdlib.h"
#include "stdio.h"
#include "string.h"


void lire_aff_un_fichier(char *fic)
{
    FILE * fichier_lire=fopen(fic,"r");
    char chaine[256];
    // ajout d une fct qui eneleve le txt du fichier pour le printf lige 22

    if (fichier_lire == NULL) {
       printf("erreur de fichier\n");
       exit(1);
    }
    
    while((fgets(chaine,255,fichier_lire)) != NULL)
    {
        printf("%s",chaine);
    } printf("\n");
    fclose(fichier_lire);
}

int compter_nb_animal(char *fic)
{
    FILE * fichier_lire=fopen(fic,"r");
    char chaine[256];
    int acc=0;

    if (fichier_lire == NULL) {
        printf("erreur de fichier\n");
        exit(1);
     }
     
    while((fgets(chaine,(sizeof(chaine)-1),fichier_lire)) != NULL)
    {
        acc++;
    }
    fclose(fichier_lire);
    return acc;

   


}
void ajout_animal(char *fic)//ajout commentaire pour animal
{
    FILE * fichier_w=fopen(fic,"a");
    char mot[230];
    int tl,id;
    char nom[100],espece[100];

    if(!fichier_w)
    {
        perror("Erreur d'ouverture\n");
        exit(33);
    }

    if(compter_nb_animal(fichier_w)>=50)
    {
        printf("Impossible,trop d'animaux!\n");
        return;
    }

    printf("Donner son nom son espece et son age svp\n");
    scanf("%s %s %d",nom,espece,&age);
    id=rand()%3001;

    fprintf(fichier_w,"%s %s %d %d",nom,espece,age,id);
    printf("L'animal suivant a été ajouté,Voici ces informations:\n%s %s %d %d",nom,espece,age,id);
    fclose(fichier_w);
}

void rechercher_animal(char *fic)//char nom, int age)?
{
    int age,id,flag;
    char nom[256],espece[256];
    int age_voullu;
    int type_age;
    char nom_voullu[256],espece_voullu[256];

    FILE *f_lire=fopen(fic,"r");
    if (f_lire == NULL) {
        printf("erreur de fichier\n");
        exit(1);
     }

    do{

    printf("Donner son nom,son espece\n");
    scanf("%s %s",nom_voullu,espece_voullu);
    printf("On passe a l'age\n");
    printf("Voulez vous un animal 1:jeune(<2ans)\n 2:sénior(>10ans)\n");
    scanf("%d",&type_age);
    if(type_age!=1 && type_age!=2)
    {
        printf("saisie fausse !\n");
        exit(2);
    }
    if(type_age==1)
    {
        printf("donner l'age voullu\n");
        scanf("%d",&age_voullu);
        if(age_voullu<0 && age_voullu>2 )
        {
            printf("age faux!\n");
            exit(3);
        }
    }
    if(type_age==2)
    {
        printf("donner l'age voullu\n");
        scanf("%d",&age_voullu);
        if(age_voullu<10)
        {
            printf("age faux!\n");
            exit(4);
        }
    }

    while(fscanf(f_lire,%s %s %d %d,nom,espece,&age,&id)==3)
    {
        if((age==age_voullu) && (strcmp(nom,nom_voullu)==0) && (strcmp(espece,espece_voullu)==0))
        {
            printf("Super!!\nCette animal existe :\n");
            printf("%s %s %d %d",nom,espece,age,id);
        }
        
        else
        {
            printf("Oups!\n Cette animal n'existe pas\n");
            exit(5);
        }
        

    }
    do{
        printf("Voir pour un autre animal\n1:oui\n2:non\n");
        scanf("%d",&flag);
    }while(flag==1 && flag==2);
    
    }while(flag!=2);
    fclose(f_lire);
}
void adoption(Char *fic)
{


}
int main(){

    char *b="chat.txt";
    fct(b);


   
}




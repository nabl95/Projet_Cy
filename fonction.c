#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "ctype.h"

int issalpha(char * chaine)
{
    int i=0;
    while(*(chaine+i)!='\0')
    {
        if(!isalpha(*(chaine+i)))
        {
            return 0;
        }
        i++;
    }
    return 1;
}
int issdigit(char *chaine)//surement inutile
{
    int i=0;
    while(*(chaine+i)!='\0')
    {
        if(!isdigit(*(chaine+i)))
        {
            return 0;
        }
        i++;
    }
    return 1;

}
void lire_aff_un_fichier(char *fic)
{
    FILE * fichier_lire=fopen(fic,"r");
    char chaine[256];
    // ajout d une fct qui enleve le txt du fichier pour le printf ligne 22

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
    char mot[230];
    int tl,id,age;
    char nom[100],espece[100],commentaire[100];
    int choix;
    srand(time(NULL));

    if(compter_nb_animal(fic)>=50)
    {
        printf("Impossible,trop d'animaux!\n");
        return;
    }
    FILE *fichier_w=fopen(fic,"a"); // Pas ouvrir inutilement si animal>50
    
    if(fichier_w==NULL)
    {
        perror("Erreur d'ouverture\n");
        exit(33);
    }

    do{
        printf("Donner son nom son espece et son age svp\n");
    scanf("%s %s %d",nom,espece,&age);
    }while(!issalpha(nom) && !issalpha(espece));
    id=rand()%3001;//placement important 

    
    do{
        printf("Ajoutez un commentaire?\n1: OUI\n2: NON\nVotre choix : ");
        scanf("%d",&choix);
    }while(choix!=1 && choix !=2);

    if(choix==1)
    {   
    do{
        printf("ecrivez votre commentaire(1 seul mot ou espace d'un '_' ) : ");
        scanf("%s",commentaire);
    }while(!issalpha(commentaire));

        fprintf(fichier_w,"%s %s %d %d %s",nom,espece,age,id,commentaire);
    }

    else{
        fprintf(fichier_w,"%s %s %d %d",nom,espece,age,id);
    }

    fclose(fichier_w);
    lire_aff_un_fichier(fic);
    
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
    printf("Voulez vous un animal 1:jeune(<2ans)\n 2:senior(>10ans)\n");
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
        if(age_voullu<0 )
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

    while(fscanf(f_lire,"%s %s %d %d",nom,espece,&age,&id)==4)
    {
        if((age==age_voullu) && (strcmp(nom,nom_voullu)==0) && (strcmp(espece,espece_voullu)==0))
        {
            printf("Super!!\nCette animal existe :\n");
            printf("%s %s %d %d\n",nom,espece,age,id);
            break;
        }
        
        else
        {
            printf("Oups!\n Cette animal n'existe pas\n");
        }
        

    }
    do{
        printf("Voir pour un autre animal\n1:oui\n2:non\n");
        scanf("%d",&flag);
    }while(flag!=1 && flag!=2);
    
    }while(flag!=2);
    fclose(f_lire);
}
void adoption(char *fic)
{


}
int main(){
    srand(time(NULL));
    char *b="chat.txt";
    char *chaine= "12a1";
    int choix;
    printf("donner votre choix\n");
    scanf("%d",&choix);

  //printf("%d",issalpha(choix));

   
}




#include "stdlib.h"
#include "stdio.h"
#include "string.h"


void lire_un_fichier(char *fic)
{
    FILE * fichier_lire=fopen(fic,"r");
    char chaine[256];
    int acc=0;
    // ajout d une fct qui eneleve le txt du fichier pour le printf lige 22

    if (fichier_lire == NULL) {
       printf("erreur de fichier\n");
       exit(1);
    }
    
    while((fgets(chaine,255,fichier_lire)) != NULL)
    {
        acc++;
        printf("%s",chaine);
    } printf("\n");
    
    printf("il y a %d \n",acc);
    fclose(fichier_lire);

}

void ajout_animal(char *fic)
{
    FILE * fichier_w=fopen(fic,"a");

    char mot[230];
    int tl;
    printf("donner le nom du chat:\n");
    scanf("%s",mot);
    fputs(mot,fichier_w);
    fclose(fichier_w);
}

void rechercher_animal(char *fic,char nom, int age)
{
    int age,id,flag;
    char nom[256];
    int age_voullu;
    int type_age;
    char nom_voullu[256];

    FILE *f_lire=fopen(fic,"r");
    if (f_lire == NULL) {
        printf("erreur de fichier\n");
        exit(1);
     }

    do{

    printf("Donner son nom\n");
    scanf("%s",nom_voullu);
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
    if(type_age==1)
    {
        printf("donner l'age voullu\n");
        scanf("%d",&age_voullu);
        if(age_voullu<10)
        {
            printf("age faux!\n");
            exit(4);
        }
    }

    while(fscanf(f_lire,%s %d %d,nom,&age,&id)==3)
    {
        if(age==age_voullu && (strcmp(nom,nom_voullu)==0))
        {
            printf("Super!!\nCette animal existe\n");
            printf("%s %d %d",nom,age,id);
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
    lire_un_fichier(b);


   
}




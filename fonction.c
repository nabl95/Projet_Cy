#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"
#include "ctype.h"



typedef struct{

    char espece[60];
    int nombre;
}Nb_espece;

void toolower(char *chaine)
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
void aff_fichier(char *fic)
{
    FILE * fichier_lire=fopen(fic,"r");
    char chaine[256];

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


void compter_nb_espece(char *fic)
{
    Nb_espece tab[50];
    int nbr_espece=0;
    char nom[50],espece[50],commentaire[200];
    int age,id,verif;
    char ligne[256];
    int flag;

    FILE *fichier_c=fopen(fic,"r");

    if(fichier_c==NULL)
    {
        printf("Erreur d'ouverture\n");
        exit(12);
    }
  
    while (fgets(ligne, sizeof(ligne)-1, fichier_c) != NULL)
    {
        int n = sscanf(ligne, "%s %s %d %d %s", nom, espece, &age, &id, commentaire);
        if(n>=4)
        {

            flag=0;
            for(int i=0;i<nbr_espece; i++)
            {
                if(strcmp(tab[i].espece,espece)==0)//au depart on ne rentre pas dans ce for, il faut avant tout ajt une premier espece pour la suite de la fct
                {
                tab[i].nombre++;
                flag=1;
                break;
                }
            }
        }

        if(!flag)//equivaut==0
        {
            strcpy(tab[nbr_espece].espece,espece);
            tab[nbr_espece].nombre=1;//nouvel espece on initailise son compteur a 1
            nbr_espece++;
        }
    }
    printf("\nNombre d'animaux par espece :\n");
    for (int i = 0; i < nbr_espece; i++) {
        printf("%s : %d\n", tab[i].espece, tab[i].nombre);
    }
    fclose(fichier_c);


}

void ajout_animal(char *fic)//!!! ajout commentaire pour animal
{
    char mot[230];
    int tl,id,age;
    char nom[100],espece[100],commentaire[100];
    int choix;


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
    toolower(nom);
    toolower(espece);
    
    }while(!issalpha(nom) || !issalpha(espece));
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
        toolower(commentaire);
    }while(!issalpha(commentaire));

        fprintf(fichier_w,"%s %s %d %d %s\n",nom,espece,age,id,commentaire);
    }

    else{
        fprintf(fichier_w,"%s %s %d %d\n",nom,espece,age,id);
    }

    fclose(fichier_w);
    aff_fichier(fic);//teste attentiona supp ou pas 
    
}

void rechercher_animal(char *fic)//char nom, int age)?
{
    int age,id,flag,find=0;
    char nom[256],espece[256],commentaire[200],ligne[256];
    int age_voullu,n;
    int type_age,verif;
    char nom_voullu[256],espece_voullu[256];

    FILE *f_lire=fopen(fic,"r");
    if (f_lire == NULL) {
        printf("erreur de fichier\n");
        exit(1);
     }

    do{
    
    printf("Donner son nom,son espece\n");
    scanf("%s %s",nom_voullu,espece_voullu);
    toolower(nom_voullu);
    toolower(espece_voullu);
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

    rewind(f_lire); // remet au début pour chaque recherche

        while (fgets(ligne, sizeof(ligne), f_lire) != NULL)
        {
            verif = sscanf(ligne, "%s %s %d %d %s", nom, espece, &age, &id, commentaire);

            if (verif >= 4)
            {
                if ((age == age_voullu) && (strcmp(nom, nom_voullu) == 0) && (strcmp(espece, espece_voullu) == 0))
                {
                    printf("Super !! Cet animal existe :\n");
                    printf("%s %s %d %d\n", nom, espece, age, id);
                    find = 1;
                    break;
                }
            }
        }

        if (!find) {
            printf("Oups ! Cet animal n'existe pas.\n");
        }

        do {
            printf("\nVoulez-vous chercher un autre animal ?\n1 : Oui\n2 : Non\nVotre choix : ");
            scanf("%d", &flag);
        } while (flag != 1 && flag != 2);

    } while (flag != 2);

    fclose(f_lire);
}

void adoption( char *fic)
{
    int n_id, age, id, find, flag, confirmer;
    char nom[60], espece[60], commentaire[200], ligne[256];
    int n;

    do {
        find = 0;

        FILE *fichier_a = fopen(fic, "r");
        if (fichier_a == NULL) {
            printf("Erreur d'ouverture\n");
            exit(123);
        }

        FILE *fichier_te = fopen("remp.txt", "w");
        if (fichier_te == NULL) {
            printf("Erreur de création de fichier\n");
            fclose(fichier_a);
            exit(124);
        }

        printf("\nVoici la liste de tous les animaux du refuge :\n");
        aff_fichier(fic);

        printf("\nChoisissez votre animal en mettant son numéro d'identification(2 eme numero) : ");
        scanf("%d", &n_id);

        while (fgets(ligne, sizeof(ligne), fichier_a) != NULL)
        {
            n = sscanf(ligne, "%s %s %d %d %s", nom, espece, &age, &id, commentaire);
            if (n >= 4)
            {
                if (n_id == id) 
                {
                    printf("\nFélicitations ! %s est à vous !\n", nom);
                    printf("Voulez-vous vraiment adopter cet animal ?\n1 : Oui\n2 : Non\nVotre choix : ");
                    scanf("%d", &confirmer);
                    if (confirmer == 1) {
                        find = 1;
                        continue; // on saute l'écriture
                    } else {
                        printf("Adoption annulée, l'animal reste au refuge.\n");
                    }
                }
                // Écrire tous les animaux sauf celui adopté
                if (n == 5) {
                    fprintf(fichier_te, "%s %s %d %d %s\n", nom, espece, age, id, commentaire);
                } else if (n == 4) {
                    fprintf(fichier_te, "%s %s %d %d\n", nom, espece, age, id);
                }
            }
        }

        fclose(fichier_a);
        fclose(fichier_te);

        if (find) {
            remove(fic);
            rename("remp.txt", fic);
        } else {
            printf("\nOups... Aucun animal trouvé avec cet identifiant ou adoption annulée.\n");
            remove("remp.txt");
        }

        do {
            printf("\nVoulez-vous adopter un autre animal ?\n1 : Oui\n2 : Non\nVotre choix : ");
            scanf("%d", &flag);
        } while (flag != 1 && flag != 2);

    } while (flag != 2);
}
int main(){
    srand(time(NULL));
    char *b="animal.txt";
    char *chaine = "NaRbeTTil";
    int choix;
    char texte[50];

   /* printf("donner votre choix\n");
    scanf("%d",&choix);*/
    adoption(b);
  //printf("%d",issalpha(choix));
 

   
}




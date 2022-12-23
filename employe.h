#ifndef EMPLOYE_H_INCLUDED
#define EMPLOYE_H_INCLUDED
#include "date.h"
#define CIN_MAX 10
#define NOM_MAX 20
#define PRENOM_MAX 20
#define NUM_TELE_MAX 10
#define FILE_NAME "employe1.txt"
#define FILE_NAME_TEMP "temp.txt"
FILE* fp;
FILE* file;


void ajoutEmp(void);
void suppEmp(void);
void afficheEmp(void);




typedef struct {
    Date debut;
    Date fin;
    int type; // CDI || CDD
}Contrat;

typedef struct {
    Date lastModif ;
    int days ; //nombre des jours
}Conge;

typedef struct{
    int id;
    char CIN[CIN_MAX];
    char nom[NOM_MAX];
    char prenom[PRENOM_MAX];
    char Num_tele_emp[NUM_TELE_MAX];
    Date date_naiss;
    Conge conge;
    Contrat contrat;
}employe;


void ajoutEmp(){
    FILE* fp;
    fp=fopen(FILE_NAME,"at+");

    employe e;
    int tr=0;
    char CIN_temp[CIN_MAX];
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",CIN_temp);
    printf("\n-----------*********------------\n");

     while(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){

        if(strcmp(CIN_temp,e.CIN)==0){
            tr=1;
            printf("employe deja enregister\n");        //employe deja existe
            break;
        }
        //
        }
        if(tr==0){
       //ajout l'employe dans le fichier
    printf("\n-----------*********------------\n");
    printf("\n-----------*********------------\n");
    printf("id :");
    scanf("%d",&e.id);
    printf("nom:");
    scanf("%s",e.nom);
    printf("prenom:");
    scanf("%s",e.prenom);
    printf("numero de telephone :");
    scanf("%s",e.Num_tele_emp);
    do{
    printf("date naissance :");
    printf("jour:");
    scanf("%d",&e.date_naiss.jour);
    printf("mois:");
    scanf("%d",&e.date_naiss.mois);
    printf("annee:");
    scanf("%d",&e.date_naiss.annee);

    }while(valideDate(e.date_naiss)==0);

    fprintf(fp,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\n",e.id,CIN_temp,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee);
            printf("\n-----------*********------------\n");

            printf("\n\n l'employe a enregistrer avec succes \n");
            printf("\n-----------*********------------\n");
        }

    fclose(fp);
}



void suppEmp(){

system("cls");
employe e;
char CIN_temp[CIN_MAX];
fp=fopen(FILE_NAME,"rt");
file=fopen(FILE_NAME_TEMP,"wt");
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",CIN_temp);
    printf("\n-----------*********------------\n");

//----&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee

    while(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%d\-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){
        if(strcmp(CIN_temp,e.CIN)!=0){
            fprintf(file,"%d\t%s\t%s\t%s\t%s\t%d\-%d-%d\n",e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee);
            printf("\n-----------*********------------\n");
            printf("    l'employe a supprimer avec succes \n");
            printf("\n-----------*********------------\n");

        }
        }

        fclose(fp);fclose(file);
        remove(FILE_NAME);
        rename(FILE_NAME_TEMP,FILE_NAME);






}



void afficheEmp(){
employe e;
system("cls");
int tr=0;
char CIN_temp[CIN_MAX];
fp=fopen(FILE_NAME,"rt");
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",CIN_temp);
    printf("\n-----------*********------------\n");

//----&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee

    while(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%d\-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){
        if(strcmp(CIN_temp,e.CIN)==0){
            tr=1;
            printf("\n-----------*********------------\n");
            printf("\n-----------*********------------\n");
            printf("    id:%d\n",e.id);
            printf("    CIN:%s\n",e.CIN);
            printf("    nom:%s\n",e.nom);
            printf("    prenom:%s\n",e.prenom);
            printf("    num tele:%s\n",e.Num_tele_emp);
            printf("    date de naissance :");
            printf("%d-%d-%d",e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee);
            printf("\n\n");

            printf("\n-----------*********------------\n");
        }

        }
        if(tr==0){
                printf("\n-----------*********------------\n");
                printf("l'employe n'existe pas :\n");
                printf("\n-----------*********------------\n");

        }
        fclose(fp);

}

int getNbrEmploye(){
    employe e ;
    int n=0;
    fp=fopen(FILE_NAME,"rt");
     while(fscanf(fp,"%d\t%s\t%s\t%s\t%s\t%d\-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){

                 n++;

                 }
return n;
}




#endif // EMPLOYE_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define EMPLOYE_H 1

#ifndef DATE_H
#include "date.c"
#endif // DATE_H



#define CIN_MAX 10
#define NOM_MAX 20
#define PRENOM_MAX 20
#define NUM_TELE_MAX 10

#define CDI_CODE 1 /* Contrat de travail à duree indeterminee */
#define CDD_CODE 0 /* Contrat de travail à duree determinee */
#define CDI "Contrat a duree indeterminee"
#define CDD "Contrat a duree determinee"

#define FILE_NAME "employe.txt"
#define FILE_NAME_TEMP "temp.txt"
FILE* fp;
FILE* file;

typedef struct {
    Date debut;
    Date fin;
    int type; // CDI || CDD
}Contrat;

typedef struct {
    Date lastModif ;
    int days ; //nombre des jours
}Conge;

typedef struct employe {
    int id ;
    char CIN[CIN_MAX];
    char nom[NOM_MAX];
    char prenom[PRENOM_MAX];
    char Num_tele_emp[NUM_TELE_MAX];
    Date date_naiss;
    Conge conge;
}employe;


void ajoutEmp(){
employe e;
int tr=0;
static int id=1;
char CIN_temp[CIN_MAX];
fp=fopen(FILE_NAME,"at");
    printf("CIN:");
    scanf("%s",CIN_temp);

//ajouter dans un fichier---------------------
//----&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee
    while(fscanf(fp,"%d\n%s\n%s\n%s\n%s\n%d-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){
        if(strcmp(CIN_temp,e.CIN)==0){
            tr=1;
        }

        }
    //
    if(tr==1){
        printf("employe deja enregister\n");
        fclose(fp);                            //employe deja existe
    }else{
       //ajout l'employe dans le fichier

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

    fprintf(fp,"%d\n%s\n%s\n%s\n%s\n%d-%d-%d\n",id=e.id+1,CIN_temp,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee);

    }

    fclose(fp);

}

void suppEmp(){

employe e;
char CIN_temp[CIN_MAX];
fp=fopen(FILE_NAME,"rt");
file=fopen(FILE_NAME_TEMP,"wt");
    printf("CIN:");
    scanf("%s",CIN_temp);

//----&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee

    while(fscanf(fp,"%d\n%s\n%s\n%s\n%s\n%d-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){
        if(strcmp(CIN_temp,e.CIN)!=0){
            fprintf(file,"%d\n%s\n%s\n%s\n%s\n%d-%d-%d\n",e.id,CIN_temp,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee);

        }
        fclose(fp);fclose(file);
        remove(FILE_NAME);
        rename(FILE_NAME_TEMP,FILE_NAME);
        }





}

void afficheEmp(){
employe e;
int tr=0;
char CIN_temp[CIN_MAX];
fp=fopen(FILE_NAME,"rt");
    printf("CIN:");
    scanf("%s",CIN_temp);

//----&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee

    while(fscanf(fp,"%d\n%s\n%s\n%s\n%s\n%d-%d-%d\n",&e.id,e.CIN,e.nom,e.prenom,e.Num_tele_emp,
                 &e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee)==8){
        if(strcmp(CIN_temp,e.CIN)==0){
            tr=1;
            printf("CIN:",e.CIN);
            printf("nom:",e.nom);
            printf("prenom:",e.prenom);
            printf("num tele:",e.Num_tele_emp);
            printf("date de naissance :");
            printDate(e.date_naiss);
        }

        }
        if(tr==0){
            printf("l'employe n'existe pas :\n");

        }
        fclose(fp);

}

















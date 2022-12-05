#include<stdio.h>
#include<stdlib.h>

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
FILE* fp;

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
    char nom_emp[NOM_MAX];
    char prenom_emp[PRENOM_MAX];
    char Num_tele_emp[NUM_TELE_MAX];
    Date date_naiss;
}employe;

employe saisie_emp(){
    employe e;
    printf("CIN:");
    scanf("%s",e.CIN);
    printf("nom:");
    scanf("%s",e.nom_emp);
    printf("prenom:");
    scanf("%s",e.prenom_emp);
    printf("numero de telephone :");
    scanf("%s",e.Num_tele_emp);
    printf("date naissance :");
    printf("jour:");
    scanf("%d",&e.date_naiss.jour);
    printf("mois:");
    scanf("%d",&e.date_naiss.mois);
    printf("annee:");
    scanf("%d",&e.date_naiss.annee);
return e;

}
//get employe from a file


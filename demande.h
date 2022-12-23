#ifndef DEMANDE_H_INCLUDED
#define DEMANDE_H_INCLUDED
#include "date.h"
#include "acces.h"

/************** gestion des demnade  *****************/

#define FILE_NAME_demande "demande.txt"
#define FILE_NAME_demande_TEMP "demandee.txt"
#define TAILLE_MAX 100

/*code des congee*/
#define CONGE_PAYE 0
#define CONGE_IMPAYE 1
#define CONGE_URGENT 2


/* Libelles des conges */
#define CONGE_PAYE_ITEM   "Conge paye"
#define CONGE_IMPAYE_ITEM "Conge non paye"
#define CONGE_URGENT_ITEM  "Conge urgent"

/* etat de demande */
#define CONGE_ETAT_REFUSE 0
#define CONGE_ETAT_ACCEPTER 1
#define CONGE_ETAT_INDETERMINER 2 //en cas de traitement

/* Libelle d'etat des demandes */
#define DEMANDE_ETAT_REFUSE_ITEM "Refusee"
#define DEMANDE_ETAT_ACCEPTER_ITEM "Acceptee"
#define DEMANDE_ETAT_INDETERMINER_ITEM "Indeterminee"

/*congee par mois*/

#define CONGE_PAR_MOIS 2.5

FILE* fp1;
FILE* temp;

typedef struct {
    int congeCode;
    char Libelle_typeConge;

}typeConge;


typedef struct {
    int id_Demande;
    Date dateDeb;
    Date dateFin;
    int etat_demande;
    int days;
    typeConge typeconge;
    employe e;

}Demande;

Demande d ;


char * getDemandeType(int n){
    switch(n){
    case CONGE_PAYE :
        return CONGE_PAYE_ITEM;
    case CONGE_IMPAYE :
        return CONGE_IMPAYE_ITEM;
    case CONGE_URGENT :
        return CONGE_URGENT_ITEM;
    }

}

/*
    printf("0 --->>> conge paye\n");
    printf("1 --->>> conge impaye\n");
    printf("2 --->>> conge urgent\n");
    scanf("%d",&d.typeconge.congeCode);
    getDemandeType(d.typeconge.congeCode);
*/



//ajout un demande

void ajoute_demande(){
    system("cls");
    printf("information du demandeur :\n");
    printf("\n--------------------------------------------\n");
    printf("CIN:");
    scanf("%s",d.e.CIN);
    printf("id:");
    scanf("%d",&d.id_Demande);
    printf("nom:");
    scanf("%s",d.e.nom);
    printf("prenom:");
    scanf("%s",d.e.prenom);
    printf("numero de telephone :");
    scanf("%s",d.e.Num_tele_emp);
    do{
        printf("date de naissance :\n");
        printf("jour:");
        scanf("%d",&d.e.date_naiss.jour);
        printf("mois");
        scanf("%d",&d.e.date_naiss.mois);
        printf("annee");
        scanf("%d",&d.e.date_naiss.annee);
    }while(!valideDate(d.e.date_naiss));

    printf("date :\n");
    printf("\n--------------------------------------------\n");
    do{
        printf("date de debut  :\n");
        printf("jour:");
        scanf("%d",&d.dateDeb.jour);
        printf("mois");
        scanf("%d",&d.dateDeb.mois);
        printf("annee");
        scanf("%d",&d.dateDeb.annee);

         printf("date de fin  :\n");
        printf("jour:");
        scanf("%d",&d.dateFin.jour);
        printf("mois");
        scanf("%d",&d.dateFin.mois);
        printf("annee");
        scanf("%d",&d.dateFin.annee);

    }while(!valideDate(d.dateDeb)&& !valideDate(d.dateFin)&& !isGreaterThan(d.dateDeb,d.dateFin)
           && !isEqualDate(d.dateDeb ,d.dateFin) );

    fp1=fopen(FILE_NAME_demande,"at+");
        if(fp1==NULL){
            printf("impossible d'ouvrir le fichier !!!");
            exit(0);
        }


        fprintf(fp1,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\n",d.id_Demande,d.e.CIN,d.e.nom,d.e.prenom
                ,d.e.Num_tele_emp ,d.e.date_naiss.jour,d.e.date_naiss.mois,d.e.date_naiss.annee
                ,d.dateDeb.jour,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee);
                printf("la demande a bien ajouter \n");

    fclose(fp1);

}

void supp_demande(){
    system("cls");
    int id;
    fp1=fopen(FILE_NAME_demande,"rt");
    if(fp1==NULL)
        printf("impossible d'ouvrir le fichier !!!\n");
    temp=fopen(FILE_NAME_demande_TEMP,"wt");
        if(temp==NULL)
                printf("impossible de cree le fichier !!!\n");
        printf("id de demande :");
        scanf("%d",&id);

    while(fscanf(fp1,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\n",&d.e.id,d.e.CIN,d.e.nom,d.e.prenom
                ,d.e.Num_tele_emp ,&d.e.date_naiss.jour,&d.e.date_naiss.mois,&d.e.date_naiss.annee
                ,&d.dateDeb.jour,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee)==14){

    if(id!=d.e.id){
        fprintf(temp,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\n",d.e.id,d.e.CIN,d.e.nom,d.e.prenom
                ,d.e.Num_tele_emp ,d.e.date_naiss.jour,d.e.date_naiss.mois,d.e.date_naiss.annee
                ,d.dateDeb.jour,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee);

    }
    }
    fclose(fp1);
    fclose(temp);
    remove(FILE_NAME_demande);
    rename(FILE_NAME_demande_TEMP,FILE_NAME_demande);
    printf("la demande a supp avec succes\n");


}


void affiche_demande(){
    system("cls");
    char CIN2[TAILLE_MAX];
    printf("CIN:");
    scanf("%s",CIN2);
    fp1=fopen(FILE_NAME_demande,"rt");
    if(fp1==NULL)
        printf("impossible d'ouvrir le fichier\n");
    while(fscanf(fp1,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\n",&d.e.id,d.e.CIN,d.e.nom,d.e.prenom
                ,d.e.Num_tele_emp ,&d.e.date_naiss.jour,&d.e.date_naiss.mois,&d.e.date_naiss.annee
                ,&d.dateDeb.jour,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee)==14){

            if(strcmp(CIN2,d.e.CIN)==0){
                    printf("\n-----------*********------------\n");
                printf("id:%d\n",d.e.id);
                printf("nom : %s\n",d.e.nom);
                printf("prenom : %s\n",d.e.prenom);
                printf("num tele:%s\n",d.e.Num_tele_emp);
                printf("date de naissance :");
                printf("%d-%d-%d\n",d.e.date_naiss.jour,d.e.date_naiss.mois,d.e.date_naiss.annee);
                printf("date de debut de congee :");
                printf("%d-%d-%d\n",d.dateDeb.jour,d.dateDeb.mois,d.dateDeb.annee);
                printf("la date de la fin de congee :");
                printf("%d-%d-%d\n",d.dateFin.jour,d.dateFin.mois,d.dateFin.annee);
                printf("le nombre des jours de congee:%d\n",getDiffDays(d.dateFin,d.dateDeb));
                printf("\n-----------*********------------\n");
                printf("\n-----------*********------------\n");





                }

                }

}

int getNbrCongee(){
    int n=0;
    fp1=fopen(FILE_NAME_demande,"rt");
    while(fscanf(fp1,"%d\t%s\t%s\t%s\t%s\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\n",&d.e.id,d.e.CIN,d.e.nom,d.e.prenom
                ,d.e.Num_tele_emp ,&d.e.date_naiss.jour,&d.e.date_naiss.mois,&d.e.date_naiss.annee
                ,&d.dateDeb.jour,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee)==14){

                n++;




                }

return n;
}








#endif // DEMANDE_H_INCLUDED

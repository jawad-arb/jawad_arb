#ifndef ABSENCE_H_INCLUDED
#define ABSENCE_H_INCLUDED
#include "date.h"
#include "acces.h"


#define DESCRIPTION_TAILLE_MAX 2500

/* Types des absences */

#define ABSENCE_TYPE_MALADIE 1
#define ABSENCE_TYPE_FORMATION 2
#define ABSENCE_TYPE_REUNION 3
#define ABSENCE_TYPE_INJUSITFIEE 4
#define ABSENCE_TYPE_MALADIE_LIBELLEE "Absence de maladie"
#define ABSENCE_TYPE_FORMATION_LIBELLEE "Absence de formation"
#define ABSENCE_TYPE_REUNION_LIBELLEE "Absence de reunion"
#define ABSENCE_TYPE_INJUSITFIEE_LIBELLEE "Absence injustifiee"

#define FILE_NAME_ABSENCE "absence.txt"
#define FILE_NAME_ABSENCEE"absencee.txt"
FILE* fp2;
FILE* fp1;

typedef struct {
  int id_absence;
  int id_employe;
  Date date;
  int type;  // Maladie - Formation - Reunion
  char description[DESCRIPTION_TAILLE_MAX];
} Absence;


char* getAbsenceType2(int type) {
  switch (type) {
    case ABSENCE_TYPE_MALADIE:
      return ABSENCE_TYPE_MALADIE_LIBELLEE;
    case ABSENCE_TYPE_FORMATION:
      return ABSENCE_TYPE_FORMATION_LIBELLEE;
    case ABSENCE_TYPE_REUNION:
      return ABSENCE_TYPE_REUNION_LIBELLEE;
    case ABSENCE_TYPE_INJUSITFIEE:
      return ABSENCE_TYPE_INJUSITFIEE_LIBELLEE;
    default:
      return "Type de conge incorrecte";
  }
}


//ajout un absence

void ajout_absence() {
    Absence absence ;
    int tr=0;
    int id_abs;
    fp2=fopen(FILE_NAME_ABSENCE,"at+");
    if(fp2==NULL){
        printf("fichier n'existe pas\n");
        exit(0);
    }
    printf("id d'absence:");
    scanf("%d",&id_abs);

    while(fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type),&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){
                     int temp=absence.id_absence;

    if(id_abs==temp){
            tr=1;
            printf("absence deja enregister\n");        //employe deja existe
            break;
        }
         }


    if(tr==0){
    printf("id d emploi:");
    scanf("%d",&absence.id_employe);
    printf("le type de absence\n");
    printf("1-->>Absence de maladie \n");
    printf("2-->>Absence de formation\n");
    printf("3-->>Absence de reunion\n");
    printf("votre choix:");
    scanf("%d",&absence.type);

    do{
    printf("date d'absence :");
    printf("jour:");
    scanf("%d",&absence.date.jour);
    printf("mois:");
    scanf("%d",&absence.date.mois);
    printf("annee:");
    scanf("%d",&absence.date.annee);


}while(valideDate(absence.date)==0);
printf("description");
scanf("%s",absence.description);

fprintf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",id_abs,absence.id_employe,getAbsenceType2(absence.type),absence.date.jour,absence.date.mois
                 ,absence.date.annee,absence.description);

printf("l'absence a ajouter avec succes\n");

    }

fclose(fp2);
}


void supp_absence(){
	Absence absence;

	int id_abs;
	 fp2=fopen(FILE_NAME_ABSENCE,"rt");
		 fp1=fopen(FILE_NAME_ABSENCEE,"wt");
		 printf("donner id de absence que vous voulez suppremez");
		 scanf("%d",&id_abs);

		  while(fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type),&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){

 if(strcmp(id_abs,absence.id_absence)==0){

            fprintf(fp1,"%d\n%d\n%d\n%d-%d-%d-%d\n%s\n",absence.id_absence,absence.id_employe,getAbsenceType2(absence.type),absence.date.jour,absence.date.mois
                 ,absence.date.annee,absence.description);
                 printf("l'absence est supp avec succes \n");
        break;
        }
    }
    fclose(fp1);fclose(fp2);
    remove(FILE_NAME_ABSENCE);
    rename(FILE_NAME_ABSENCEE,FILE_NAME_ABSENCE);

}

void  afficheAbsence(){
	Absence absence;
	int id_abs;
	fp2=(FILE_NAME_ABSENCE,"rt");
	printf("donner id absence");
	scanf("%d",&id_abs);
	 while(fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type),&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){

 if(strcmp(id_abs,absence.id_absence)==0){


   printf("%d\n",absence.id_absence);
   printf("%d\n",absence.id_employe);
   printf("%d\n",absence.type);
   printf(" la date d'absence :%d-%d-%d\n",absence.date.jour,absence.date.mois,absence.date.annee);
   printf("%s",absence.description);


        }
    }
    fclose(fp2);
}

int afficheNbrAbsencemaladie() {
    int n=0;
 fp2 = fopen(FILE_NAME_ABSENCE, "rt");

  Absence absence;

   while (fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type),&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){


    if (strcmp(getAbsenceType2(absence.type),ABSENCE_TYPE_MALADIE_LIBELLEE )==0){

      n++;
  }
  }
  fclose(fp2);
  return n;
}
int afficheNbrAbsenceformation() {
  int n=0;
 fp2 = fopen(FILE_NAME_ABSENCE, "rt");

  Absence absence;

   while (fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type) ,&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){


    if (strcmp(getAbsenceType2(absence.type),ABSENCE_TYPE_FORMATION_LIBELLEE )==0){

      n++;
  }
  }
  fclose(fp2);
  return n;
}
int afficheNbrAbsencereunion() {
 int n=0;
 fp2 = fopen(FILE_NAME_ABSENCE, "rt");

  Absence absence;

   while (fscanf(fp2,"%d\t%d\t%s\t%d-%d-%d\t%s\n",&absence.id_absence,&absence.id_employe,getAbsenceType2(absence.type),&absence.date.jour,&absence.date.mois
                 ,&absence.date.annee,absence.description)==7){


    if (strcmp(getAbsenceType2(absence.type),ABSENCE_TYPE_FORMATION_LIBELLEE )==0){

      n++;
  }
  }
  fclose(fp2);
  return n;
}



#endif // ABSENCE_H_INCLUDED

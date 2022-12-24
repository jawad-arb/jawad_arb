#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "date.c"



/**************** gestion de employe   ******************************/

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
    float salaire;
    Date date_naiss;
    Conge conge;
    Contrat contrat;
}employe;

employe e;



int getLastEmpId(){
    FILE* fp;
    fp=fopen(FILE_NAME,"r");
    fseek(fp,-99,SEEK_END);
    int id;
    fscanf(fp,"%d",&id);
    fclose(fp);

    return id+1;
}



void ajoutEmp(){
    fp=fopen(FILE_NAME,"a+");

    employe e;
    int tr=0;
    char CIN_temp[CIN_MAX];
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",CIN_temp);
    printf("\n-----------*********------------\n");
    
    char buff1[99],cin[CIN_MAX];
    int id ;
    fseek(fp,99,SEEK_SET);
    while(!feof(fp)){
        fgets(buff1,99,fp);
        sscanf(fp,"%d%s",&id,cin);

        if(strcmp(cin,CIN_temp)==0){
            printf("employe existe .\n");
            tr=1;
            break;
        }
    }
    if(tr==0){
        //ajout l'employe dans le fichier
    printf("\n-----------*********------------\n");
    printf("\n-----------*********------------\n");
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
    printf("salaire:");
    scanf("%f",&e.salaire);

    }while(valideDate(e.date_naiss)==0);

    fprintf(fp,"%-10d%-10s%-15s%-15s%-15s%d/%d/%-14d%-12.2f\n",getLastEmpId(),CIN_temp,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee, e.salaire);
            printf("\n-----------*********------------\n");

            printf("\n\n l'employe a enregistrer avec succes \n");
            printf("\n-----------*********------------\n");
        }

    fclose(fp);


    }


void suppEmp(){

employe e;
char CIN_temp[10];
fp=fopen(FILE_NAME,"r");
file=fopen(FILE_NAME_TEMP,"w");
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",CIN_temp);
    printf("\n-----------*********------------\n");


    char buff[99], cin[10];
    int id;
    int found = 0;
    fgets(buff,99,fp);
    fputs(buff,file);
    rewind(fp);
    fseek(fp,99,SEEK_SET);
    while(!feof(fp)) {
        fgets(buff,99, fp);
        sscanf(buff,"%d%s",&id,cin);
        

        if(strcmp(CIN_temp,cin)!=0) {
            fputs(buff,file);
            found=1;
        } 
    }

    if(found==1) {
        printf("\n-----------*********------------\n");
        printf("    l'employe a supprimer avec succes \n");
        printf("\n-----------*********------------\n");

        
    }else {
        printf("    cin non trouvable \n");
    }
        fclose(fp);fclose(file);
        remove(FILE_NAME);
        rename(FILE_NAME_TEMP,FILE_NAME);

}


void rechercheEmp(){

    fp=fopen(FILE_NAME,"r");
    char cin[20];
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",&cin);
    printf("\n-----------*********------------\n");
    char buff[99], fCin[20];
    int id;

    fseek(fp,99,SEEK_CUR);
    while(!feof(fp)) {
        fgets(buff,99, fp);
        sscanf(buff,"%d%s",&id,fCin);
        if(strcmp(cin,fCin)==0) {
            printf("%s",buff);
            return;
        }
    }

    printf("cin non trouvable \n");



    fclose(fp);



    }



int getIdByCin(char* cin){
fp=fopen(FILE_NAME,"r");

char buff[99], fCin[20];
    int id;
    fseek(fp,99,SEEK_CUR);
    while(!feof(fp)) {
        fgets(buff,99, fp);
        sscanf(buff,"%d%s",&id,fCin);
        if(strcmp(cin,fCin)==0) {

            return id ;
        }
    }
    return -1;
fclose(fp);

}

/********************* gestion des demnade  ****************************/

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
    int id_emp;
    int id_Demande;
    char CIN[CIN_MAX];
    Date dateDeb;
    Date dateFin;
    int etat_demande;
    int days;
    typeConge typeconge;
    

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

int getLastDmdId(){
    FILE* fp1;
    fp=fopen(FILE_NAME_demande,"r");
    fseek(fp1,-78,SEEK_END);
    int id,id_Dmd;
    fscanf(fp1,"%d%d",&id,&id_Dmd);
    fclose(fp1);

    return id_Dmd+1;
}

//ajout un demande

void ajoute_demande(){
    system("cls");
    printf("information du demandeur :\n");
    printf("\n--------------------------------------------\n");
    printf("CIN:");
    scanf("%s",d.CIN);
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
           printf("0-->congee paye\n");
           printf("1-->congee non payee");
           printf("2-->congee urgent\n");
           printf("votre choix :");
           scanf("%d",d.typeconge.congeCode);
           

    fp1=fopen(FILE_NAME_demande,"a");

        if(fp1==NULL){
            printf("impossible d'ouvrir le fichier !!!");
            exit(0);
        }


        fprintf(fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",getIdByCin(d.CIN),getLastDmdId(),d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee,getDemandeType(d.typeconge.congeCode));
                printf("la demande a bien ajouter \n");

    fclose(fp1);

}

/*fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",getIdByCin(d.CIN),getLastDmdId(),d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee,getDemandeType(d.typeconge.congeCode) */

/*
fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",&d.id_emp,&d.id_Demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee,d.typeconge.Libelle_typeConge

*/

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

    while(fscanf(fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",&d.id_emp,&d.id_Demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee,d.typeconge.Libelle_typeConge)==9){

    if(id!=d.id_Demande){
        fprintf(temp,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",getIdByCin(d.CIN),getLastDmdId(),d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee,getDemandeType(d.typeconge.congeCode));

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
    fp1=fopen(FILE_NAME_demande,"r");
    if(fp1==NULL)
        printf("impossible d'ouvrir le fichier\n");
    while(fscanf(fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",&d.id_emp,&d.id_Demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee,d.typeconge.Libelle_typeConge)==9){

            if(strcmp(CIN2,d.CIN)==0){
                    printf("\n-----------*********------------\n");
                printf("id de employe :%d\n",d.id_emp);
                printf("id de demande :%d\n",d.id_Demande);
                printf("date de debut de congee :");
                printf("%d-%d-%d\n",d.dateDeb.jour,d.dateDeb.mois,d.dateDeb.annee);
                printf("la date de la fin de congee :");
                printf("%d-%d-%d\n",d.dateFin.jour,d.dateFin.mois,d.dateFin.annee);
                printf("type de congee :%s",d.typeconge.Libelle_typeConge);
                printf("le nombre des jours de congee:%d\n",getDiffDays(d.dateFin,d.dateDeb));
                
                printf("\n-----------*********------------\n");
                printf("\n-----------*********------------\n");





                }

                }

}


int getNbrCongee(){
    int n=0;
    fp1=fopen(FILE_NAME_demande,"rt");
    while(fscanf(fp1,"%-12d%-12d%d/%d/%-10d%d/%d/%-10d%-12s",&d.id_emp,&d.id_Demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee,d.typeconge.Libelle_typeConge)==9){

                n++;




                }

return n;
}


/*************************** gesion des demande *******************************************/
































































int main(){
    int choix,x;
    /** menu **/
    printf("\n\n");
    printf("\n-----------*********------------\n");
    printf("\n-----------*********------------\n");
    printf("    1-->> gestion des employes\n");
    printf("    2-->> gestion des demande\n");
    printf("    3-->> gestion des absences\n");
    printf("    4-->> statistique\n");
    printf("    5-->> quitter le programme \n");
    printf("\n-----------*********------------\n");
    printf("votre choix:");
    scanf("%d",&choix);
    system("cls");

    /** sous menu **/

    switch(choix){
        case 1 :{
            printf("\n-----------*********------------\n");
            printf("\n-----------*********------------\n");
            printf("    1-->ajout un employe:\n");
            printf("    2-->supprimer un employe :\n");
            printf("    3-->afficher un employe:\n");
            printf("    4-->retour\n");
            printf("    5-->quitter le programme\n");
            printf("\n-----------*********------------\n");
            printf("votre choix:");
            scanf("%d",&x);
            //----------------------------------------------- gere employe
            switch(x){
        case 1 :

            ajoutEmp();
            break;

         case 2 :
            suppEmp();
            break;
            exit(0);

          case 3 :
            rechercheEmp();
            break;
            exit(0);

           case 4 :
               system("cls");
                exit(0);

            case 5 :
                exit(0);


        }
        break;

        }


        case 2:{
            printf("\n-----------*********------------\n");
            printf("\n-----------*********------------\n");
            printf("    1-->ajout un demande:\n");
            printf("    2-->supprimer un demande :\n");
            printf("    3-->afficher un demandes:\n");
            printf("    4-->afficher tout mes demandes \n");
            printf("    5-->quitter le programme\n");
            printf("\n-----------*********------------\n");
            printf("votre choix:");
            scanf("%d",&x);
             switch(x){
        case 1 :{
            ajoute_demande();
            break;

        }
         case 2 :{
            supp_demande();
            break;
         }
          case 3 :{
              affiche_demande();
            break;
          }
           case 4 :{
               //affiche_MesDemande();
                break;
           }
            case 5 :{
                break;
            }

    }
            break;
        }
        case 3:{
            printf("\n-----------*********------------\n");
            printf("\n-----------*********------------\n");
            printf("    1-->ajout un absence:\n");
            printf("    2-->supprimer un absence :\n");
            printf("    3--> affiche l'absence\n");
            printf("    4-->afficher nombre des absences MALADIE:\n");
            printf("    5-->afficher nombre des absences FORMATION:\n");
            printf("    6-->afficher nombre des absences reunion:\n");
            printf("    7-->quitter le programme\n");
            printf("\n-----------*********------------\n");
            printf("votre choix:");
            scanf("%d",&x);

            switch(x){
                    case 1:{
                        //ajout_absence();
                        break;

                    }

                case 2:{
                        //supp_absence();
                        break;

            }
                case 3:{
                        //afficheAbsence();
                            break;
                    }
                case 4:{
                    
                        break;
                }
                case 5:{
                    
                    break;
                }
                case 6:{
                    
                    break;
                }
                case 7:{
                    break;
                }

            }


                        break;
                    }


                    case 4: {
                        system("cls");
                        printf("\n-----------*********------------\n");
                        printf("\n-----------*********------------\n");
                       
                       printf("nombre des congee   --->>> \n");
                       printf("\n-----------*********------------\n");
                       exit(0);
                    }

                    case 5: {
                       printf("fin de programme \n");
                       exit(0);
                    }


    }


        return 0;
    }

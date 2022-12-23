#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "employe.h"
#include "demande.h"
#include "absence.h"


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
            exit(0);

         case 2 :
            suppEmp();
            break;
            exit(0);

          case 3 :
            afficheEmp();
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
                        ajout_absence();
                        break;

                    }

                case 2:{
                        supp_absence();
                        break;

            }
                case 3:{
                        afficheAbsence();
                            break;
                    }
                case 4:{
                    printf("%d",afficheNbrAbsencemaladie());
                        break;
                }
                case 5:{
                    printf("%d",afficheNbrAbsenceformation());
                    break;
                }
                case 6:{
                    printf("%d",afficheNbrAbsencereunion());
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
                       printf("nombre des employes --->>> %d\n",getNbrEmploye());
                       printf("nombre des congee   --->>> %d\n",getNbrCongee());
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



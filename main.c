#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef EMPLOYE_H
#include "employe.c"
#endif // EMPLOYE_H

#ifndef DATE_H
#include "date.c"
#endif // DATE_H

int choix,choix1,x;
void menu(){
    printf("1--> gestion des employes\n");
    printf("2--> gestion des congees\n");
    printf("3-->  consultation \n");//les demandes et son etat (accepter ou refuser)::
    printf("4--> quitter le programme \n");
    printf("votre choix:");
    scanf("%d",&choix);
    sous_menu(choix);
}

void sous_menu(int choix){
    switch(choix){
        case 1 :{
            printf("1-->ajout un employe:\n");
            printf("2-->supprimer un employe :\n");
            printf("3-->afficher un employe:\n");
            printf("4-->retour\n");
            printf("5-->quitter le programme\n");
            printf("votre choix:");
            scanf("%d",&x);
            gere_employe(x);
        }
        case 2:{
            printf("1-->ajout un demande:\n");
            printf("2-->supprimer un demande :\n");
            printf("3-->afficher mes demande:\n");
            printf("4-->retour\n");
            printf("5-->quitter le programme\n");
            printf("votre choix:");
            scanf("%d",&x);
            gere_demande(x);
            printf("1-->ajout un demande:\n");
            printf("2-->supprimer un demande :\n");
            printf("3-->modifier un demande:\n");
            printf("4-->retour\n");
            printf("5-->quitter le programme\n");
            printf("4-->votre choix:");
            scanf("%d",&x);
            //gere_congee(x);
        }
        case 3:{
            //afiche_congee();
        }
        case 4:{
           printf("fin de programme \n");
           return 0;
        }


    }

}

//gere les employe

void gere_employe(int x){

    switch(x){
        case 1 :{
            ajoutEmp();
            break;

        }
         case 2 :{
            suppEmp();
            break;
         }
          case 3 :{
            afficheEmp();
            break;
          }
           case 4 :{
               system("cls");
               menu();

           }
            case 5 :{
                break;
            }





    }

}

void gere_demande(int x){

    switch(x){
        case 1 :{

            break;

        }
         case 2 :{

            break;
         }
          case 3 :{

            break;
          }
           case 4 :{
               system("cls");
               menu();

           }
            case 5 :{
                break;
            }





    }

}





int main(){

menu();


return 0;
}

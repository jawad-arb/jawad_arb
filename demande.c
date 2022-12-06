#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEMANDE_H_ 1

#ifndef DATE_H
#include "date.c"
#endif // DATE_H

#ifndef EMPLOYE_H
#include "employe.c"
#endif // EMPLOYE_H

#define FILE_NAME_demande "demande.txt"

/* Libelles des conges */
#define CONGE_PAYE_ITEM   "Conge paye"
#define CONGE_IMPAYE_ITEM "Conge non paye"
#define CONGE_URGENT_ITEM  "Conge urgent"


FILE* fp1;

typedef struct {
    int congeCode;
    char Libelle_typeConge;

}typeConge;


typedef struct {
    int id_Demande;
    Date dateDeb;
    Date dateFin;
    int etat;
    int days;
    typeConge typeconge;
    employe e;


}Demande;

int getCongeType(char* type) {
  if (!strcmp(type, CONGE_PAYE_ITEM))
    return CONGE_PAYE;
  else if (!strcmp(type, CONGE_IMPAYE_ITEM))
    return CONGE_IMPAYE;
  else if (!strcmp(type, CONGE_URGENT_ITEM))
    return CONGE_URGENT;
  return -1;
}

int calcConge(int jours) {
  /**
   * Le nombre de jours travailles par mois (30jours) est 22
   * 22 jours de travail => 2.5 jours de conge
   * 22 ==========> 2.5
   * 01 ==========> ???
   */
  double x = 2.5 / 22; // x = ???
  return arroundissement(x * jours);
}



#include<stdio.h>
#include<string.h>
#include<time.h>

#define DATE_H 1


#define SAMEDI_ID   6
#define DIMANCHE_ID 0

#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define HOUR_PER_DAY 24

#define _DATE_H 1

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;

//verifier si deux date sont equal

int isEqualDate(Date d1 , Date d2){

    return d1.annee==d2.annee && d1.mois==d2.mois && d1.jour==d2.jour ;
}
//verifier si la date est correct

int valideDate(Date date){
    return (date.jour>0 && date.jour<=31)
        &&(date.mois>0 && date.mois<=12)
        &&(date.annee>1960);
}
//verifier si la date 1 est inferieur a la date 2 :

int isGreaterThan(Date d1 , Date d2){
    if(!valideDate(d1) || !valideDate(d2));
        return 0;
    return d1.annee<d2.annee ||(d1.annee==d2.annee && (d1.mois <d2.mois || (d1.mois==d2.annee && d1.jour < d2.jour)));
}
//Calculer le nombre de jours entre la date 1 et la date 2 (Date1 - Date2)
//pour determiner nombre des jours entre deux de congees

int getDiffDays(Date d1, Date d2) {
  if (isEqualDate(d1, d2))
    return 0;

  struct tm t1;
  t1.tm_isdst = -1;
  t1.tm_sec    = 0;
  t1.tm_min    = 0;
  t1.tm_hour   = 0;
  t1.tm_mday   = d1.jour;
  t1.tm_mon    = d1.mois - 1;
  t1.tm_year   = d1.annee - 1900;

  struct tm t2;
  t2.tm_isdst = -1;
  t2.tm_sec    = 0;
  t2.tm_min    = 0;
  t2.tm_hour   = 0;
  t2.tm_mday   = d2.jour;
  t2.tm_mon    = d2.mois - 1;
  t2.tm_year   = d2.annee - 1900;

  return difftime(mktime(&t1), mktime(&t2)) / (int) (SEC_PER_MIN * MIN_PER_HOUR * HOUR_PER_DAY);
}

//Saisir la date sous format (dd-mm-yy)



Date saisirDate(){
  Date date ;
  do{
    scanf("%d-%d-%d",&(date.jour),&(date.mois),&(date.annee));
  }while(!valideDate(date));
return date;
}

Date strToDate(char* sDate) {
  Date date;
  sscanf(sDate, "%d-%d-%d", &(date.jour), &(date.mois), &(date.annee));
  return date;
}
//initialiser la date

Date initDate(int j , int m , int a){
    Date d;
    d.jour=j;
    d.mois=m;
    d.annee=a;
return d;
}

//afficher la date sous la forme dd/mm/yy

int printDate(Date date){
    if(!valideDate(date)){
        printf("la date est invalide\n");
        return -1;
        }

    printf("%d-%d-%d",(date.jour),(date.mois),(date.annee));
        return 1;
}
//date d'aujourd'hui
Date today() {
  time_t t;
  t = time(&t);
  struct tm* c = gmtime(&t);
  return (Date) {c->tm_mday, c->tm_mon + 1, c->tm_year + 1900};
}
//Jour de la semaine, 0 à 6 (commençant par 0: dimanche)

int getWeekDay(Date d) {
  struct tm t1;

  t1.tm_isdst = -1;
  t1.tm_sec    = 0;
  t1.tm_min    = 0;
  t1.tm_hour   = 0;
  t1.tm_mday   = d.jour;
  t1.tm_mon    = d.mois - 1;
  t1.tm_year   = d.annee - 1900;
  mktime(&t1);

  return t1.tm_wday;
}
//Verifier si l'annee est une annee bissextile

int isLeapYear(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}
//Nombre de jour par mois
int daysPerMonth(Date d) {
  if (d.mois == 2)
    return isLeapYear(d.annee) ? 28 : 29;
  int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return *(days + d.mois - 1);
}
//Calculer le nombre de jours entre 2 Dates, similaire à getDiffDays(Date, Date)
int getDays(Date d1, Date d2) {
  if (isEqualDate(d1, d2))
    return 0;

  if (d1.annee <= d2.annee) {
    if ((d1.mois < d2.mois && d1.annee == d2.annee) || d1.annee < d2.annee) {
      int s = (d1.jour != 1) ? daysPerMonth(d1) - (d1.jour) + 1 : daysPerMonth(d1);

      d1.jour = 1;
      if (d1.mois == 12) {
        d1.mois = 1;
        d1.annee++;
      } else
        d1.mois++;

      return s + getDays(d1, d2);
    } else if (d1.mois == d2.mois)
      return d2.jour - d1.jour;

    return -1;
  }
  return -1;
}
//Verifier si une date est comprise entre 2 dates (d1 <= d < d2)
int isBetween2Dates(Date d, Date d1, Date d2) {
  return (isGreaterThan(d1, d) || isEqualDate(d1, d)) && isGreaterThan(d, d2);
}
//Calculer l'intersection de 2 intervalles [debut, fin] et [d1, d2]
int getIntersection(Date d1, Date d2, Date debut, Date fin) {
  if (isGreaterThan(d2, d1) || isGreaterThan(fin, debut))
    return -1;

  int days = getDays(debut, fin);
  if (isGreaterThan(d2, debut) || isEqualDate(fin , d1))
    return 0;

  if (isBetween2Dates(d2, debut, fin)) {
    return isGreaterThan(debut, d1)
      ? getDays(d1, d2)
      : getDays(debut, d2);
  }
  if (isBetween2Dates(d1, debut, fin)) {
    return isGreaterThan(d2, fin)
      ? getDays(d1, d2)
      : getDays(d1, fin);
  }
}

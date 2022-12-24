#include <stdio.h>
#include <time.h>

#define _DATE_H 1

#define SAMEDI_ID   6
#define DIMANCHE_ID 0

#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define HOUR_PER_DAY 24

typedef struct date{
          int jour;
          int mois;
          int annee;
} Date;

#define _DATE_H 1


int isEqualDate(Date d1, Date d2) {
  return d1.annee == d2.annee && d1.mois == d2.mois && d1.jour == d2.jour;
}

/**
 * @brief Verifier si la date est vrai ou non
 *
 * @param date Date à verifier
 * @return int
 */
int valideDate(Date date) {
  return (date.jour > 0 && date.jour < 32)
    && (date.mois > 0 && date.mois < 13)
    && (date.annee > 1960);
}

/**
 * @brief Verifier si la 1ere date est inferieur à la 2eme date.
 *
 * @param d1 1ere Date
 * @param d2 2eme Date
 * @return int Retourne 1 si (d1 < d2), 0 sinon
 */
int isGreaterThan(Date d1, Date d2) {
  if (!valideDate(d1) || !valideDate(d2))
    return 0;

  return d1.annee < d2.annee || (d1.annee == d2.annee
    && (d1.mois < d2.mois || (d1.mois == d2.mois && d1.jour < d2.jour)));
}

/**
 * @brief Calculer le nombre de jours entre la date 1 et la date 2 (Date1 - Date2)
 *
 * @param d1 Date 1
 * @param d2 Date 2
 * @return int
 */
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

/**
 * @brief Saisir la date sous format (dd-mm-yy)
 *
 * @return Date
 */
Date saisirDate() {
  Date date;
  do {
    scanf("%d-%d-%d", &(date.jour), &(date.mois), &(date.annee));
  } while (!valideDate(date));
  return date;
}

Date strToDate(char* sDate) {
  Date date;
  sscanf(sDate, "%d-%d-%d", &(date.jour), &(date.mois), &(date.annee));
  return date;
}

/**
 * @brief Initialiser la Date
 *
 * @param j jour (compris entre 1 et 31)
 * @param m mois (compris entre 1 et 12)
 * @param a annee
 * @return Date
 */
Date initDate(int j, int m, int a) {
  Date d;
  d.jour = j;
  d.mois = m;
  d.annee = a;
  return d;
}

/**
 * @brief Afficher la Date sous forme dd-mm-yy
 *
 * @param date
 * @return int - Si la date n'est pas valide, retourne -1
 */
int printDate(Date date) {
  if (!valideDate(date)) {
    printf(" Date non valide !!! \n");
    return -1;
  }

  printf(" %d-%d-%d", date.jour, date.mois, date.annee);
  return 1;
}

/**
 * @brief Date d'aujourd'hui
 *
 * @return Date
 */
Date today() {
  time_t t;
  t = time(&t);
  struct tm* c = gmtime(&t);
  return (Date) {c->tm_mday, c->tm_mon + 1, c->tm_year + 1900};
}

/**
 * @brief Jour de la semaine, 0 à 6 (commençant par 0: dimanche)
 *
 * @return int
 */
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

/**
 * @brief Verifier si l'annee est une annee bissextile
 *
 * @param year L'annee à verifier
 * @return int
 */
int isLeapYear(int year) {
  return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

/**
 * @brief Nombre de jour par mois
 *
 * @param d Date
 * @return int
 */
int daysPerMonth(Date d) {
  if (d.mois == 2)
    return isLeapYear(d.annee) ? 28 : 29;
  int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  return *(days + d.mois - 1);
}

/**
 * @brief Calculer le nombre de jours entre 2 Dates, similaire à getDiffDays(Date, Date)
 * @param d1 1ere Date
 * @param d2 2eme Date
 * @return int
 */
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

/**
 * @brief Verifier si une date est comprise entre 2 dates (d1 <= d < d2)
 *
 * @param d
 * @param d1
 * @param d2
 * @return int
 */
int isBetween2Dates(Date d, Date d1, Date d2) {
  return (isGreaterThan(d1, d) || isEqualDate(d1, d)) && isGreaterThan(d, d2);
}

/**
 * @brief Calculer l'intersection de 2 intervalles [debut, fin] et [d1, d2]
 *
 * @param d1 D2
 * @param d2 D2
 * @param debut Debut
 * @param fin Fin
 * @return Si une des dates est invalide, -1 est retourne
 */
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


int comparer_dates_(Date d1, Date d2){
    if (d2.annee < d1.annee)
       return 0;
    else if (d2.annee > d1.annee)
       return 1;
    if (d2.annee == d1.annee)
    {
        if (d2.mois<d1.mois)
            return 0;
        else if (d2.mois>d1.mois)
            return 1;
        else if (d2.jour<d1.jour)
            return 0;
        else if(d2.jour>d1.jour)
            return 1;
        else
            return 1;
    }
}



int estEntre(Date debut, Date m, Date fin){
    return comparer_dates_(debut,m)&&comparer_dates_(m,fin);
}

//intersection =ensemble vide   =>  return 0
int intersection(Date d1, Date d2, Date d3, Date d4){
    return estEntre(d1,d3,d2) || estEntre(d1,d4,d2) || estEntre(d3,d1,d4) ;
}
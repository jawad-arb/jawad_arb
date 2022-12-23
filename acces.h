#ifndef ACCES_H_INCLUDED
#define ACCES_H_INCLUDED
#include<math.h>

//arroundissement si [x = 0.1] => 0, si [x = 0.8] => 1, si [x = 0.5] => 1

int arroundissement(double x) {
  double cX = ceil(x);
  return ( cX - x ) <= 0.5 ? cX : cX - 1;
}

//calcule le nombre de jour de congee basant sur les jour de travaille::

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





#endif // ACCES_H_INCLUDED

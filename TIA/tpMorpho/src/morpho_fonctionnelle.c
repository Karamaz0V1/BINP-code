
#include <it/mat.h>
#include "morpho_fonctionnelle.h"

  //---------------------------------------------------//
  //  MORPHOLOGIE FONCTIONNELLE
  //---------------------------------------------------//


// Cette fonction calcule la dilatation en NDG du pixel (i,j) de l'image im
// par rapport a l'element structurant masque

int applique_masque_dilatation_NDG( imat im, imat masque, int i, int j){

  // A COMPLETER
  return 0;
}

// Cette fonction calcule la dilatation en NDG de l'image im par l'element structurant
// masque.

imat dilatation_NDG( imat im, imat masque ){

  // A COMPLETER

  return imat_new_zeros(1,1);
}

// Cette fonction calcule l'erosion en NDG du pixel (i,j) de l'image im
// par rapport a l'element structurant masque

int applique_masque_erosion_NDG( imat im, imat masque, int i, int j){


  // A COMPLETER

  return 0;
}

// Cette fonction calcule l'erosion en NDG de l'image im par l'element structurant
// masque.

imat erosion_NDG( imat im, imat masque ){

 // A COMPLETER

  return imat_new_zeros(1,1);
}



#include <it/mat.h>
#include "traitements_morpho.h"

  //---------------------------------------------------//
  // TOUT OU RIEN ET SQUELETTISATION
  //---------------------------------------------------//

// Cette fonction renvoie 1 si le gabarit de la transformation en tout-ou-rien
// peut etre "placé" au pixel (i,j).
int ttourien(imat im, int i, int j, imat masque){

  // A COMPLETER
  return 0;
}


// Cette fonction calcule la transformee en tout-ou-rien de l'image im par l'element structurant
// masque.

imat toutourien( imat im, imat masque ){
	
	// A COMPLETER
	
	return imat_new_zeros(1,1);
}



// Squelettisation
imat squelette(imat im, imat * masques)
{
  // A COMPLETER

	return imat_new_zeros(1,1);
}


  //---------------------------------------------------//
  //  PROBLEME
  //---------------------------------------------------//


int nbCarres(imat im){
	
	// A COMPLETER
	
	return 0;
}



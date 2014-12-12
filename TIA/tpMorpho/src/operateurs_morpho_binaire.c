#include <it/mat.h>
#include "operateurs_morpho_binaire.h"


  //---------------------------------------------------//
  // EROSION ET DILATATION
  //---------------------------------------------------//



// Cette fonction renvoie 1 si le masque (element structurant) positionné au point
// (i,j) de l'image im "touche" im (intersection non vide). 
// Vous pourrez considérer que le centre de masque est son centre géométrique.

int applique_masque_dilatation( imat im, imat masque, int i, int j ){

  // A COMPLETER

  return 0;
}

// Cette fonction calcule la dilatation de l'image im par l'element structurant
// "masque". 
imat dilatation( imat im, imat masque ){

  // A COMPLETER

  return imat_new_zeros(1,1);
}


// Cette fonction renvoie 1 si le masque (element structurant) positionné au point
// (i,j) de l'image est entièrement inclu dans im. 
// Vous pourrez considérer que le centre de masque est son centre géométrique.

int applique_masque_erosion( imat im, imat masque, int i, int j ){


  // A COMPLETER

  return 0;
}


// Cette fonction calcule l'erosion de l'image im par l'element structurant
// masque.

imat erosion( imat im, imat masque ){

  // A COMPLETER

  return imat_new_zeros(1,1);
}



// Calcule la dilatation d'une image en utilisant
// la dualité avec l'érosion
imat dilatation_dual( imat im, imat masque ){
	
	// A COMPLETER
	
	return imat_new_zeros(1,1);
}	


// Calcule l'érosion d'une image en utilisant
// la dualité avec la dilatation
imat erosion_dual( imat im, imat masque ){
	
	// A COMPLETER
	
	return imat_new_zeros(1,1);
}	



  //---------------------------------------------------//
  // OUVERTURE ET FERMETURE
  //---------------------------------------------------//

// Cette fonction calcule l'ouverture de l'image im par l'element structurant
// masque.

imat ouverture( imat im, imat masque ){

  // A COMPLETER
  return imat_new_zeros(1,1);

}


// Cette fonction calcule la fermeture de l'image im par l'element structurant
// masque.
imat fermeture( imat im, imat masque ){

  // A COMPLETER
  return imat_new_zeros(1,1);

}


// Calcule l'ouverture d'une image en utilisant
// la dualité avec la fermeture
imat ouverture_dual( imat im, imat masque ){
	
	// A COMPLETER
	return imat_new_zeros(1,1);
	
}


// Calcule la fermeture d'une image en utilisant
// la dualité avec l'ouverture
imat fermeture_dual( imat im, imat masque ){
	
	// A COMPLETER
	return imat_new_zeros(1,1);
	
}
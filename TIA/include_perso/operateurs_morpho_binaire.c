#include <it/mat.h>
#include "operateurs_morpho_binaire.h"


  //---------------------------------------------------//
  // EROSION ET DILATATION
  //---------------------------------------------------//



// Cette fonction renvoie 1 si le masque (element structurant) positionné au point
// (i,j) de l'image im "touche" im (intersection non vide). 
// Vous pourrez considérer que le centre de masque est son centre géométrique.

int applique_masque_dilatation( imat im, imat masque, int i, int j ){
  int a,b;
  int deltaH=imat_height(masque)/2;
  int deltaW=imat_width(masque)/2;
  for(a=-deltaH;a<=deltaH;a++){
        for(b=-deltaW;b<=deltaW;b++){
		if(pasDepassement(im,i+a,j+b)) {	
			if(1==masque[a+deltaH][b+deltaW] && im[i+a][j+b]>=1)
				return 1;
		}
	}
  }

  return 0;
}


// Cette fonction calcule la dilatation de l'image im par l'element structurant
// "masque". 
imat dilatation( imat im, imat masque ){
  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_dilatation(im, masque, i, j)*255;
		}
	}
  return res;
}


// Cette fonction renvoie 1 si le masque (element structurant) positionné au point
// (i,j) de l'image est entièrement inclu dans im. 
// Vous pourrez considérer que le centre de masque est son centre géométrique.

int applique_masque_erosion( imat im, imat masque, int i, int j ){
  int a,b;
  int deltaH=imat_height(masque)/2;
  int deltaW=imat_width(masque)/2;
  for(a=-deltaH;a<=deltaH;a++){
        for(b=-deltaW;b<=deltaW;b++){
		if(pasDepassement(im,i+a,j+b)) {
			if(im[i+a][j+b]==0 && masque[a+deltaH][b+deltaW]==1)
				return 0;
		}
	}
  }
  return 1;
}


// Cette fonction calcule l'erosion de l'image im par l'element structurant
// masque.

imat erosion( imat im, imat masque ){
  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_erosion(im, masque, i, j)*255;
		}
	}
  return res;
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
  return dilatation(erosion(im,masque),masque);
}


// Cette fonction calcule la fermeture de l'image im par l'element structurant
// masque.
imat fermeture( imat im, imat masque ){
  return erosion(dilatation(im,masque),masque);

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

//Cette fonction renvoie 1 si les coordonnées ne sortent pas de l'image

int pasDepassement(imat im, int i, int j) {
	int h = imat_height(im);
	int w = imat_width(im);
	if(i>=0 && i<h && j>=0 && j<w)
		return 1;
	return 0;
}

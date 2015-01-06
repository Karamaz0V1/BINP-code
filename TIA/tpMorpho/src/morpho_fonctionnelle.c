
#include <it/mat.h>
#include "morpho_fonctionnelle.h"

  //---------------------------------------------------//
  //  MORPHOLOGIE FONCTIONNELLE
  //---------------------------------------------------//


// Cette fonction calcule la dilatation en NDG du pixel (i,j) de l'image im
// par rapport a l'element structurant masque

int applique_masque_dilatation_NDG( imat im, imat masque, int i, int j){
  int a,b,max;
  max=0;
  int deltaH=imat_height(masque)/2;
  int deltaW=imat_width(masque)/2;
  for(a=-deltaH;a<=deltaH;a++){
    for(b=-deltaW;b<=deltaW;b++){
        if(pasDepassement(im,i+a,j+b)) {	
            if(1==masque[a+deltaH][b+deltaW])
			    if(im[i+a][j+b]>max)
			        max=im[i+a][j+b];
		}
	}
  }
  
  return max;
}

// Cette fonction calcule la dilatation en NDG de l'image im par l'element structurant
// masque.

imat dilatation_NDG( imat im, imat masque ){

  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_dilatation_NDG(im, masque, i, j);
		}
	}
  return res;
}

// Cette fonction calcule l'erosion en NDG du pixel (i,j) de l'image im
// par rapport a l'element structurant masque

int applique_masque_erosion_NDG( imat im, imat masque, int i, int j){

  int a,b,min;
  min=255;
  int deltaH=imat_height(masque)/2;
  int deltaW=imat_width(masque)/2;
  for(a=-deltaH;a<=deltaH;a++){
        for(b=-deltaW;b<=deltaW;b++){
		if(pasDepassement(im,i+a,j+b)) {
			if(masque[a+deltaH][b+deltaW]==1)
				if(im[i+a][j+b]<min)
				    min=im[i+a][j+b];
		}
	}
  }
  return min;
}

// Cette fonction calcule l'erosion en NDG de l'image im par l'element structurant
// masque.

imat erosion_NDG( imat im, imat masque ){

  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_erosion_NDG(im, masque, i, j);
		}
	}
  return res;
}

#include <it/mat.h>
#include "traitements_morpho.h"

  //---------------------------------------------------//
  // TOUT OU RIEN ET SQUELETTISATION
  //---------------------------------------------------//

// Cette fonction renvoie 1 si le gabarit de la transformation en tout-ou-rien
// peut etre "placé" au pixel (i,j).
int ttourien(imat im, int i, int j, imat masque){

  int a,b;
  int deltaH=imat_height(masque)/2;
  int deltaW=imat_width(masque)/2;
  for(a=-deltaH;a<=deltaH;a++){
        for(b=-deltaW;b<=deltaW;b++){
		if(pasDepassement(im,i+a,j+b)) {
		    if(masque[a+deltaH][b+deltaW]==128)
		        continue;	
			if(masque[a+deltaH][b+deltaW]==0 && im[i+a][j+b]>=1)
			    return 0;
			if(masque[a+deltaH][b+deltaW]==255 && im[i+a][j+b]==0)
			    return 0;
		}
	}
  }
  return 1;
}


// Cette fonction calcule la transformee en tout-ou-rien de l'image im par l'element structurant
// masque.

imat toutourien( imat im, imat masque ){

  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=ttourien(im,i,j,masque)*255;
		}
	}
  return res;
}



// Squelettisation
imat squelette(imat im, imat * masques)
{
  imat res = imat_clone(im);
  imat tmp = imat_clone(im);
  int i;
  int nbIter=0;
  do {
    nbIter++;
    printf("%d \n",nbIter);
    imat_copy(tmp,res);
    for(i=0;i<8;i++) {
        res = toutourien(res,masques[i]);
    }
   } while(!imat_eq(res,tmp) && nbIter<1);
  printf("Nb iter : %d",nbIter);
  imat_delete(tmp);
  return res;
}


  //---------------------------------------------------//
  //  PROBLEME
  //---------------------------------------------------//


int nbCarres(imat im){
	
	return 0;
}


#include <it/mat.h>
#include "traitements_morpho.h"
#include <it/io.h>
#include <it/parser.h>
#include "operateurs_morpho_binaire.h"
#include "morpho_fonctionnelle.h"

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
		if(pasDepassement(im,i+a,j+b)==0) {
		    if(masque[a+deltaH][b+deltaW]==255)
                return 0;
        }
		else if(masque[a+deltaH][b+deltaW]==0 && im[i+a][j+b]!=0)
		    return 0;
		else if(masque[a+deltaH][b+deltaW]==255 && im[i+a][j+b]==0)
            return 0;
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
            if(ttourien(im,i,j,masque)==1)
                res[i][j]=0;
		}
	}
  return res;
}



// Squelettisation
imat squelette(imat im, imat * masques)
{
  printf("Squelette\n");
  imat res = imat_clone(im);
  imat tmp = imat_clone(im);
  int i;
  int nbIter=0;
  while(1) {
    nbIter++;
    printf("%d \n",nbIter);
    for(i=0;i<8;i++) {
        res = toutourien(res,masques[i]);
    }
    if(imat_eq(res,tmp))
        break;
    imat_copy(tmp,res);
   }
  printf("Nb iter : %d",nbIter);
  imat_delete(tmp);
  return res;
}


  //---------------------------------------------------//
  //  PROBLEME
  //---------------------------------------------------//


int nbCarres(imat im){
	int res = 0;
	parser_t * parser = parser_init( 0, NULL,  /* Command line arguments */
									"tp_morpho.param", /* Parameter file    */
									NULL );      /* Default arguments */

	imat masques[8];
	masques[0] = parser_get_imat( parser, "es1" );
	masques[1] = parser_get_imat( parser, "es2" );
	masques[2] = parser_get_imat( parser, "es3" );
	masques[3] = parser_get_imat( parser, "es4" );
	masques[4] = parser_get_imat( parser, "es5" );
	masques[5] = parser_get_imat( parser, "es6" );
	masques[6] = parser_get_imat( parser, "es7" );
	masques[7] = parser_get_imat( parser, "es8" );
	
	im = squelette(im,masques);
	imat_pgm_write("../results/out.pgm",im);
	return res;
}

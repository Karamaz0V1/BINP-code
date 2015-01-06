#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>
#include "operateurs_morpho_binaire.h"
#include "traitements_morpho.h"
#include "morpho_fonctionnelle.h"
// include the header file of your functions from tpFiltrage


////////////////////////////////////////////////
//
//			EVALUATION TP
//
////////////////////////////////////////////////
//
//	NOMS-PRENOMS :
// - BECKER FREDERIC
// - GUIOTTE FLORENT
//
////////////////////////////////////////////////




void affiche(imat im){
	int i,j;
	printf("\n ");
    for(i=0;i<imat_height(im);i++){
        for(j=0;j<imat_width(im);j++){
            printf("%d ",im[i][j]);
        }
		printf("\n ");
    }
}

imat gradient_morpho_NDG(imat im, imat es) {
  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_dilatation_NDG(im, es, i, j)-applique_masque_erosion_NDG(im, es, i, j);
		}
	}
  return res;
}

imat laplacien_morpho_NDG(imat im, imat es) {
  imat res = imat_clone(im);
  int i,j;
	for(i=0;i<imat_height(im);i++) {
		for(j=0;j<imat_width(im);j++) {
			res[i][j]=applique_masque_dilatation_NDG(im, es, i, j)+applique_masque_erosion_NDG(im, es, i, j)-2*im[i][j];
		}
	}
  return res;
}

int q1(imat es) {
   imat im1=imat_pgm_read("../images/circuit_nb.pgm");
	if(im1==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	//fermeture NDG
	imat ferm=erosion_NDG(dilatation_NDG(im1,es),es);
	imat_pgm_write("../results/fermeture.pgm",ferm);
	//ouverture NDG
	imat ouvr=dilatation_NDG(erosion_NDG(im1,es),es);
   imat_pgm_write("../results/ouverture.pgm",ouvr);
   
   imat_delete(im1);
   imat_delete(ferm);
	imat_delete(ouvr);
   return 1;
}

int q2morpho(imat es) {
   imat tro0=imat_pgm_read("../images/trotro_00.pgm");
	if(tro0==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	imat tro1=imat_pgm_read("../images/trotro_01.pgm");
	if(tro1==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	imat tro2=imat_pgm_read("../images/trotro_02.pgm");
	if(tro2==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	//trotro00
   imat grad0=gradient_morpho_NDG(tro0,es);
   imat_pgm_write("../results/grad_morpho0.pgm",grad0);
   //trotro01
   imat grad1=gradient_morpho_NDG(tro1,es);
   imat_pgm_write("../results/grad_morpho1.pgm",grad1);
   //trotro02
   imat grad2=gradient_morpho_NDG(tro2,es);
   imat_pgm_write("../results/grad_morpho2.pgm",grad2);
   
   imat_delete(tro0);
   imat_delete(tro1);
   imat_delete(tro2);
   imat_delete(grad0);
   imat_delete(grad1);
   imat_delete(grad2);
   
   return 1;
}

int q3morpho(imat es) {
   imat tro0=imat_pgm_read("../images/trotro_00.pgm");
	if(tro0==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	imat tro1=imat_pgm_read("../images/trotro_01.pgm");
	if(tro1==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	imat tro2=imat_pgm_read("../images/trotro_02.pgm");
	if(tro2==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
   imat lapl0=imat_rescale_value(laplacien_morpho_NDG(tro0,es));
   imat_pgm_write("../results/lapl_morpho0.pgm",lapl0);
   imat lapl1=imat_rescale_value(laplacien_morpho_NDG(tro1,es));
   imat_pgm_write("../results/lapl_morpho1.pgm",lapl1);
   imat lapl2=imat_rescale_value(laplacien_morpho_NDG(tro2,es));
   imat_pgm_write("../results/lapl_morpho2.pgm",lapl2);
   
   imat_delete(tro0);
   imat_delete(tro1);
   imat_delete(tro2);
   imat_delete(lapl0);
   imat_delete(lapl1);
   imat_delete(lapl2);
   
   return 1;
}



  //---------------------------------------------------//
  // PROGRAMME PRINCIPAL
  //---------------------------------------------------//

int main( int argc, char ** argv )
{
	parser_t * parser = parser_init( argc, argv,  /* Command line arguments */
									"tp_eval.param", /* Parameter file    */
									NULL );      /* Default arguments */
	imat es1      = parser_get_imat( parser, "es_q1" );
   
   q1(es1);
   q2morpho(es1); //gradient morphologique = dilatation(im) - erosion(im)
   q3morpho(es1); //laplacien morpho = dilatation(im) + erosion(im) - 2*im

   imat_delete(es1);
	
	
	return 0;
}
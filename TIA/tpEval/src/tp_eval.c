#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>
#include "operateurs_morpho_binaire.h"
#include "traitements_morpho.h"
#include "morpho_fonctionnelle.h"
#include "mati_utils.h"

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


parser_t * parser;

int q34_laplacien_diff() {
    /*** PARTIE LAPLACIEN ***/
	
	// lecture image
	imat im0 = imat_pgm_read("../images/trotro_00.pgm");
	imat im1 = imat_pgm_read("../images/trotro_01.pgm");
	imat im2 = imat_pgm_read("../images/trotro_02.pgm");

	if(im0==NULL || im1==NULL || im2==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	printf("height(im0) = %d\tmaxheight(im0) = %d\nwidth(im0) = %d\tmaxwidth(im0) = %d\n", imat_height (im0), imat_height_max (im0), imat_width (im0), imat_width_max (im0));	 
	
	// sauvegarde
	imat_pgm_write("out0.pgm",im0);
	imat_pgm_write("out1.pgm",im1);
	imat_pgm_write("out2.pgm",im2);
  
  //---------------------------------------------------//
  // filtrage bidimensionnel d'une image avec un filtre separable
  //---------------------------------------------------//
  imat gauss = parser_get_imat( parser, "gaussien" );
  //imat resg2 = filtrage_bidimensionnel(im2,gauss);
  //imat_pgm_write("gaussien2.pgm",resg2);

  imat moy = parser_get_imat( parser, "moyenne" );
  imat resg2 = filtrage_bidimensionnel(im2,moy);
  imat_pgm_write("moyenne2.pgm",resg2);

  imat croix = parser_get_imat( parser, "croix" );
  imat am1 = erosion_NDG(dilatation_NDG(im1,croix),croix);
  imat am2 = dilatation_NDG(erosion_NDG(am1,croix),croix);
  imat_pgm_write("ouverturefermeture2.pgm",am2);
  //////////////////////////////////////////////////////
  //  CONTOURS
  //---------------------------------------------------//

  //---------------------------------------------------//
  // Filtre Laplacien
  //---------------------------------------------------//
  imat laplacien = parser_get_imat( parser, "laplacien" );

  imat resl0 = filtrage_bidimensionnel_inseparable(im0,laplacien);
  imat resl1 = filtrage_bidimensionnel_inseparable(am2,laplacien);
  imat resl2 = filtrage_bidimensionnel_inseparable(resg2,laplacien);
  //imat reslc = imat_coeff(resl,1.0/8);

  imat reslcr0 = imat_rescale_value(resl0);
  imat reslcr1 = imat_rescale_value(resl1);
  imat reslcr2 = imat_rescale_value(resl2);
  imat_pgm_write("laplacien0.pgm",reslcr0);
  imat_pgm_write("laplacien1.pgm",reslcr1);
  imat_pgm_write("laplacien2.pgm",reslcr2);

  imat reslcz0 = imat_zero(resl0, 400);
  imat_pgm_write("laplacien_contour0.pgm",reslcz0);

  imat reslcz1 = imat_zero(resl1, 400);
  imat_pgm_write("laplacien_contour1.pgm",reslcz1);

  imat reslcz2 = imat_zero(resl2, 500);
  imat_pgm_write("laplacien_contour2.pgm",reslcz2);


  imat_delete(reslcz0);
  imat_delete(reslcz1);
  imat_delete(reslcz2);

  imat_delete(reslcr0);
  imat_delete(reslcr1);
  imat_delete(reslcr2);
  //imat_delete(reslc);
  imat_delete(resl0);
  imat_delete(resl1);
  imat_delete(resl2);
  imat_delete(laplacien);

  imat_delete(resg2);

  // desallocation
  imat_delete(im0);
  imat_delete(im1);
  imat_delete(im2);
  /*** FIN PARTIE LAPLACIEN ***/


  return 0;
}

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
	imat_pgm_write("fermeture.pgm",ferm);
	//ouverture NDG
	imat ouvr=dilatation_NDG(erosion_NDG(im1,es),es);
   imat_pgm_write("ouverture.pgm",ouvr);
   
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
   imat_pgm_write("grad_morpho0.pgm",grad0);
   //trotro01
   imat grad1=gradient_morpho_NDG(tro1,es);
   imat_pgm_write("grad_morpho1.pgm",grad1);
   //trotro02
   imat grad2=gradient_morpho_NDG(tro2,es);
   imat_pgm_write("grad_morpho2.pgm",grad2);
   
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
   imat_pgm_write("lapl_morpho0.pgm",lapl0);
   imat lapl1=imat_rescale_value(laplacien_morpho_NDG(tro1,es));
   imat_pgm_write("lapl_morpho1.pgm",lapl1);
   imat lapl2=imat_rescale_value(laplacien_morpho_NDG(tro2,es));
   imat_pgm_write("lapl_morpho2.pgm",lapl2);
   
   imat_delete(tro0);
   imat_delete(tro1);
   imat_delete(tro2);
   imat_delete(lapl0);
   imat_delete(lapl1);
   imat_delete(lapl2);
   
   return 1;
}

int q5() {
	// lecture image
	imat im = imat_pgm_read("../images/trotro_00.pgm");

	if(im==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	
	// sauvegarde
	imat_pgm_write("out.pgm",im);
  
  mat h1 = parser_get_mat( parser, "h1" );
  mat h2 = parser_get_mat( parser, "h2" );
  mat h3 = parser_get_mat( parser, "h3" );

  imat ih1 = fltrage_bidimensionnel_inseparable(im,h1);
  imat ih2 = fltrage_bidimensionnel_inseparable(im,h2);
  imat ih3 = fltrage_bidimensionnel_inseparable(im,h3);

  imat_pgm_write("ih1.pgm",ih1);
  imat_pgm_write("ih2.pgm",ih2);
  imat_pgm_write("ih3.pgm",ih3);

  imat_sub(ih1,ih2);

  imat cih = imat_clamp(ih1);
  imat_pgm_write("ih1ih2.pgm",cih);

  mat_delete(h1);
  mat_delete(h2);
  mat_delete(h3);
  imat_delete(cih);
  imat_delete(ih1);
  imat_delete(ih2);
  imat_delete(ih3);
  imat_delete(im);

  return 0;
}
  //---------------------------------------------------//
  // PROGRAMME PRINCIPAL
  //---------------------------------------------------//

int main( int argc, char ** argv )
{
	parser = parser_init( argc, argv,  /* Command line arguments */
									"tp_eval.param", /* Parameter file    */
                                    NULL ); /* Default arguments */

	imat es1      = parser_get_imat( parser, "es_q1" );
   
   q1(es1);
   q2morpho(es1); //gradient morphologique = dilatation(im) - erosion(im)
   q3morpho(es1); //laplacien morpho = dilatation(im) + erosion(im) - 2*im
 q34_laplacien_diff();
    q5();
   imat_delete(es1);
	
	
	return 0;
}

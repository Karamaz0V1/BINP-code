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
// -
// - 
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
}
  //---------------------------------------------------//
  // PROGRAMME PRINCIPAL
  //---------------------------------------------------//

int main( int argc, char ** argv )
{
	parser = parser_init( argc, argv,  /* Command line arguments */
									"tp_eval.param", /* Parameter file    */
									NULL );      /* Default arguments */
    q34_laplacien_diff();
    q5();
  return 0;
}

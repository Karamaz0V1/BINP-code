#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>


imat filtrage_monodimensionnel(imat image, imat filtre) {
    int i, j, j_f;
    imat tmp = imat_clone(image);
    int offset = imat_width(filtre)/2;

    int coeff = 0;
    for (j=0; j<imat_width(filtre); j++)
        coeff+=filtre[0][j];

    for (i=0; i<imat_height(image); i++)
        for (j=offset; j<imat_width(image)-offset; j++) {
            int value = 0;
            for (j_f=0; j_f<imat_width(filtre); j_f++) {
                value+=image[i][j+j_f-offset] * filtre[0][j_f];
            }
            tmp[i][j] = value / coeff;
        }

    return tmp;
}

imat filtrage_bidimensionnel(imat image, imat filtre) {
    imat tmp = filtrage_monodimensionnel(image, filtre);
    imat transpose = imat_new_transpose(tmp);
    filtrage_monodimensionnel(transpose, filtre);
    imat res = imat_new_transpose(transpose);
    imat_delete(transpose);
    imat_delete(tmp);
    return res;
}

int main( int argc, char ** argv )
{
	parser_t * parser = parser_init( argc, argv,  /* Command line arguments */
									"tp_filtrage.param", /* Parameter file    */
									NULL );      /* Default arguments */
	
	
	imat imtest          = parser_get_imat( parser, "i_m" );
	imat filtre      = parser_get_imat( parser, "filtre" );
	
	int i,j;
	
	// lecture image
	imat im = imat_pgm_read("../images/alpes.pgm");
	if(im==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	printf("height(im) = %d\tmaxheight(im) = %d\nwidth(im) = %d\tmaxwidth(im) = %d\n", imat_height (im), imat_height_max (im), imat_width (im), imat_width_max (im));	 
	
	// sauvegarde
	imat_pgm_write("out.pgm",im);
  
  //---------------------------------------------------//
  // AMELIORATION
  //---------------------------------------------------//

  
  
  //---------------------------------------------------//
  // filtrage bidimensionnel d'une image avec un filtre separable
  //---------------------------------------------------//

  imat gauss          = parser_get_imat( parser, "gaussien" );

  imat res = filtrage_monodimensionnel(im,gauss);


  imat_pgm_write("gaussien.pgm",res);

  //---------------------------------------------------//
  // filtrage d'une image avec un filtre moyenneur
  //---------------------------------------------------//


  //---------------------------------------------------//
  // accentuation des contours d'une image par simple filtrage
  //---------------------------------------------------//


  //---------------------------------------------------//
  // accentuation des contours d'une image pretraitee
  //---------------------------------------------------//


  //////////////////////////////////////////////////////
  //  CONTOURS
  //---------------------------------------------------//

	//---------------------------------------------------//
   // Filtre de Sobel 
   //---------------------------------------------------//  

  //---------------------------------------------------//
  // Filtre Laplacien
  //---------------------------------------------------//




  // desallocation
  imat_delete(im);
  imat_delete(imtest);
  imat_delete(filtre);
  imat_delete(res);
  imat_delete(gauss);

  return 0;
}

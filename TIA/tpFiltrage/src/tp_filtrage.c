#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>


void filtrage_monodimensionnel(imat & image, const imat & filtre) {
    imat tmp = imat_clone(image);
    for (int i=0; i<imat_height(image); i++)
        for (int j=0; j<imat_width(image); j++) {
            int value = 0;
            for (int j_f=0; j_f<imat_width(filtre); j_f++)
                value+=tmp[i][j+j_f-(imat_width(filtre)/2)] * filtre[0][j_f];
            image[i][j] = value;
        }
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

  return 0;
}

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
            for (j_f=0; j_f<imat_width(filtre); j_f++)
                value+=image[i][j+j_f-offset] * filtre[0][j_f];
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

int clamp(int val) {
    if (val > 255)
        return 255;
    else
        return val;
}

imat filtrage_bidimensionnel_inseparable(imat image, imat filtre) {
    int i, j, i_f, j_f;
    imat tmp = imat_clone(image);
    int offset = imat_width(filtre)/2;

    int coeff = 0;
    for (i=0; i<imat_height(filtre); i++)
        for (j=0; j<imat_width(filtre); j++)
            coeff+=filtre[i][j];
    if (coeff==0) coeff = 1;

    for (i=offset; i<imat_height(image)-offset; i++)
        for (j=offset; j<imat_width(image)-offset; j++) {
            int value = 0;
            for (i_f=0; i_f<imat_height(filtre); i_f++)
                for (j_f=0; j_f<imat_width(filtre); j_f++)
                    value+=image[i+i_f-offset][j+j_f-offset] * filtre[i_f][j_f];
            tmp[i][j] = clamp(value / coeff);
        }

    return tmp;
}

imat imat_coeff(imat image, float coeff) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = image[i][j] * coeff;
    return tmp;
}

imat imat_abs(imat image) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = abs(image[i][j]);
    return tmp;
}

imat imat_add_clamp(imat image1, imat image2) {
    int i, j;
    imat tmp = imat_clone(image1);
    for (i=0; i<imat_height(image1); i++)
        for (j=0; j<imat_width(image1); j++)
            tmp[i][j] = clamp(image1[i][j] + image2[i][j]);
    return tmp;
}

imat imat_rescale_value(imat image) {
    //TODO
    int i, j;
    int min = imat_min(image);
    int max = imat_max(image);
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = abs(image[i][j]);
    return tmp;
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
	imat im = imat_pgm_read("../images/journal1_394.pgm");
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
  imat gauss = parser_get_imat( parser, "gaussien" );
  imat resg = filtrage_bidimensionnel(im,gauss);
  imat_pgm_write("gaussien.pgm",resg);
  imat_delete(resg);

  //---------------------------------------------------//
  // filtrage d'une image avec un filtre moyenneur
  //---------------------------------------------------//
  imat moy = parser_get_imat( parser, "moyenneur" );
  imat resm = filtrage_bidimensionnel(im,moy);
  imat_pgm_write("moyenne.pgm",resm);
  imat_delete(resm);
  imat_delete(moy);

  //---------------------------------------------------//
  // accentuation des contours d'une image par simple filtrage
  //---------------------------------------------------//
  imat rehauss = parser_get_imat( parser, "rehauss" );
  imat resr = filtrage_bidimensionnel_inseparable(im,rehauss);
  imat_pgm_write("rehaussement.pgm",resr);

  //---------------------------------------------------//
  // accentuation des contours d'une image pretraitee
  //---------------------------------------------------//

  resg = filtrage_bidimensionnel(im,gauss);
  imat resrg = filtrage_bidimensionnel_inseparable(resg,rehauss);
  imat_pgm_write("passsebas_rehaussement.pgm",resrg);

  imat_delete(resr);
  imat_delete(resrg);
  imat_delete(resg);
  imat_delete(rehauss);
  imat_delete(gauss);

  //////////////////////////////////////////////////////
  //  CONTOURS
  //---------------------------------------------------//

  //---------------------------------------------------//
  // Filtre de Sobel 
  //---------------------------------------------------//  
  imat sobelh = parser_get_imat( parser, "sobelh" );
  imat sobelv = parser_get_imat( parser, "sobelv" );
  imat ressh = filtrage_bidimensionnel_inseparable(im,sobelh);
  imat ressv = filtrage_bidimensionnel_inseparable(im,sobelv);
  imat ressha = imat_abs(ressh);
  imat ressva = imat_abs(ressv);
  imat sobel = imat_add_clamp(ressha,ressva);
  imat_pgm_write("sobelh.pgm",ressha);
  imat_pgm_write("sobelv.pgm",ressva);
  imat_pgm_write("sobel.pgm",sobel);

  imat_delete(sobel);
  imat_delete(ressha);
  imat_delete(ressva);
  imat_delete(ressh);
  imat_delete(ressv);
  imat_delete(sobelv);
  imat_delete(sobelh);

  //---------------------------------------------------//
  // Filtre Laplacien
  //---------------------------------------------------//
  imat laplacien = parser_get_imat( parser, "laplacien" );
  imat resl = filtrage_bidimensionnel_inseparable(im,laplacien);
  imat reslc = imat_coeff(resl,1.0/8);
  imat_pgm_write("laplacien.pgm",reslc);

  imat_delete(resl);
  imat_delete(laplacien);



  // desallocation
  imat_delete(im);
  imat_delete(imtest);
  imat_delete(filtre);

  return 0;
}

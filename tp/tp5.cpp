/****************************************************************************
 * Copyright (C) 2010 Universite de Rennes 1. All rights reserved.
 *
 * This software was developed at:
 * Universite de Rennes 1
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 *
 * This file uses the ViSP library.
*****************************************************************************/

/****************************************************************************
 * NOMS - PRENOMS:
 *  -
 *	-
 * 
 * Date :
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;

void decimation_lineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++)
            Is[i][j] = I[i*2][j*2];
    I = Is;
}

void test_decimation_lineaire() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/baboon.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_lineaire(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Image decimee lineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
    vpDisplay::getClick(I);
}

void decimation_bilineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++) {
            Is[i][j].R = (I[i*2][j*2].R+I[i*2+1][j*2].R+I[i*2][j*2+1].R+I[i*2+1][j*2+1].R) / 4;   
            Is[i][j].G = (I[i*2][j*2].G+I[i*2+1][j*2].G+I[i*2][j*2+1].G+I[i*2+1][j*2+1].G) / 4;   
            Is[i][j].B = (I[i*2][j*2].B+I[i*2+1][j*2].B+I[i*2][j*2+1].B+I[i*2+1][j*2+1].B) / 4;   
        }

    I = Is;
}

void test_decimation_bilineaire() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/baboon.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_bilineaire(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Image decimee bilineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
    vpDisplay::getClick(I);
}

void test_decimation() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/baboon.ppm") ;	
  	vpImage<vpRGBa>  I2;
    I2 = I;
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_lineaire(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Image decimee lineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_bilineaire(I2);
	vpDisplayX d2(I2,600,100) ;
	vpDisplay::setTitle(I2, "Image decimee bilineaire");
	vpDisplay::display(I2);
	vpDisplay::flush(I2) ;	
    vpDisplay::getClick(I2);

}

int main(int argc, char **argv)
{

  cout << "BINP TP 5 : REDUCTION ET AGRANDISSEMENT D'IMAGES " << endl ;
  cout << "--" << endl ;


	// creation du menu
    test_decimation();




  cout << "Fin du programme " << endl ;
  return(0);
}

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
 *  - Frédéric BECKER
 *	- Florent GUIOTTE
 * 
 * Date : oct 2014
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;

/** Réduit lataille de l'image en prenant une valeur sur 2 **/
void decimation_simple(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++)
            Is[i][j] = I[i*2][j*2];
    I = Is;
}

/** Réduit la taille de l'image en moyennant les valeurs d'origine **/
void decimation_lineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++) {
            Is[i][j].R = (I[i*2][j*2].R+I[i*2+1][j*2].R+I[i*2][j*2+1].R+I[i*2+1][j*2+1].R) / 4;   
            Is[i][j].G = (I[i*2][j*2].G+I[i*2+1][j*2].G+I[i*2][j*2+1].G+I[i*2+1][j*2+1].G) / 4;   
            Is[i][j].B = (I[i*2][j*2].B+I[i*2+1][j*2].B+I[i*2][j*2+1].B+I[i*2+1][j*2+1].B) / 4;   
        }

    I = Is;
}

/** Effectue un agrandissement en dupliquant les pixels de l'image d'origine **/
void agrandissement_simple(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()*2,I.getWidth()*2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++) {
            Is[i][j].R = I[i/2][j/2].R;
            Is[i][j].G = I[i/2][j/2].G;
            Is[i][j].B = I[i/2][j/2].B;
        }
    I = Is;
}

/** retourne le pixel aux coordonées i, j; en appliquant l'effet miroirs sur les bords
 *  de l'image quand les coordonnées sont trop grandes/petites. */
const vpRGBa & access(const vpImage<vpRGBa> & I, int i, int j) {
    if (i >= (int)I.getHeight()) i = 2 * I.getHeight() - i -1;
    if (j >= (int)I.getWidth()) j = 2 * I.getWidth() - j -1;
    return I[(int)abs(i)][(int)abs(j)];
}

/** Donne la valeur du pixel i, j après interpolation bilinéaire **/
vpRGBa interpol(const vpImage<vpRGBa> & src, int i, int j) {
    vpRGBa sortie;
    sortie.R = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).R * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).R * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).R * 0.25 + access(src,i/2,j/2).R * 0.75);
    sortie.G = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).G * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).G * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).G * 0.25 + access(src,i/2,j/2).G * 0.75);
    sortie.B = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).B * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).B * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).B * 0.25 + access(src,i/2,j/2).B * 0.75);
    return sortie;
}

/** Calcule l'agrandissement linéaire d'une image **/
void agrandissement_lineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()*2,I.getWidth()*2);
    for (int i=0; i<Is.getHeight(); i++) 
        for (int j=0; j<Is.getWidth(); j++)
            Is[i][j] = interpol(I, i, j);
    I = Is;
}

void test_decimation_simple() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/baboon.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_simple(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Image decimee lineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
    vpDisplay::getClick(I);
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

void test_decimation() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/baboon.ppm") ;	
  	vpImage<vpRGBa>  I2;
    I2 = I;
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_simple(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Réduction simple");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    decimation_lineaire(I2);
	vpDisplayX d2(I2,600,100) ;
	vpDisplay::setTitle(I2, "Réduction lineaire");
	vpDisplay::display(I2);
	vpDisplay::flush(I2) ;	
    vpDisplay::getClick(I2);
	vpImageIo::write(I,"./img/baboon_si.ppm") ;	
	vpImageIo::write(I2,"./img/baboon_bi.ppm") ;	
}

void test_agrandissement_simple() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/lena.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    agrandissement_simple(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Agrandissement lineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
    vpDisplay::getClick(I);
	vpImageIo::write(I,"./img/baboon_agli.ppm") ;	
}

void test_agrandissement_lineaire() {
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/lena.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    agrandissement_lineaire(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Agrandissement lineaire");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
    vpDisplay::getClick(I);
	vpImageIo::write(I,"./img/baboon_agbi.ppm") ;	
}

void test_agrandissement() {
  	vpImage<vpRGBa>  I, I2;
	vpImageIo::read(I,"../images/lena.ppm") ;	
    I2 = I;
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    agrandissement_simple(I);
	vpDisplayX d1(I,400,100) ;
	vpDisplay::setTitle(I, "Agrandissement simple");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    agrandissement_lineaire(I2);
	vpDisplayX d2(I2,900,100) ;
	vpDisplay::setTitle(I2, "Agrandissement lineaire");
	vpDisplay::display(I2);
	vpDisplay::flush(I2);	
    vpDisplay::getClick(I2);
	vpImageIo::write(I2,"./img/baboon_agbi.ppm") ;	
	vpImageIo::write(I,"./img/baboon_agsi.ppm") ;	
}

int main(int argc, char **argv)
{

  cout << "BINP TP 5 : REDUCTION ET AGRANDISSEMENT D'IMAGES " << endl ;
  cout << "--" << endl ;


	// creation du menu
	
	int choix=0;
	while(choix<3)
	{
		cout << "\n-------------------------------------" << endl;
		cout<<"1. Comparaison de la réduction d'image"<<endl;
		cout<<"2. Comparaison de l'agrandissement d'image"<<endl;
		cout<<"3. Quitter"<<endl;
		
		cin>>choix;
		cout << "-------------------------------------" << endl;
		
		switch(choix)
		{
			case 1 :
                test_decimation();
                break;
            case 2 :
                test_agrandissement();
                break;
			default :
				break;
		}
    }

    cout << "Fin du programme " << endl ;
    return(0);
}

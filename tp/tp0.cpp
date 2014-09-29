
/****************************************************************************
 *
 *
 * Copyright (C) 2010 Université de Rennes 1. All rights reserved.
 *
 * This software was developed at:
 * Universite de Rennes 1
 * Campus Universitaire de Beaulieu
 * 35042 Rennes Cedex
 *
 * This file uses the ViSP library.
 *
 
 *
 *****************************************************************************/


#include <iostream>

/*!
 tp0_exemple.cpp
 Ouverture, affichage et sauvegarde d'une image avec la librairie VISP
 
 */


#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;



int main(int argc, char **argv)
{
	/*
	// creation du menu
	
	cout << "BINP TP : EXEMPLE MANIPULATION IMAGE AVEC VISP " << endl ;
	cout << "--" << endl ;
	
	string sIm;
	unsigned int h, w;
	
	// lecture (interactive) d'une image en niveau de gris
	vpImage<unsigned char>  I1(384,384);

	// On fait des carrés
	for (int i=0; i<384/2; i++) 
		for (int j=0; j<384; j++){
			I1[i][j]=128;
		}

	for (int i=384/2; i<384; i++) 
		for (int j=0; j<384; j++){
			I1[i][j]=244;
		}

	for (int i=(384/2-64)/2; i<(384/2-64)/2+64; i++) 
		for (int j=(384/2-64)/2; j<(384/2-64)/2+64; j++) {
			I1[i][j]=130;
		}

	for (int i=(384/2-64)/2; i<(384/2-64)/2+64; i++) 
		for (int j=(384/2-64)/2+64*3; j<(384/2-64)/2+64*4; j++) {
			I1[i][j]=132;
		}

	for (int i=(384/2-64)/2+64*3; i<(384/2-64)/2+64*4; i++) 
		for (int j=(384/2-64)/2; j<(384/2-64)/2+64; j++) {
			I1[i][j]=246;
		}

	for (int i=(384/2-64)/2+64*3; i<(384/2-64)/2+64*4; i++) 
		for (int j=(384/2-64)/2+64*3; j<(384/2-64)/2+64*4; j++) {
			I1[i][j]=240;
		}

	vpDisplayX d1(I1,100,100) ;
	vpDisplay::setTitle(I1, "Image n.d.g.");
	vpDisplay::display(I1);
	vpDisplay::flush(I1) ;	
	vpDisplay::getClick(I1);

	*/

	// Partie perception des couleurs
	vpImage<vpRGBa>  I1(384,384);
	vpImage<vpRGBa>  I2(384,384);
	vpImage<vpRGBa>  I3(384,384);
	
	int x;
	cout << "Contraste x : " ;
	cin >> x;

	for (int i=0; i<384; i++) 
		for (int j=0; j<384; j++) {
			I1[i][j].R=128;
			I2[i][j].G=128;
			I3[i][j].B=128;
		}

	for (int i=(384-64)/2; i<(384-64)/2+64; i++) 
		for (int j=(384-64)/2; j<(384-64)/2+64; j++) {
			I1[i][j].R=128+x;
			I2[i][j].G=128+x;
			I3[i][j].B=128+x;
		}

	vpDisplayX d1(I1,100,100) ;
	vpDisplayX d2(I2,100,600) ;
	vpDisplayX d3(I3,600,100) ;
	vpDisplay::display(I1);
	vpDisplay::flush(I1) ;	
	vpDisplay::display(I2);
	vpDisplay::flush(I2) ;	
	vpDisplay::display(I3);
	vpDisplay::flush(I3) ;	
	vpDisplay::getClick(I1);



	vpImage<unsigned char>  I4(384,256,255);
	for (int i=188; i<196; i++) 
		for (int j=0; j<256; j++)
            I4[i][j] = 128;

	vpImage<unsigned char>  I5(384,256);
	for (int i=0; i<188; i++) 
		for (int j=0; j<256; j++)
            I5[i][j] = j;
	for (int i=188; i<196; i++) 
		for (int j=0; j<256; j++)
            I5[i][j] = 128;
	for (int i=196; i<384; i++) 
		for (int j=0; j<256; j++)
            I5[i][j] = j;

	vpDisplayX d4(I4,100,100) ;
	vpDisplayX d5(I5,500,100) ;
	vpDisplay::display(I4);
	vpDisplay::flush(I4) ;	
	vpDisplay::display(I5);
	vpDisplay::flush(I5) ;	
	vpDisplay::getClick(I4);

	vpImage<unsigned char>  I6(290,360,228);

	for (int i=0; i<290; i++) {
		for (int j=0; j<60; j++)
            I6[i][j] = 102;
		for (int j=60; j<120; j++)
            I6[i][j] = 127;
		for (int j=120; j<180; j++)
            I6[i][j] = 152;
		for (int j=180; j<240; j++)
            I6[i][j] = 178;
		for (int j=240; j<300; j++)
            I6[i][j] = 202;
    }

	vpDisplayX d6(I6,500,100) ;
	vpDisplay::display(I6);
	vpDisplay::flush(I6);
	vpDisplay::getClick(I6);

	vpImage<unsigned char> I7(168,168,255);

    for (int I=8; I<168; I+=40)
        for (int J=8; J<168; J+=40)
            for (int i=0; i<32; i++)
                for (int j=0; j<32; j++)
                    I7[i+I][j+J] = 0;

	vpDisplayX d7(I7,100,100) ;
	vpDisplay::display(I7);
	vpDisplay::flush(I7);
	vpDisplay::getClick(I7);

	return 0;
/*
	
	// lecture (interactive) d'une image couleur
	vpImage<vpRGBa>  I2;
	cout << "Nom de l'image (couleur) : ";
	cin >> sIm; // Ex: ../images/lena.pgm	
	vpImageIo::read(I2,sIm) ;
	
	h=I2.getHeight(); w=I2.getWidth();
	
	cout << "Lecture " << sIm << " (" << h << ", " << w << ")" << endl;
	
	vpDisplayX d2(I2,500,100) ;
	vpDisplay::setTitle(I2, "Image couleur");
	vpDisplay::display(I2);
	vpDisplay::flush(I2) ;	
	vpDisplay::getClick(I2);
	
	// modification et sauvegarde de l'image
	for (int i=50; i<=150; i++) 
		for (int j=50; j<=150; j++){
			I2[i][j].R=0;
			I2[i][j].G=0;
			I2[i][j].B=0;
		}

	cout << "Sauvegarder l'image sous : ";
	cin >> sIm; // Ex: ../tp0_results/lena_modif.pgm	
	vpImageIo::write(I2,sIm) ;
		
	vpDisplay::close(I1) ;
	vpDisplay::close(I2) ;
	
	cout << "Fin du programme " << endl ;
	return(0);
*/
}

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
 *  - BECKER Frédéric
 *	- GUIOTTE Florent
 * 
 * Date : sept 2014
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;

// QUESTION 2 : LIMITE DE PERCEPTION VISUELLE
void question2()
{
    string sIm;
    vpImage<unsigned char>  I1(384,384);
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
    	cout << "Sauvegarder l'image sous : ";
	    cin >> sIm; // Ex: ../tp0_results/lena_modif.pgm	
	    vpImageIo::write(I1,sIm) ;
    	vpDisplay::close(I1);
    }
    
// QUESTION 3 : PERCEPTION DES COULEURS
void question3()
{
    string sIm;
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
	cout << "Sauvegarder les images sous : ";
	cin >> sIm;
	vpImageIo::write(I1,sIm) ;
	cin >> sIm;
    vpImageIo::write(I2,sIm) ;
    cin >> sIm;
    vpImageIo::write(I3,sIm) ;
    vpDisplay::close(I1);
    vpDisplay::close(I2);
    vpDisplay::close(I3);
}

// QUESTION 4 : ILLUSION DU GRADIENT
void question4()
{
    string sIm;
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
	cout << "Sauvegarder les images sous : ";
	cin >> sIm;	
	vpImageIo::write(I4,sIm) ;
	cin >> sIm;	
	vpImageIo::write(I5,sIm) ;
    vpDisplay::close(I4);
    vpDisplay::close(I5);
}

// QUESTION 5 : BANDES DE MACH
void question5()
{
    string sIm;
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
	cout << "Sauvegarder l'image sous : ";
	cin >> sIm;	
	vpImageIo::write(I6,sIm) ;
    vpDisplay::close(I6);
}

// QUESTION 6 : GRILLE DE HERMAN
void question6()
{
    string sIm;
    vpImage<unsigned char> I7(168,168,255);

    for (int I=8; I<168; I+=40)
        for (int J=8; J<168; J+=40)
            for (int i=0; i<32; i++)
                for (int j=0; j<32; j++)
                    I7[i+I][j+J] = 0;

	vpDisplayX d7(I7,100,100) ;
	vpDisplay::display(I7);
	vpDisplay::flush(I7);
	cout << "Sauvegarder l'image sous : ";
	cin >> sIm;	
	vpImageIo::write(I7,sIm) ;
    vpDisplay::close(I7);
}

// QUESTION 7 : EFFET DE MASQUAGE
void question7()
{
    string sIm;
    vpImage<unsigned char> I8(256,256);

    int lb, hb;

    cout<<"LB (-1 pour terminer) : ";
    cin>>lb;

    while (lb != -1) {
        cout<<"HB : ";
        cin>>hb;
        cout<<endl;

        for (int i=0; i<256; i++)
            for (int j=0; j<128; j++)
                I8[i][j] = 255;

        unsigned char valb;
        for (int j=128-lb/2; j<128+lb/2; j++) {
            if (I8[0][j] == 0) 
                valb = I8[0][j] + (rand() % hb);
            else
                valb = I8[0][j] - (rand() % hb);

            for (int i=0; i<256; i++)
                I8[i][j] = valb;
        }

        vpDisplayX d8(I8,100,100) ;
        vpDisplay::display(I8);
        vpDisplay::flush(I8);
        
        cout << "Sauvegarder l'image sous : ";
	    cin >> sIm;	
    	vpImageIo::write(I8,sIm) ;
        vpDisplay::close(I8);

        cout<<"LB (-1 pour terminer) : ";
        cin>>lb;
    }
}


int main(int argc, char **argv)
{

  cout << "BINP TP1 : PERCEPTION VISUELLE " << endl ;
  cout << "--" << endl ;


  // creation du menu
  int choix=0;
  while(choix<7) {

    cout << "1. Limite de perception visuelle" <<endl ;
    cout << "2. Perception des couleurs"<<endl;
	cout << "3. Illusion du gradient" << endl;
    cout << "4. Bandes de Mach"<<endl;
    cout << "5. Grille de Herman"<<endl;
    cout << "6. Effet de masquage"<<endl;
    cout << "7. Quitter"<<endl;

    cin >> choix ;

    switch(choix) {
    case 1:
      question2();
      break;

    case 2:
      question3();
      break;

    case 3:
      question4();
      break;

    case 4:
      question5();
      break;

    case 5:
      question6();
	  break;
	  
    case 6:
      question7();	  
	  
    default:
      break;
    }
  }

  cout << "Fin du programme " << endl ;
  return(0);
}
















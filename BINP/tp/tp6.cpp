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
 * Date : nov 2014
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;

float dec(float n) {
    return n - floor(n);
}

const uchar & access(const vpImage<uchar> & I, int i, int j) {
    if (i >= (int)I.getHeight()) i = 2 * I.getHeight() - i -1;
    if (j >= (int)I.getWidth()) j = 2 * I.getWidth() - j -1;
    return I[(int)abs(i)][(int)abs(j)];
}

uchar interpole(vpImage<uchar> &I, float i, float j) {
    uchar p1, p2, p3, p4, x1, x2;

    p1 = access(I,(int)floor(i),(int)floor(j));
    p2 = access(I,(int)floor(i),(int)floor(j)+1);
    p3 = access(I,(int)floor(i)+1,(int)floor(j));
    p4 = access(I,(int)floor(i)+1,(int)floor(j)+1);

    x1 = (1-dec(j)) * p1 + dec(j) * p2;
    x2 = (1-dec(j)) * p3 + dec(j) * p4;

    return (1-dec(i)) * x1 + dec(i) * x2;
}

void test() {
    cout<<"1.19 "<<dec(1.19)<<endl;
    cout<<"11.59 "<<dec(11.59)<<endl;
}

void RotationBasic(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    // Si l'image de destination est plus grande que celle d'origine on décale le centre avec offseti et offsetj
    int offseti = (D.getHeight() - I.getHeight()) / 2;
    int offsetj = (D.getWidth() - I.getWidth()) / 2;
    int a = I.getHeight() / 2;
    int b = I.getWidth() /2;
    for (int i=0; i<I.getHeight(); i++)
        for (int j=0; j<I.getWidth(); j++) {
            int ti = (i-a) * cos(alpha) - (j-b) * sin(alpha) + a;
            int tj = (i-a) * sin(alpha) + (j-b) * cos(alpha) + b;
            ti+=offseti;
            tj+=offsetj;
            if((tj>0) && (ti>0) && (ti<D.getHeight()) && (ti<D.getWidth())) D[ti][tj] = I[i][j];
        }
}

void RotationInvertedBasic(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    // Si l'image de destination est plus grande que celle d'origine on décale le centre avec offseti et offsetj
    int offseti = (D.getHeight() - I.getHeight()) / 2;
    int offsetj = (D.getWidth() - I.getWidth()) / 2;
    int a = I.getHeight() / 2;
    int b = I.getWidth() /2;
    for (int fi=0; fi<D.getHeight(); fi++)
        for (int fj=0; fj<D.getWidth(); fj++) {
            int i = fi - offseti;
            int j = fj - offsetj;
            int ti = (i-a) * cos(alpha) + (j-b) * sin(alpha) + a;
            int tj = - (i-a) * sin(alpha) + (j-b) * cos(alpha) + b;
            if((tj>0) && (ti>0) && (ti<I.getHeight()) && (tj<I.getWidth())) D[i+offseti][j+offsetj] = I[ti][tj];
        }

}

void RotationInvertedInterpolated(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    // Si l'image de destination est plus grande que celle d'origine on décale le centre avec offseti et offsetj
    int offseti = (D.getHeight() - I.getHeight()) / 2;
    int offsetj = (D.getWidth() - I.getWidth()) / 2;
    int a = I.getHeight() / 2;
    int b = I.getWidth() /2;
    for (int fi=0; fi<D.getHeight(); fi++)
        for (int fj=0; fj<D.getWidth(); fj++) {
            int i = fi - offseti;
            int j = fj - offsetj;
            float ti = (i-a) * cos(alpha) + (j-b) * sin(alpha) + a;
            float tj = - (i-a) * sin(alpha) + (j-b) * cos(alpha) + b;
            if((tj>0) && (ti>0) && (ti<I.getHeight()) && (tj<I.getWidth())) D[i+offseti][j+offsetj] = interpole(I,ti,tj);
        }
}

void testRotationBasic() {
  	vpImage<uchar>  I;
	vpImageIo::read(I,"../images/lena.pgm") ;	
    vpImage<uchar> D(I.getHeight()*2,I.getWidth()*2);
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    for (int i=0; i<1000; i++)
    RotationBasic(I,D,1*3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Rotation basique");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);

    vpImageIo::write(D,"./rb.pgm");
}

void testRotationInvertedBasic() {
  	vpImage<uchar>  I;
	vpImageIo::read(I,"../images/lena.pgm") ;	
    vpImage<uchar> D(I.getHeight()*2,I.getWidth()*2);
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    for (int i=0; i<1000; i++)
    RotationInvertedBasic(I,D,3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Rotation inverse basique");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);

    vpImageIo::write(D,"./rib.pgm");
}

void testRotationInvertedInterpolated() {
  	vpImage<uchar>  I;
	vpImageIo::read(I,"../images/lena.pgm") ;	
    vpImage<uchar> D(I.getHeight()*2,I.getWidth()*2);
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    for (int i=0; i<1000; i++)
    RotationInvertedInterpolated(I,D,3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Rotation inverse interpolee");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);

    vpImageIo::write(D,"./rii.pgm");
}
int main(int argc, char **argv)
{

  cout << "BINP TP 6 : REDUCTION ET AGRANDISSEMENT D'IMAGES " << endl ;
  cout << "--" << endl ;


	// creation du menu
    //test();
	
	int choix=0;
	while(choix<4)
	{
		cout << "\n-------------------------------------" << endl;
		cout<<"1. Rotation basique"<<endl;
		cout<<"2. Rotation inverse basique"<<endl;
		cout<<"3. Rotation inverse interpolée"<<endl;
		cout<<"4. Quitter"<<endl;
		
		cin>>choix;
		cout << "-------------------------------------" << endl;
		
		switch(choix)
		{
			case 1 :
                testRotationBasic();
                break;
            case 2 :
                testRotationInvertedBasic();
                break;
            case 3 :
                testRotationInvertedInterpolated();
                break;
			default :
				break;
		}
    }

  cout << "Fin du programme " << endl ;
  return(0);
}

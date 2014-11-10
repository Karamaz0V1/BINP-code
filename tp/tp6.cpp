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

uchar interpole(vpImage<uchar> I, float i, float j) {
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
    for (int i=0; i<I.getHeight(); i++)
        for (int j=0; j<I.getWidth(); j++) {
            int ti = i * cos(alpha) - j * sin(alpha) - (I.getHeight()/2*cos(alpha) - sin(alpha)*I.getWidth()/2) + I.getHeight();
            int tj = i * sin(alpha) + j * cos(alpha) - (I.getWidth()/2*cos(alpha) + sin(alpha)*I.getHeight()/2) + I.getWidth();
            if((tj>0) && (ti>0) && (ti<D.getHeight()) && (ti<D.getWidth())) D[ti][tj] = I[i][j];
        }
}

void RotationInvertedBasic(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    for (int i=0; i<D.getHeight(); i++)
        for (int j=0; j<D.getWidth(); j++) {
            int ti = i * cos(alpha) + j * sin(alpha);// - (I.getHeight()/2*cos(alpha) - sin(alpha)*I.getWidth()/2) ;
            int tj = - i * sin(alpha) + j * cos(alpha);// - (I.getWidth()/2*cos(alpha) + sin(alpha)*I.getHeight()/2) + 3 * I.getWidth();
            if((tj>0) && (ti>0) && (ti<I.getHeight()) && (ti<I.getWidth())) D[i][j] = I[ti][tj];
        }

}

void RotationInvertedInterpolated(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    for (int i=0; i<D.getHeight(); i++)
        for (int j=0; j<D.getWidth(); j++) {
            float ti = i * cos(alpha) + j * sin(alpha);// - (I.getHeight()/2*cos(alpha) - sin(alpha)*I.getWidth()/2) ;
            float tj = - i * sin(alpha) + j * cos(alpha);// - (I.getWidth()/2*cos(alpha) + sin(alpha)*I.getHeight()/2) + 3 * I.getWidth();
            if((tj>0) && (ti>0) && (ti<I.getHeight()) && (ti<I.getWidth())) D[i][j] = interpole(I,ti,tj);
        }

}
void RotationInvertedBasicB(vpImage<uchar> I, vpImage<uchar> &D, float alpha) {
    vpDisplayX d1(D,400,100) ;
    vpDisplay::setTitle(D, "Image decimee bilineaire");
   while (true) 
    for (float x=0; x<6.28; x+=.01) {
        alpha = x;
        for (int i=0; i<D.getHeight(); i++)
            for (int j=0; j<D.getWidth(); j++) {
                int ti = i * cos(alpha) + j * sin(alpha) - (I.getHeight()/2*cos(alpha) - sin(alpha)*I.getWidth()/2) ;
                int tj = - i * sin(alpha) + j * cos(alpha) - (I.getWidth()/2*cos(alpha) + sin(alpha)*I.getHeight()/2) + 3 * I.getWidth();
                if((tj>0) && (ti>0) && (ti<I.getHeight()) && (ti<I.getWidth())) D[i][j] = I[ti][tj];
            }

        vpDisplay::display(D);
        vpDisplay::flush(D) ;	
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

    RotationBasic(I,D,3*3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Image decimee bilineaire");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);
}

void testRotationInvertedBasic() {
  	vpImage<uchar>  I;
	vpImageIo::read(I,"../images/lena.pgm") ;	
    vpImage<uchar> D(I.getHeight()*2,I.getWidth()*2);
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    RotationInvertedBasicB(I,D,3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Image decimee bilineaire");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);
}

void testRotationInvertedInterpolated() {
  	vpImage<uchar>  I;
	vpImageIo::read(I,"../images/lena.pgm") ;	
    vpImage<uchar> D(I.getHeight()*2,I.getWidth()*2);
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	

    RotationInvertedInterpolated(I,D,3.141592654/4);
	vpDisplayX d1(D,400,100) ;
	vpDisplay::setTitle(D, "Image decimee bilineaire");
	vpDisplay::display(D);
	vpDisplay::flush(D) ;	
    vpDisplay::getClick(D);
}
int main(int argc, char **argv)
{

  cout << "BINP TP 6 : REDUCTION ET AGRANDISSEMENT D'IMAGES " << endl ;
  cout << "--" << endl ;


	// creation du menu
    test();
    testRotationInvertedInterpolated();




  cout << "Fin du programme " << endl ;
  return(0);
}

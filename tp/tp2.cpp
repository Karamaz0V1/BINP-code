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


////////////////////// FONCTIONS FOURNIES ////////////////////////////////////////////
void HSVtoRGB(int h,int s,int v,vpRGBa &pix)
{
	int r=v, g=v, b=v;
    if ( s == 0 || h == -1 ) {                  // achromatic case
        ;
    } else {                                    // chromatic case
        if ( (unsigned int)h >= 360 )
            h %= 360;
        unsigned int f = h%60;
        h /= 60;
        unsigned int p = (unsigned int)(2*v*(255-s)+255)/510;
        unsigned int q, t;
        if ( h&1 ) {
            q = (unsigned int)(2*v*(15300-s*f)+15300)/30600;
            switch( h ) {
                case 1: r=(int)q; g=(int)v, b=(int)p; break;
                case 3: r=(int)p; g=(int)q, b=(int)v; break;
                case 5: r=(int)v; g=(int)p, b=(int)q; break;
            }
        } else {
            t = (unsigned int)(2*v*(15300-(s*(60-f)))+15300)/30600;
            switch( h ) {
                case 0: r=(int)v; g=(int)t, b=(int)p; break;
                case 2: r=(int)p; g=(int)v, b=(int)t; break;
                case 4: r=(int)t; g=(int)p, b=(int)v; break;
            }
        }
    }
    pix.R=r;
    pix.G=g;
    pix.B=b;
}

void RGBtoHSV( int &h, int &s, int &v , vpRGBa &pix)
{
    int r = pix.R;
    int g = pix.G;
    int b = pix.B;
    unsigned int max = r;                               // maximum RGB component
    int whatmax = 0;                            // r=>0, g=>1, b=>2
    if ( (unsigned int)g > max ) {
        max = g;
        whatmax = 1;
    }
    if ( (unsigned int)b > max ) {
        max = b;
        whatmax = 2;
    }
    unsigned int min = r;                               // find minimum value
    if ( (unsigned int)g < min ) min = g;
    if ( (unsigned int)b < min ) min = b;
    int delta = max-min;
    v = max;                                    // calc value
    s = max ? (510*delta+max)/(2*max) : 0;
    if ( s == 0 ) {
        h = -1;                         // undefined hue
    } else {
        switch ( whatmax ) {
            case 0:                             // red is max component
                if ( g >= b )
                    h = (120*(g-b)+delta)/(2*delta);
                else
                    h = (120*(g-b+delta)+delta)/(2*delta) + 300;
                break;
				case 1:                             // green is max component
                if ( b > r )
                    h = 120 + (120*(b-r)+delta)/(2*delta);
                else
                    h = 60 + (120*(b-r+delta)+delta)/(2*delta);
                break;
				case 2:                             // blue is max component
                if ( r > g )
                    h = 240 + (120*(r-g)+delta)/(2*delta);
                else
                    h = 180 + (120*(r-g+delta)+delta)/(2*delta);
                break;
        }
    }
}

//void RGBtoYUV(const vpImage<unsigned char> & const irgb , vpImage<unsigned char> & iyuv) {
void RGBtoYUV(const vpRGBa &rgb, vpRGBa &yuv) {
    // TODO U et V signés 
    yuv.R = 0.299 * rgb.R + 0.587 * rgb.G + 0.114 * rgb.B;
    yuv.G = 0.492 * (rgb.B - yuv.R);
    yuv.B = 0.877 * (rgb.R - yuv.R);
}

//}
//////////////////////////////////////////////////////////////////

/* 
- chaine : chaine de caracteres a modifier
- val : valeur du bit a inserer/modifier dans la chaine (1/0)
- position : position du bit a modifier dans la chaine
putBitInString : modifie le bit  la position pos dans chaine (et donc le caractere concerne)
*/
void putBitInString(char chaine[],const bool val,const unsigned int position) {
    if (val) chaine[position/8] |= (char)pow(2,(position%8));
}

void q11() {
    cout<<"Question 1.1"<<endl;
    cout<<"Décodage"<<endl;

	vpImage<unsigned char> Ii;
    vpImageIo::read(Ii,"../BINP-code/img/mixer.pgm") ;

	vpImage<unsigned char> Io1(Ii.getHeight(),Ii.getWidth());
	vpImage<unsigned char> Io2(Ii.getHeight(),Ii.getWidth());

    for (int i=0; i<Ii.getHeight(); i++) {
        for (int j=0; j<Ii.getWidth(); j++) {
            Io1[i][j] = Ii[i][j] & 240;
            Io2[i][j] = Ii[i][j] & 15;
            Io2[i][j] *= 16;
        }
    }

	vpDisplayX di(Ii,100,100) ;
	vpDisplay::display(Ii);
	vpDisplay::flush(Ii);
	vpDisplayX do1(Io1,350,100) ;
	vpDisplay::display(Io1);
	vpDisplay::flush(Io1);
	vpDisplayX do2(Io2,600,100) ;
	vpDisplay::display(Io2);
	vpDisplay::flush(Io2);

	vpDisplay::getClick(Ii);

    cout<<"Encodage"<<endl;

	vpImage<unsigned char> Ii1;
    vpImageIo::read(Ii1,"../BINP-code/img/otter.pgm") ;
	vpImage<unsigned char> Ii2;
    vpImageIo::read(Ii2,"../BINP-code/img/ottre.pgm") ;

	vpImage<unsigned char> Io(Ii1.getHeight(),Ii1.getWidth());

    for (int i=0; i<Ii1.getHeight(); i++) {
        for (int j=0; j<Ii1.getWidth(); j++) {
            Io[i][j] = (Ii1[i][j] & 240)+ Ii2[i][j] / 16;
        }
    }

	vpDisplayX di1(Ii1,100,100) ;
	vpDisplay::display(Ii1);
	vpDisplay::flush(Ii1);
	vpDisplayX di2(Ii2,350,100) ;
	vpDisplay::display(Ii2);
	vpDisplay::flush(Ii2);

	vpDisplayX doo(Io,600,100) ;
	vpDisplay::display(Io);
	vpDisplay::flush(Io);

	vpImageIo::write(Io,"./img/otrte.pgm") ;

	vpDisplay::getClick(Ii1);

}

void q12() {
    cout<<"Question 1.2"<<endl;
	vpImage<unsigned char> I1;
    vpImageIo::read(I1,"../BINP-code/img/water.pgm") ;
	vpDisplayX d1(I1,100,100) ;
	vpDisplay::display(I1);
	vpDisplay::flush(I1);
	vpDisplay::getClick(I1);

    char mark[I1.getHeight()*I1.getWidth()/8];

    for (int i=0; i<I1.getWidth(); i++)
        for (int j=0; j<I1.getHeight(); j++)
            putBitInString(mark, (I1[i][j] & 1), i*I1.getWidth()+j);

    cout<<"Oh ! I Mark : "<<mark<<endl;
}

void q22() {
    cout<<"Question 2.2"<<endl;
	vpImage<vpRGBa> I1;
    vpImageIo::read(I1,"../BINP-code/img/baboon_jpg.ppm") ;
	vpImage<vpRGBa> I2(I1.getWidth(),I1.getHeight());

    for (int i=0; i<I1.getHeight(); i++)
        for (int j=0; j<I1.getWidth(); j++)
            RGBtoYUV(I1[i][j],I2[i][j]);

	vpImage<unsigned char> I2R(I2.getWidth(),I2.getHeight());
    for (int i=0; i<I2.getHeight(); i++)
        for (int j=0; j<I2.getWidth(); j++)
            I2R[i][j] = I2[i][j].R;

	vpImage<unsigned char> I2G(I2.getWidth(),I2.getHeight());
    for (int i=0; i<I2.getHeight(); i++)
        for (int j=0; j<I2.getWidth(); j++)
            I2G[i][j] = I2[i][j].G;

	vpImage<unsigned char> I2B(I2.getWidth(),I2.getHeight());
    for (int i=0; i<I2.getHeight(); i++)
        for (int j=0; j<I2.getWidth(); j++)
            I2B[i][j] = I2[i][j].B;

	vpDisplayX d1(I2,100,000) ;
	vpDisplay::display(I2);
	vpDisplay::flush(I2);
	vpDisplayX d2R(I2R,100,500) ;
	vpDisplay::display(I2R);
	vpDisplay::flush(I2R);
	vpDisplayX d2G(I2G,500,000) ;
	vpDisplay::display(I2G);
	vpDisplay::flush(I2G);
	vpDisplayX d2B(I2B,500,500) ;
	vpDisplay::display(I2B);
	vpDisplay::flush(I2B);
	vpDisplay::getClick(I2);
}

int main(int argc, char **argv)
{

    cout << "BINP TP2 : MANIPULATION DES COULEURS " << endl ;
    cout << "--" << endl ;

  // creation du menu

    q22();

  cout << "Fin du programme " << endl ;
  return(0);
}
















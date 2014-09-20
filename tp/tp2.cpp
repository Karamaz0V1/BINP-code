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
//////////////////////////////////////////////////////////////////

/* 
- chaine : chaine de caracteres a modifier
- val : valeur du bit a inserer/modifier dans la chaine (1/0)
- position : position du bit a modifier dans la chaine
putBitInString : modifie le bit ˆ la position pos dans chaine (et donc le caractere concerne)
*/
void putBitInString(char chaine[],const bool val,const unsigned int position) {
	
	
}




int main(int argc, char **argv)
{

  cout << "BINP TP2 : MANIPULATION DES COULEURS " << endl ;
  cout << "--" << endl ;

  // creation du menu






  cout << "Fin du programme " << endl ;
  return(0);
}
















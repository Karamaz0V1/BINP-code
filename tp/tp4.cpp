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


/////////////////////// FONCTIONS FOURNIES  //////////////////////////////////////////
void creerPalette(const unsigned char* repR,const unsigned char* repG,const unsigned char* repB, const unsigned int nbRep, vpRGBa* pal) {
	int kk=0;
	int i,j,k;
	for(i=0;i<nbRep;i++)
		for(j=0;j<nbRep;j++)
			for(k=0;k<nbRep;k++) {
				pal[kk].R=repR[i];
				pal[kk].G=repG[j];
				pal[kk].B=repB[k];
				kk++;
			}
}


int corres(const vpRGBa &coul, const int * classeR, const int * classeG,const int * classeB,const unsigned int nbClasse) {
	int nbbits=(int)(ceil(log(nbClasse)/log(2)));
	return(((classeR[coul.R])<<(nbbits*2))+((classeG[coul.G])<<nbbits)+((classeB[coul.B])));
}
///////////////////////////////////////////////////////////////////////////////////////////


void quantifVectoriel(const vpImage<vpRGBa> &imasrc,vpImage<vpRGBa> &imadest, vpRGBa * pal,const int taillePalette) 
{
	
}



int main(int argc, char **argv)
{
	
	cout << "BINP TP4 : REDUCTION DE COULEURS " << endl ;
	cout << "--" << endl ;
	
	// chargement de l'image lena.ppm
  	vpImage<vpRGBa>  I;
	vpImageIo::read(I,"../images/lena.ppm") ;	
	vpDisplayX d(I,100,100) ;
	vpDisplay::setTitle(I, "Image originale");
	vpDisplay::display(I);
	vpDisplay::flush(I) ;	
	
	int nbbits;
    cout <<"entrer le nombre bits par composante :"<<endl;
    cin >> nbbits;
	
	// creation du menu
	
	
	
	vpDisplay::close(I) ;
	cout << "Fin du programme " << endl ;
	return(0);
}
















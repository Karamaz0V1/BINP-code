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


void histogramme(const vpImage<unsigned char>  &I, unsigned int* histo, int &max)
{
    for (int i=0; i<256; i++) 
        histo[i] = 0;

    for (int i=0; i<I.getHeight(); i++)
        for (int j=0; j<I.getWidth(); j++)
            if (++histo[I[i][j]] > max) max = histo[I[i][j]];
}

void histocumule(const vpImage<unsigned char> &I, unsigned int* histo, unsigned int* histocumul)
{
    int max = 0;
    int cumul = 0;

    histogramme(I, histo, max);
    for (int i=0; i<256; i++) {
        cumul += histo[i];
        histocumul[i] = cumul;
    }
}

void decoupecompo(const vpImage<unsigned char> &compo, unsigned char * correscompo, int n) {
    unsigned int histo[256];
    unsigned int histocumul[256];

    histocumule(compo, histo, histocumul);

    int pas = (compo.getWidth() * compo.getHeight()) / n;
    int palier = pas;
    int nbiter = 0;
    int aborne = 0;

    for (int i=0; i<256; i++) {
        if (histocumul[i] > palier) {
            correscompo[nbiter] = (aborne + i)/2; //TODO Faire la moyenne plutôt que de prendre la mediane
            aborne  = i;
            nbiter++;
            palier += pas;
        }
    }
}

// void separecompo(const vpImage<vpRGBa> &I, vpImage<unsigned char> is ...) //TODO split des composantes si possible

void quantifnonuniforme(const vpImage<vpRGBa> &I, int n, unsigned char* R, unsigned char * G, unsigned char* B) {
    vpImage<unsigned char> cr(I.getHeight(), I.getWidth());
    vpImage<unsigned char> cg(I.getHeight(), I.getWidth());
    vpImage<unsigned char> cb(I.getHeight(), I.getWidth());

    //TODO la suite
}

void quantifuniforme(const vpImage<vpRGBa> &I, int n) {
    int classe[256];
    unsigned char repR[n];
    unsigned char repG[n];
    unsigned char repB[n];

    int pas = 256 / n;
    int palier = 0;

    for(int i=0; i<256; i++) {
        if(i>palier*pas+pas) {
            repR[palier] = (palier*pas * 2 + pas) /2;
            repG[palier] = (palier*pas * 2 + pas) /2;
            repB[palier] = (palier*pas * 2 + pas) /2;
            palier++;
        }
        classe[i] = palier;
    }


    vpRGBa pal[(int)pow(n,3)];
    creerPalette(repR, repG, repB, n, pal);
    /*
    for(int=0; i<256; i++) {
        corres(I.
        */
}

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

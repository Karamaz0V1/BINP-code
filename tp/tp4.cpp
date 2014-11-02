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
 *  - BECKER Frederic
 *	- GUIOTTE Florent
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

void quantitatifnonuniformesurcomposante(const vpImage<unsigned char> &compo, unsigned char * corresCompo, int * classeCompo, int n) {
    cout<<"Travail sur une composante ---"<<endl;
    unsigned int histo[256];
    unsigned int histocumul[256];

    histocumule(compo, histo, histocumul);

    int pas = (compo.getWidth() * compo.getHeight()) / n;
    int nbiter = 0;
    int aborne = 0;
    int valmoy = 0;

    for (int i=0; i<256; i++) {
        classeCompo[i] = nbiter;
        if (histocumul[i] > (nbiter + 1) * pas - (pas/2) && valmoy == 0) valmoy = i;
        if (histocumul[i] > (nbiter + 1) * pas || i == 255) {
            corresCompo[nbiter] = valmoy;
            cout<<"I : "<<i<<"\tPalier : "<<nbiter<<"\tRep : "<<valmoy<<endl;
            aborne = i;
            nbiter++;
            valmoy = 0;
        }
    }
}

void quantifnonuniforme(const vpImage<vpRGBa> &I, int n) {
    vpImage<unsigned char> cr(I.getHeight(), I.getWidth());
    vpImage<unsigned char> cg(I.getHeight(), I.getWidth());
    vpImage<unsigned char> cb(I.getHeight(), I.getWidth());

    for (int i=0; i<I.getHeight(); i++)
        for (int j=0; j<I.getWidth(); j++) {
            cr[i][j] = I[i][j].R;
            cg[i][j] = I[i][j].G;
            cb[i][j] = I[i][j].B;
        }

    unsigned char crCorres[n];
    unsigned char cgCorres[n];
    unsigned char cbCorres[n];

    int crClasse[256];
    int cgClasse[256];
    int cbClasse[256];

    quantitatifnonuniformesurcomposante(cr,crCorres,crClasse,n);
    quantitatifnonuniformesurcomposante(cg,cgCorres,cgClasse,n);
    quantitatifnonuniformesurcomposante(cb,cbCorres,cbClasse,n);

    vpRGBa pal[(int)pow(n,3)];
    creerPalette(crCorres, cgCorres, cbCorres, n, pal);

    vpImage<vpRGBa> I2(I.getHeight(),I.getWidth());

    for(int i=0; i<I.getHeight(); i++)
        for(int j=0; j<I.getWidth(); j++)
            I2[i][j] = pal[corres(I[i][j], crClasse, cgClasse, cbClasse, n)];

    vpDisplayX d(I2,100,300);
    vpDisplay::setTitle(I2, "Tadaaaa!");
    vpDisplay::display(I2);
    vpDisplay::flush(I2);
    vpDisplay::getClick(I2);
}

void quantifuniforme(const vpImage<vpRGBa> &I, const int tailleComposante) {
    int n = tailleComposante;

    int classe[256];
    unsigned char rep[n];

    int pas = 256 / n;
    int palier = 0;

    for(int i=0; i<256; i++) {
        if(i > palier * pas + pas || i == 255) {
            rep[palier] = (palier*pas * 2 + pas) /2;
            cout<<"I : "<<i<<"\tPalier : "<<palier<<"\tRepR : "<<(int)rep[palier]<<endl;
            palier++;
        }
        classe[i] = palier;
    }

    vpRGBa pal[(int)pow(n,3)];
    creerPalette(rep, rep, rep, n, pal);

    vpImage<vpRGBa> I2(I.getHeight(),I.getWidth());

    for(int i=0; i<I.getHeight(); i++)
        for(int j=0; j<I.getWidth(); j++)
            I2[i][j] = pal[corres(I[i][j], classe, classe, classe, n)];

    vpDisplayX da(I2,100,300);
    vpDisplay::setTitle(I2, "Tadaaaa!");
    vpDisplay::display(I2);
    vpDisplay::flush(I2);
    vpDisplay::getClick(I2);
}


int distance_pix(const vpRGBa &a, const vpRGBa &b) {
    return sqrt(pow(b.R-a.R,2)+pow(b.G-a.G,2)+pow(b.B-a.B,2));
}


void quantifVectoriel(const vpImage<vpRGBa> &imasrc,vpImage<vpRGBa> &imadest, vpRGBa * pal,const int taillePalette) 
{
    float erreur = 0;
    int i = 0;

    float seuilErreur = 0.1;
    int seuilIteration = 100000;

    double sumCompo[taillePalette][3];
    for (int i=0; i<taillePalette; i++) 
        for (int j=0; j<3; j++) sumCompo[i][j] = 0;

    while (erreur < seuilErreur && i < seuilIteration) {
        for(int i=0; i<imasrc.getHeight(); i++)
            for(int j=0; j<imasrc.getWidth(); j++) {
                int dist_min = distance_pix(imasrc[i][j],pal[0]);
                int classe = 0;
                for(int x=1; x<taillePalette; x++)
                    if (distance_pix(imasrc[i][j],pal[x]) < dist_min) int classe = x;
            }
    }
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
    int tailleComposante = pow(2,nbbits);

    quantifuniforme(I,tailleComposante);
    quantifnonuniforme(I,tailleComposante);
	
	
	
	vpDisplay::close(I) ;
	cout << "Fin du programme " << endl ;
	return(0);
}

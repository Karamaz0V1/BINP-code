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
 * Date : Oct 2014
 *****************************************************************************/


#include <iostream>

#include <visp/vpConfig.h>
#include <visp/vpDebug.h>

#include <visp/vpImage.h>
#include <visp/vpImageIo.h>
#include <visp/vpDisplayX.h>

using namespace std;


////////////////////// FONCTION FOURNIE ////////////////////////////////////////////
void tracer_histo(const unsigned int *histo, const unsigned int max, const int size, const int posX, const int posY) {
	
	vpImage<unsigned char> Ih(100,size) ;
	Ih = 0;
	
	vpDisplayX d2(Ih,posX,posY) ;
	vpDisplay::display(Ih) ;
	vpDisplay::flush(Ih) ;
	
	
	int i;
	for(i=0;i<size;i++)
		vpDisplay::displayLine(Ih,99,i,99-(int)(histo[i]*99/max),i,vpColor::red);
	vpDisplay::flush(Ih) ;
	vpDisplay::getClick(Ih) ;
	vpDisplay::close(Ih) ;	
}

/////////////////////////////////////////////////////////////////////////////////////


void histogramme(const vpImage<unsigned char>  &I, unsigned int* histo, int &max)
{
    for (int i=0; i<256; i++) 
        histo[i] = 0;

    for (int i=0; i<I.getHeight(); i++)
        for (int j=0; j<I.getWidth(); j++)
            if (++histo[I[i][j]] > max) max = histo[I[i][j]];
}


double entropie (const unsigned int* histo, const unsigned int h, const unsigned int w)
{
    double sum = 0;

    for (int i=0; i<256; i++) {
        float prob = (histo[i]*1.0/(h*w));
        if (prob == 0) continue;
        sum += prob * (log(prob)/log(2));
    }
    return -sum;
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

float moyenne (const unsigned int* histo, const unsigned int h, const unsigned int w) {
    double sum = 0;
    for (int i=0; i<256; i++)
        sum += histo[i] * i;
    return sum/(h*w);
}

float  ecart_type (const unsigned int* histo, const unsigned int h, const unsigned int w) {
    int moy = moyenne(histo, h, w);
    double sum = 0;
    for (int i=0; i<256; i++)
        sum += pow(i - moy, 2) / (h*w) * histo[i];
    return sqrt(sum);
}

void dynamique (const unsigned int* histo, int &min, int &max) {
    int i=0;
    while (histo[i] == 0) i++;
    min = i;
    i=255;
    while (histo[i] == 0) i--;
    max = i;
}

int niveaux_de_gris (const unsigned int* histo) {
    int nb = 0;
    for (int i=0; i<256; i++)
        if (histo[i] != 0) nb++;
    return nb;
}

void compute_stat(const vpImage<unsigned char>  &I0, const unsigned int h,const unsigned int w, const int posX, const int posY)
{
    unsigned int histo[256];
    unsigned int histocumul[256];

    int max = 0;
    histogramme(I0, histo, max);
    tracer_histo(histo, max, 256, 100, 300);
    histocumule(I0, histo, histocumul);
    tracer_histo(histocumul, I0.getWidth()*I0.getHeight(), 256, 100, 300);

    cout<<"Entropie : "<<entropie(histo, h, w)<<endl;
    cout<<"Moyenne : "<<moyenne(histo, h, w)<<endl;
    cout<<"Écart type : "<<ecart_type(histo, h, w)<<endl;
    int dmin, dmax;
    dynamique(histo, dmin, dmax);
    cout<<"Dynamique minimum : "<<dmin<<" maximum : "<<dmax<<endl;
    cout<<"Nombre de niveaux de gris : "<<niveaux_de_gris(histo)<<endl;
}

void anamorphose1(const vpImage<unsigned char>  &I0, const float pente)
{
	vpImage<unsigned char> I1(I0.getWidth(), I0.getHeight());

    for (int i=0; i<I0.getWidth(); i++)
        for (int j=0; j<I0.getHeight(); j++)
            I1[i][j] = I0[i][j] * pente;

	vpDisplayX d2(I1,100,500) ;
	vpDisplay::display(I1) ;
	vpDisplay::flush(I1) ;
	
	compute_stat(I1, I1.getHeight(), I1.getWidth(), 100, 500);
	
	vpDisplay::getClick(I1) ;
}


void anamorphose2(const vpImage<unsigned char>  &I0, const unsigned int seuil)
{
	vpImage<unsigned char> I1(I0.getWidth(), I0.getHeight());

    for (int i=0; i<I0.getWidth(); i++)
        for (int j=0; j<I0.getHeight(); j++) {
            int g = I0[i][j] * (255/seuil);
            if (g > 255) I1[i][j] = 255;
            else I1[i][j] = g;
        }

	vpDisplayX d2(I1,100,500) ;
	vpDisplay::display(I1) ;
	vpDisplay::flush(I1) ;
	
	compute_stat(I1, I1.getHeight(), I1.getWidth(), 100, 500);
	
	vpDisplay::getClick(I1) ;
}


void egalisation(const vpImage<unsigned char>  &I)
{
	vpImage<unsigned char>  I2(I.getHeight(), I.getWidth());

    unsigned int histo[256];
    unsigned int histocumul[256];
    unsigned int anam[256];
    int max;
    int h = I.getHeight();
    int w = I.getWidth();

    histogramme(I, histo, max);
    tracer_histo(histo, max, 256, 100, 300);
    histocumule(I, histo, histocumul);
    tracer_histo(histocumul, w*h, 256, 100, 300);
    cout<<"Entropie : "<<entropie(histo, h, w)<<endl;
    cout<<"Moyenne : "<<moyenne(histo, h, w)<<endl;
    cout<<"Écart type : "<<ecart_type(histo, h, w)<<endl;
    int dmin, dmax;
    dynamique(histo, dmin, dmax);
    cout<<"Dynamique minimum : "<<dmin<<" maximum : "<<dmax<<endl;
    cout<<"Nombre de niveaux de gris : "<<niveaux_de_gris(histo)<<endl;

    for (int i=0; i<256; i++)
        anam[i] = round(1.0*histocumul[i]/(I.getWidth()*I.getHeight())*255);

    //tracer_histo(anam, max, 256, 100, 300);

    for (int i=0; i<I.getHeight(); i++) 
        for (int j=0; j<I.getWidth(); j++)
            I2[i][j] = anam[I[i][j]];

    

	vpDisplayX d2(I2,100,500) ;
	vpDisplay::display(I2) ;
	vpDisplay::flush(I2) ;
	
	histogramme(I2, histo, max);
    tracer_histo(histo, max, 256, 100, 300);
	histocumule(I2, histo, histocumul);
    tracer_histo(histocumul, w*h, 256, 100, 300);
    cout<<"Entropie : "<<entropie(histo, h, w)<<endl;
    cout<<"Moyenne : "<<moyenne(histo, h, w)<<endl;
    cout<<"Écart type : "<<ecart_type(histo, h, w)<<endl;
    dynamique(histo, dmin, dmax);
    cout<<"Dynamique minimum : "<<dmin<<" maximum : "<<dmax<<endl;
    cout<<"Nombre de niveaux de gris : "<<niveaux_de_gris(histo)<<endl;
	
	vpDisplay::getClick(I2) ;
}

int main(int argc, char **argv)
{

  cout << "BINP TP3 : MANIPULATION D'HISTOGRAMMES " << endl ;
  cout << "--" << endl ;

	vpImage<unsigned char>  I0;
	string sIm;	
	vpDisplayX d0(100,100,"Image originale") ;
	float pente;
	unsigned int seuil;
	
	int choix=0;
	while(choix<5)
	{
		cout << "\n-------------------------------------" << endl;
		cout<<"1. Affichage des stats d'une image"<<endl;
		cout<<"2. Anamorphoses"<<endl;
		cout<<"3. Egalisation d'histogramme"<<endl;
		cout<<"4. Egalisation d'histogramme (choix)"<<endl;
		cout<<"5. Quitter"<<endl;
		
		cin>>choix;
		cout << "-------------------------------------" << endl;
		
		
		switch(choix)
		{
			case 1 :
				cout << "Nom de l'image : "; cin >> sIm; 	
				vpImageIo::read(I0,sIm) ;
				d0.init(I0);
				vpDisplay::display(I0);
				vpDisplay::flush(I0) ;
				cout << "\n Valeurs image initiale : " << endl;

				compute_stat(I0, I0.getHeight(), I0.getWidth(), 100, 500);
				
				vpDisplay::getClick(I0);
				vpDisplay::close(I0) ;
				break;
			case 2 :
				cout << "Nom de l'image : "; cin >> sIm; 	
				vpImageIo::read(I0,sIm) ;
				d0.init(I0);
				vpDisplay::display(I0);
				vpDisplay::flush(I0) ;	
				
				// Premiere anamorphose
				cout << "pente ? "; cin >> pente; 	
				anamorphose1(I0,pente);
				
				// Deuxieme anamorphose
				cout << "\nseuil ? "; cin >> seuil; 
				anamorphose2(I0, seuil);	
				
				vpDisplay::getClick(I0);
				vpDisplay::close(I0) ;
				break;
			case 3 :
				vpImageIo::read(I0,"../images/lezard.pgm") ;
				d0.init(I0);
				vpDisplay::display(I0);
				vpDisplay::flush(I0) ;	
				// Egalisation
				egalisation(I0);
				
				vpDisplay::getClick(I0);
				vpDisplay::close(I0) ;
				break;
            case 4 :
				cout << "Nom de l'image : "; cin >> sIm; 	
				vpImageIo::read(I0,sIm) ;
				d0.init(I0);
				vpDisplay::display(I0);
				vpDisplay::flush(I0) ;	
				
				// Egalisation
				egalisation(I0);
				
				vpDisplay::getClick(I0);
				vpDisplay::close(I0) ;
				break;
				
			default :
				break;
		}
	}
	
  cout << "Fin du programme " << endl ;
  return(0);
}

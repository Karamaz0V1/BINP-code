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

}


double entropie (const unsigned int* histo, const unsigned int h, const unsigned int w)
{


}

void histocumule(const vpImage<unsigned char> &I, unsigned int* histo, unsigned int* histocumul)
{


}

void compute_stat(const vpImage<unsigned char>  &I0, const unsigned int h,const unsigned int w, const int posX, const int posY)
{

	
}

void anamorphose1(const vpImage<unsigned char>  &I0, const float pente)
{
	
}


void anamorphose2(const vpImage<unsigned char>  &I0, const unsigned int seuil)
{

}


void egalisation(const vpImage<unsigned char>  &I)
{
	
	
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
				
			default :
				break;
		}
	}
	

	
  cout << "Fin du programme " << endl ;
  return(0);
}
















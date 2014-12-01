#include <stdlib.h>				/* pour exit(); */
#include <stdio.h>
#include <iostream>
//#include <unistd.h>				/* pour SEEK_END */
#include <math.h>
#include "fft-a-prog.h"
#include "module-fft.h"
#include "imagesRW.h"





/******************** calcul de module complexe ********* **********************
  entrees:
  double *x;	  vecteur d'entree partie reelle
  double *y;	  vecteur d'entree partie imaginaire
  int  n;		  dimension signal
  sorties:        vecteur contenant le module
*********************************************************************************/

void module(double *x,double *y,int n,double *mod)
{
    for (int i=0; i<n; i++)
        mod[i] = sqrt(pow(x[i],2)+pow(y[i],2));
}




/******************* procedure FFT_INV  ***************************************
  double *x;	  vecteur d'entree/sortie partie reelle
  double *y;	  vecteur d'entree/sortie partie imaginaire
  int     n;	  dimension signal
  role : calcule la fft inverse = 1/n(fft(x*))*
*********************************************************************************/


void fft_inv (double *x,double *y,int n)
{
    for (int i=0; i<n; i++)
        y[i] = -y[i];

    fft(x,y,n);

    for (int i=0; i<n; i++) {
        x[i] = x[i] / n;
        y[i] = -y[i] / n;
    }
}



/******************* procedure FFT_2D  ***************************************
  double *x;	  vecteur entree/sortie partie reelle du signal 2D
  double *y;	  vecteur d'entree/sortie partie imaginaire du signal 2D
  int     n;	  dimension du signal = nombre de lignes = nombre de colonnes
  role : calcule la fft 2D = 1/n * fft(colonnes(fft(lignes))

  ATTENTION: faire un bit reverse sur les lignes avant de faire une FFT
             sur les lignes.
             faire un bit reverse sur les colonnes avant de faire une FFT sur
	     les colonnes.
  *********************************************************************************/


void fft_2D (double *x,double *y,int n)
{
    double xi[n];
    double yi[n];
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            xi[j]=x[j+n*i];
            yi[j]=y[j+n*i];
        }
        bit_reverse(xi,n);
        bit_reverse(yi,n);
        fft(xi,yi,n);
        for(int j=0; j<n; j++) {
            x[j+n*i]=xi[j];
            y[j+n*i]=yi[j];
        }
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            xi[j]=x[i+n*j];
            yi[j]=y[i+n*j];
        }
        bit_reverse(xi,n);
        bit_reverse(yi,n);
        fft(xi,yi,n);
        for(int j=0; j<n; j++) {
            x[i+n*j]=xi[j] / n;
            y[i+n*j]=yi[j] / n;
        }
    }

}


/******************* procedure FFT_2D_INV  ***************************************
  double *x;	  vecteur entree/sortie partie reelle du signal 2D
  double *y;	  vecteur d'entree/sortie partie imaginaire du signal 2D
  int     n;	  dimension du signal = nombre de lignes = nombre de colonnes
  role : calcule la fft inverse = (fft_2D(x*))*
*********************************************************************************/


void fft_2D_inv (double *x,double *y,int n)
{
    for (int i=0; i<n*n; i++)
        y[i] = -y[i];

    fft_2D(x,y,n);

    for (int i=0; i<n*n; i++) {
        x[i] = x[i];
        y[i] = -y[i];
    }
}

/******************* procedure sinusoidale_1d  **************************************
  - cree la fonction sin(2*pi*4nb/n) et la sauve dans test1d.

  int n;     taille du signal.
  int nb;    nb de periodes.

  *********************************************************************************/


void sinusoidale_1d(int n,int nb)
{
    FILE* fich = fopen("test1d.txt","w");
    if (fich) {
        fprintf(fich, "%d\n",n);
        for (int i=0; i<n; i++) {
            float res = sin(2*PI*1*nb*i/n);
            fprintf(fich,"%.4f ",res);
        }
        fclose(fich);
    }
}



/***************** procedure mire_sinus ***********************************
  int n;    taille de l'image
  int nb;   nb de periodes
  role:  creation d'une mire sinusoidale nxn contenant nb periodes et
         sauvegarde sous forme d'image dans le fichier "mire-sinusoidale.pgm".
	 ( utiliser la fonction sauve_pgm("mire-sinusoidale.pgm",im1,n,n);)
	 ****************************************************************/     

void mire_sinus (int n,int nb)
{
    unsigned char * im; 
    im = new unsigned char [n*n];
    for (int j=0; j<n; j++) {
            for (int i=0; i<n; i++) {
                float res = sin(2*PI*1*nb*i/n);
                im[j*n+i] = res * 127 + 128;
            }
    }
    writePGM_Picture("mire_sinusoidale.pgm", im, n, n);
}




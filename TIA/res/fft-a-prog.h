
#ifndef aprog_h /* evite d'inclure deux fois le fichier */
#define prog_h

#include <stdlib.h>				/* pour exit(); */
#include <stdio.h>
//#include <unistd.h>				/* pour SEEK_END */
#include <math.h>
#include "module-fft.h"


#define PI		3.141592653589793



/******************** calcul de module complexe ********* **********************
  entrees:
  double *x;	  vecteur d'entree partie reelle
  double *y;	  vecteur d'entree partie imaginaire
  int  n;		  dimension signal
  sorties:        vecteur contenant le module
*********************************************************************************/

void module(double *x,double *y,int n,double *mod);




/******************* procedure FFT_INV  ***************************************
  double *x;	  vecteur d'entree/sortie partie reelle
  double *y;	  vecteur d'entree/sortie partie imaginaire
  int     n;	  dimension signal
  role : calcule la fft inverse = 1/n(fft(x*))*
*********************************************************************************/


void fft_inv (double *x,double *y,int n);



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


void fft_2D (double *x,double *y,int n);



/******************* procedure FFT_2D_INV  ***************************************
  double *x;	  vecteur entree/sortie partie reelle du signal 2D
  double *y;	  vecteur d'entree/sortie partie imaginaire du signal 2D
  int     n;	  dimension du signal = nombre de lignes = nombre de colonnes
  role : calcule la fft inverse = (fft_2D(x*))*
*********************************************************************************/


void fft_2D_inv (double *x,double *y,int n);


/******************* procedure sinusoidale_1d  **************************************
  - cree la fonction sin(2*pi*4nb/n) et la sauve dans test1d.

  int n;     taille du signal.
  int nb;    nb de periodes.

  *********************************************************************************/


void sinusoidale_1d(int n,int nb);



/***************** procedure mire_sinus ***********************************
  int n;    taille de l'image
  int nb;   nb de periodes
  role:  creation d'une mire sinusoidale nxn contenant nb periodes et
         sauvegarde sous forme d'image dans le fichier "mire-sinusoidale.pgm".
	 ( utiliser la fonction sauve_pgm("mire-sinusoidale.pgm",im1,n,n);)
	 ****************************************************************/     

void mire_sinus (int n,int nb);



#endif /* #ifndef aprog_h */

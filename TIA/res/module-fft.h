#ifndef module_inclu /* empeche d'inclure deux fois le fichier */
#define module_inclu


#include <stdio.h>
#include <stdlib.h>
#include "fft-a-prog.h"


#define PI		3.141592653589793

/*************************** Bit reverse ****************************************
   entrees : x : vecteur reel de taille n
             n : puissance de 2
   sorties : x : elements de x apres permutation
     role  : permutte les elements de x pour obtenir la FFT dans l'ordre voulu
*********************************************************************************/
void bit_reverse(double *x,int n);


/******************* procedure FFT , Entrelacement temporel ********************
  double *x ;	  vecteur d'entree/sortie partie reelle
  double *y ;	  vecteur d'entree/sortie partie imaginaire
  int     n ;	  dimension signal (y compris padding)
  role : calcule la fft par entrelacement temporel d'un signal complexe
*********************************************************************************/
void fft(double *x,double *y,int n);


/******************* procedure DECAL_ORIGINE ***************************************
  double *x;	  vecteur d'entree/sortie : pointeur sur la matrice de pixels
  int     n;	  image de taille n*n
  role : decale les elements pour avoir l'origine au centre de l'image
*********************************************************************************/
void decal_origine (double *x,int n);



/******************* procedure ecrire_vec_2D  ***************************************
  FILE   *fichout; fichier de sortie
  double *x;       adresse du vecteur 2D
  int     n;	   image de taille n*n

*********************************************************************************/
void ecrire_vec_2D(FILE *fichout,double *x, int n);


/******************* procedure TEST1D  ***************************************

  - lit les donnees a partir du fichier "test1d" contenant la taille du
    vecteur puis le vecteur lui-meme.
  - ecrit le signal d'entree dans le fichier "resul1d".
  - calcule la fft 1d et le module du de cette fft
  - ecrit la partie reelle et imaginaire de la fft ainsi
    que son module dans le fichier "resul1d".

 **************************************************************************/
void TEST1D();


/******************* procedure TEST2D  ***************************************

  - lit les donnees a partir du fichier "test2d" contenant la taille du
    vecteur puis n*n valeurs.
  - ecrit le signal d'entree.
  - calcule la fft 2d et le module decale de cette fft
  - ecrit la partie reelle et imaginaire de la fft ainsi
    que son module  decale dans le fichier "resul2d".

    **************************************************************************/
void TEST2D();



/******************* procedure FFT_IM  ***************************************

  - lit une image au format pgm.
  - calcule sa fft2d ainsi que son module.
  - ecrit le module dans le fichier ascii fft_im.ascii
  - ecrit le module dans le fichier image fft_im.pgm (avec mise a l'echelle)
  - calcule la fft imverse
  - ecrit la fft inverse dans le fichier ascii fft_im_inv.ascii

    **************************************************************************/
void FFT_IM();



#endif /* #ifndef module_inclu */



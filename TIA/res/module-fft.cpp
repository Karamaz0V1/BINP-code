#include <math.h>
#include <string.h>
#include "module-fft.h"
#include "imagesRW.h"
#include <iostream>

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

/********************************************************************************
*		FFT - Entrelacement temporel					*
*										*
*		X : Vecteur
D'entree reel					*
*		Y : Vecteur D'entree imaginaire	(nul pour signaux reels)	*
*		N : Taille signal (puissance de 2)				*
*										*
*********************************************************************************/




/*************************** Bit reverse ****************************************
   entrees : x : vecteur reel de taille n
           n : puissance de 2
   sorties: x : elements de x apres permutation
   role  : permutte les elements de x pour obtenir la FFT dans l'ordre voulu
*********************************************************************************/

void bit_reverse(double *x,int n)

{
  int i,j;
  double buffer_x1,buffer_x2;
  int n2,l;

  j=1;
  n2 = n/2;

  for(i=1;i<n;i++) {

    if(i<j) {
      buffer_x1=x[i-1];
      buffer_x2=x[j-1];
      x[i-1]=buffer_x2;
      x[j-1]=buffer_x1;
    }
    l=n2;

    while(j>l) {
      j -= l;
      l /= 2;
    }
    j += l;

  }

}

/************** FIN bit-reverse***************************************************/



/******************* procedure FFT , Entrelacement temporel ********************
  double *x;	  vecteur d'entree/sortie partie reelle
  double *y;	  vecteur d'entree/sortie partie imaginaire
  int     n;	  dimension signal (y compris padding)
  role : calcule la fft par entrelacement temporel d'un signal complexe
  *********************************************************************************/

void fft(double *x,double *y,int n)

{

  int i,k,l;
  int  m,nm1,nm3,n1,n2,n3;
  double ur,tr,ui,ti,vr,vi,wr,wi;
  double teta;

  m = (int)(log((double)(n))/log(2.0));
  nm1= n-1;
  nm3 = n-3;

  /*---------------- premier etage ----------------------*/

  for(i=0;i<nm1;i+=2) {

    tr = x[i];
    ti = y[i];
    ur = x[i+1];
    ui = y[i+1];
    x[i] = tr + ur;
    y[i] = ti + ui;
    x[i+1] = tr - ur;
    y[i+1] = ti - ui;
  }

  /*------------------ deuxieme etage -------------------*/

  for(i=0;i<nm3;i+=4) {

    tr = x[i];
    ti = y[i];
    ur = x[i+2];
    ui = y[i+2];
    x[i] = tr + ur;
    y[i] = ti + ui;
    x[i+2] = tr - ur;
    y[i+2] = ti - ui;
    tr = x[i+1];
    ti = y[i+1];
    ur = x[i+3];
    ui = y[i+3];
    x[i+1] = tr + ui;
    y[i+1] = ti - ur;
    x[i+3] = tr - ui;
    y[i+3] = ti + ur;
  }

  /*--------------------------------------------------------------*/

  for(i=3;i<=m;i++) {

    n1 = (1<<(i-1));
    n2 = (1<<(m-i));

    for(l=1;l<=n2;l++) {

      for(k=1;k<=n1;k++) {

	n3 = (k - 1) + (l - 1) * 2 * n1;
	tr = x[n3];
	ti = y[n3];
	ur = x[n1+n3];
	ui = y[n1+n3];

	teta = (double)((2.*PI*(float)(n2*(float)(k-1.)))/(float)(n));

	wr = cos(teta);
	wi = sin(teta);
	vr = ur * wr + ui * wi;
	vi = -ur * wi + ui * wr;
	x[n3]= tr + vr;
	y[n3]= ti + vi;
	x[n1+n3] = tr - vr;
	y[n1+n3] = ti - vi;

      }
    }
  }
}

/**************************** FIN PROCEDURE FFT *******************************/



/******************* procedure DECAL_ORIGINE ***************************************
  double *x;	  vecteur d'entree/sortie : pointeur sur la matrice de pixels
  int     n;	  image de taille n*n
  role : decale les elements pour avoir l'origine au centre de l'image
  *********************************************************************************/

void decal_origine (double *x,int n)

{
  double  val;
  int i,j,k,l;

  for(i=0;i<n/2;i++){
    for(j=0;j<n;j++){
      k = (i+n/2) % n;
      l = (j+n/2) % n;
      val = x[n*i+j];
      x[n*i+j] = x[n*k+l];
      x[n*k+l] = val;
    }
  }

}

/************** FIN decal_origine ************************************************/



/******************* procedure ecrire_vec_2D ***************************************
  FILE   *fichout; fichier de sortie
  double *x;       adresse du vecteur 2D
  int     n;	   image de taille n*n

  *********************************************************************************/

void ecrire_vec_2D(FILE *fichout,double *x, int n)
{
  int i,j;

  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      fprintf(fichout,"%8lg ",x[n*i+j]);
    }
    fprintf(fichout,"\n");
  }
  fprintf(fichout,"\n");

}

/************** FIN ecrire_vec_2D ************************************************/



/******************* procedure TEST1D  ***************************************

  - lit les donnees a partir du fichier "test1d" contenant la taille du
    vecteur puis le vecteur lui-meme.
  - ecrit le signal d'entree dans le fichier "resul1d".
  - calcule la fft 1d et le module de cette fft
  - ecrit la partie reelle et imaginaire de la fft ainsi
    que son module dans le fichier "resul1d".

  **************************************************************************/

void TEST1D()

{
  FILE *fichin,*fichout;

  int i,j;
  int n;
  double *x,*y,*mod;


   /* lecture depuis des fichiers contenant le nombre de valeurs n, puis de la suite des n valeurs */

  fichin = fopen("test1d.txt","r");
  if (fichin){
    fscanf(fichin,"%d",&n);


    x = new double[n];
    y = new double[n];
    mod = new double[n];

    for(i=0;i<n;i++) /* initialisation de y a 0 */
    {
      y[i] = 0.0;
    }

    for(i=0;i<n;i++)  /* lecture du fichier d'entree */
    {
      fscanf(fichin,"%lf",&(x[i]));

    }

    /* ecriture dans fichier resultat */

    fichout = fopen("resul1d.txt","w");
    if (fichout){
      fprintf(fichout,"donnees d'entree: \n");
      /* ecriture donnees d'entree */
      for(i=0;i<n;i++)
      {
	fprintf(fichout,"%8lg ",x[i]);
      }

      /* calcul fft1D et module */
      bit_reverse(x,n);
      fft(x,y,n);
      module(x,y,n,mod);

      /* ecriture donnees resultats */

      fprintf(fichout,"\n");
      fprintf(fichout,"partie reelle: \n");
      for(i=0;i<n;i++){
	fprintf(fichout,"%8lg ",x[i]);
      }
      fprintf(fichout,"\n");
      fprintf(fichout,"partie imaginaire: \n");
      for(i=0;i<n;i++){
	fprintf(fichout,"%8lg ",y[i]);
      }
      fprintf(fichout,"\n");
      fprintf(fichout,"module: \n");
      for(i=0;i<n;i++){
	fprintf(fichout,"%8lg ",mod[i]);
      }
      fprintf(fichout,"\n");

      /* calcul fft1D inverse */
      bit_reverse(x,n);
      bit_reverse(y,n);
      fft_inv(x,y,n);

      fprintf(fichout,"\n");
      fprintf(fichout," fft inv partie reelle : \n");
      for(i=0;i<n;i++){
	fprintf(fichout,"%8lg ",x[i]);
      }
      fprintf(fichout,"\n");
      fprintf(fichout,"fft inv partie imaginaire: \n");
      for(i=0;i<n;i++){
	fprintf(fichout,"%8lg ",y[i]);
      }
      fprintf(fichout,"\n");

    }
    else printf("erreur ecriture fichier");
    fclose(fichout);

    delete []x;
    delete []y;
    delete []mod;

  }
  else printf("erreur lecture fichier");
  fclose(fichin);

}

/************** FIN TEST1D **************************************************/



/******************* procedure TEST2D  ***************************************

  - lit les donnees a partir du fichier "test2d" contenant la taille du
    vecteur puis n*n valeurs.
  - ecrit le signal d'entree.
  - calcule la fft 2d et le module de cette fft
  - ecrit la partie reelle et imaginaire de la fft ainsi
    que son module  decale dans le fichier "resul2d".

    **************************************************************************/

void TEST2D()

{
  FILE *fichin,*fichout;

  int i,j;

  int n;

  double *imx,*imy,*immod;


  /* lecture depuis des fichiers contenant n, puis  n*n valeurs */

  fichin = fopen("test2d.txt","r");
  if (fichin){
    fscanf(fichin,"%d",&n);

    imx = new double[n*n];
    imy = new double[n*n];
    immod = new double[n*n];
    for(i=0;i<n*n;i++){
      fscanf(fichin, "%lf",&(imx[i]));
      imy[i] = 0;
    }


    fichout = fopen("resul2d.txt","w");
    if (fichout){
      fprintf(fichout,"donnees initiales \n");
      ecrire_vec_2D(fichout,imx,n);

      /* calcul de la fft 2D */
      fft_2D(imx,imy,n);
      module(imx,imy,n*n,immod);

      fprintf(fichout,"fft: partie reelle \n");
      ecrire_vec_2D(fichout,imx,n);

      fprintf(fichout,"fft: partie immaginaire \n");
      ecrire_vec_2D(fichout,imy,n);

      fprintf(fichout,"fft: module \n");
      ecrire_vec_2D(fichout,immod,n);

      /* decalage pour avoir l'origine au centre */
      decal_origine(immod,n);

      fprintf(fichout,"fft: module avec origine au centre\n");
      ecrire_vec_2D(fichout,immod,n);

      /* fft inverse */
      fft_2D_inv(imx,imy,n);

      fprintf(fichout,"fft_inverse : partie reelle \n");
      ecrire_vec_2D(fichout,imx,n);

      fprintf(fichout,"fft_inverse : partie immaginaire \n");
      ecrire_vec_2D(fichout,imy,n);      
    }
    else printf("erreur ecriture fichier");
    fclose(fichout);

  }
  else printf("erreur lecture fichier");
 
  if (fichin)
  {  
   delete [] imx;
   delete [] imy;
   delete [] immod;
  }
  fclose(fichin);
}

/************** FIN TEST2D *************************************************/


void debruit_local(int n, double* imx, double* imy, int x1, int y1, int x2, int y2) {
    for (int i=x1; i<=x2; i++)
        for (int j=y1; j<=y2; j++) {
              imx[i*n+j] = 0;//= 500 ;
              imy[i*n+j] = 0;//= 500;
        }
}

int distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2-x1,2)+pow(y2-y1,2));
}

float eqm(int n, unsigned char *I1, unsigned char *I2){
    float EQM=0;   
    for (int i=0 ; i< n; i++)
        for (int j=0; j < n; j++)
            EQM+=pow(I1[i*n+j] - I2[i*n+j],2)/(n*n);
    return EQM;
}

/******************* procedure FFT_IM  ***************************************

  - lit une image au format pgm.
  - calcule sa fft2d ainsi que son module.  
  - ecrit le module dans le fichier image fft-im.pgm (avec mise a l'echelle)
  - calcule la fft imverse
  - ecrit la fft inverse dans le fichier image  fft-im-inv.pgm

    **************************************************************************/

void FFT_IM()
{   
  double *imx,*imy,*immod;
  unsigned char *im1,*im2;
  int i,j;
  int k;
  double val_double;
  double max;

  /* lecture d'une image en format pgm */
  char fileName[250];
  //strcpy(fileName, "./test.pgm");
  strcpy(fileName, "./save.pgm");
  int n = 512 ;
  im1 = new unsigned char [n*n];

  printf("\n Ouverture de %s de taille [%d,%d]", fileName, n, n);
  readPGM_Picture(fileName, im1, n, n);

  /*initialisation des vecteurs d'entree reel et imaginaire*/
  imx = new double[n*n];
  imy = new double[n*n];
  immod = new double[n*n];
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      k=n*i+j;
      imx[k] = double (im1[k]);
      imy[k] = 0.0;
    }
  }

  /* calcul de la fft-2D */
  fft_2D(imx,imy,n);

  module(imx,imy,n*n,immod);
  //decal_origine(immod,n);

  /* ecriture dans une image */
  im2 = new unsigned char [n*n];

  max=0; /* variable de remise a l'echelle*/
  for (i=0;i<n*n;i++)
    if ( immod[i] > max) max=immod[i];

  for (i=0;i<n;i++){
    for(j=0;j<n;j++){
      val_double = log(immod[n*i+j]+1) / log(max+1) * 255 ;
      im2[i*n+j]  = (unsigned char) (val_double);
    }
  }
 
  /* Calculs sur spectre */
  /* Attenuer la barre verticale */
//  for (int i=0; i<n; i++)
//      for (int j=0; j<n ; j++) {
//          if (j>0&&j<63) {
//              imx[i*n+j] = 0;
//              imy[i*n+j] = 0;
//          }
//  }

  /* Diminuer la valeur moyenne */
//              imx[0] /= 3 ;
//              imy[0] /= 3;
//              imx[n-1] /= 3 ;
//              imy[n-1] /= 3;
//              imx[(n-1)*n] /= 3 ;
//              imy[(n-1)*n] /= 3;
//              imx[(n-1)*n+n-1] /= 3 ;
//              imy[(n-1)*n+n-1] /= 3;

  /* Debruiter lena */
  debruit_local(n,imx,imy,10,58,61,71);
  debruit_local(n,imx,imy,44,118,86,131);
  debruit_local(n,imx,imy,124,246,141,248);
  debruit_local(n,imx,imy,57,206,73,211);
  debruit_local(n,imx,imy,122,331,140,334);
  debruit_local(n,imx,imy,374,178,391,182);
  debruit_local(n,imx,imy,470,386,482,394);
  debruit_local(n,imx,imy,486,443,489,456);
  debruit_local(n,imx,imy,342,303,460,305);
  debruit_local(n,imx,imy,376,265,390,268);
  debruit_local(n,imx,imy,160,392,169,395);
  debruit_local(n,imx,imy,128,445,135,448);
  debruit_local(n,imx,imy,344,118,351,121);
  debruit_local(n,imx,imy,377,64,385,68);

  /* Filtrage dans le domaine fréquentiel */

  /* Filtre Idéal */
//  int D = 130;
//  decal_origine(imx,n);
//  decal_origine(imy,n);
//  for (int i=0; i<n; i++)
//      for (int j=0; j<n ; j++) {
//          if (distance(i-n/2,j-n/2,0,0)<D) continue;
//          imx[i*n+j] = 0;
//          imy[i*n+j] = 0;
//      }
//  decal_origine(imx,n);
//  decal_origine(imy,n);
    
  /* Filtre de Butterworth */
//  int D = 10;
//  int N = 1;
//  decal_origine(imx,n);
//  decal_origine(imy,n);
//  for (int i=0; i<n; i++)
//      for (int j=0; j<n ; j++) {
//          imx[i*n+j] *= 1/(1+pow((distance(i-n/2,j-n/2,0,0)/D),2*N));
//          imy[i*n+j] *= 1/(1+pow((distance(i-n/2,j-n/2,0,0)/D),2*N));
//      }
//  decal_origine(imx,n);
//  decal_origine(imy,n);

  /* Filtre Gaussien */
//  int D = 50;
//  decal_origine(imx,n);
//  decal_origine(imy,n);
//  for (int i=0; i<n; i++)
//      for (int j=0; j<n ; j++) {
//          imx[i*n+j] *= exp(-pow(distance(i-n/2,j-n/2,0,0),2)/(2*pow(D,2)));
//          imy[i*n+j] *= exp(-pow(distance(i-n/2,j-n/2,0,0),2)/(2*pow(D,2)));
//      }
//  decal_origine(imx,n);
//  decal_origine(imy,n);

  /* Filtre Gaussien anisotrope */
//  int D = 100;
//  decal_origine(imx,n);
//  decal_origine(imy,n);
//  for (int i=0; i<n; i++)
//      for (int j=0; j<n ; j++) {
//          imx[i*n+j] *= exp(-pow(i-n/2,2)/(2*pow(D,2))) * exp(-pow(j-n/2,2)/(2*pow(D,2)));
//          imy[i*n+j] *= exp(-pow(i-n/2,2)/(2*pow(D,2))) * exp(-pow(j-n/2,2)/(2*pow(D,2)));
//      }
//  decal_origine(imx,n);
//  decal_origine(imy,n);


  /* sauvegarde dans un fichier */
  printf("\n Sauvegardez l'image de la FFT sous fft-im.pgm ");
  strcpy(fileName, "fft_im.pgm");
  writePGM_Picture(fileName, im2, n, n);

    
  /* calcul de la FFT inverse */
  fft_2D_inv(imx,imy,n);

  /* ecriture dans une image */
  for (i=0;i<n;i++){
    for(j=0;j<n;j++){
      im2[i*n+j]  = (unsigned char) MAX(0,(imx[n*i+j]));
    }
  }
  /* sauvegarde dans un fichier */
  printf("\n Sauvegardez l'image de la FFT inverse sous fft-im-inv.pgm ");  
  strcpy(fileName, "fft_im_inv.pgm");
  writePGM_Picture(fileName, im2, n, n);

  /* EQM */
  unsigned char *imo = new unsigned char [n*n];
  unsigned char *imf = new unsigned char [n*n];
  strcpy(fileName, "./images/lena.pgm");
  readPGM_Picture(fileName, imo, n, n);
  strcpy(fileName, "./fft_im_inv.pgm");
  readPGM_Picture(fileName, imf, n, n);

  printf("\n EQM : %f\n",eqm(512,imo,imf));


  delete [] imx;
  delete [] imy;
  delete [] immod;

  delete [] im1;
  delete [] im2;

}

/************** FIN FFT_IM *************************************************/

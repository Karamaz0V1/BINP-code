#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "imagesRW.h"



unsigned char clamp(double val) {
    if ((unsigned char)val>255) printf("Ouais, va falloir programmer clamp.\n");
    return (unsigned char)val;
}

// Calcul du gradient de imgIn  (Attention aux bords)
void IMgradient (unsigned char *imgIn, unsigned char *imgOut, int sizeX, int sizeY)
{
  double a[sizeX*sizeY];
  double atmp[sizeX*sizeY];
  double b[sizeX*sizeY];
  double btmp[sizeX*sizeY];

  int I = sizeX;
  int J = sizeY;

  // Calcul de Hx
  for (int i=1; i<I-1; i++)
      for (int j=0; j<J; j++)
          atmp[i*J+j] = imgIn[(i-1)*J+j] - imgIn[(i+1)*J+j];
  for (int i=0; i<I; i++)
      for (int j=1; j<J-1; j++)
          a[i*J+j] = atmp[i*J+j-1] + 2*atmp[i*J+j] + atmp[i*J+j+1];

  // Calcul de Hy
  for (int i=1; i<I-1; i++)
      for (int j=0; j<J; j++)
          btmp[i*J+j] = imgIn[(i-1)*J+j] + 2*imgIn[i*J+j] + imgIn[(i+1)*J+j];
  for (int i=0; i<I; i++)
      for (int j=1; j<J-1; j++)
          b[i*J+j] = btmp[i*J+j-1] - btmp[i*J+j+1];

  // Calcul de G
  for (int i=0; i<I; i++)
      for (int j=0; j<J; j++)
          imgOut[i*J+j] = clamp(sqrt(pow(a[i*J+j],2)+pow(b[i*J+j],2)));
}

double min_previous(double *score, double &min, int &addr_i_min, int i, int j) {
        min = score[(i-1)*sizeY+j-1];
        for(int precedent=0; precedent<2; precedent++)
            if (score[(i+precedent)*sizeY+j-1]<min) {
                min = score[(i+precedent)*sizeY+j-1];
                addr_i_min = i+precedent;
            }
}

// Recherche du chemin d'energie minimale dans imgIn 
void min_path(unsigned char *imgIn, int *posX, int *posY, int sizeX, int sizeY) 
{
    double filtre[sizeX*sizeY];
    double score[sizeX*sizeY];

    for (int i=0; i<sizeY; i++)
        score[i*sizeY] = imgIn[i*sizeY];

    for (int j=1; j<sizeX; j++)
        for (int i=1; i<sizeY-1; i++) {
            }
        }
}



int main(int argc, char **argv)
{
 
  // Lecture de l'image à redimensionner
  char fileName[250];
  //strcpy(fileName, "./test.pgm");
  strcpy(fileName, "./images/loup.pgm");
  int I = 425;
  int J = 290;
  unsigned char * im1 = new unsigned char [J*I];
  unsigned char * ime = new unsigned char [J*I];
  printf("\n Ouverture de %s de taille [%d,%d]", fileName, I, J);
  readPGM_Picture(fileName, im1, J, I);

  
  // Lecture d'un masque si besoin

  // 1) Calculer la matrice d'énergie de l'image 

  IMgradient(im1,ime,I,J);

  strcpy(fileName, "energie.pgm");
  writePGM_Picture(fileName, ime, J, I);

  // 2) Déterminer le chemin d'énergie minimale 



  // 3) L'enlever de l'image 



    return 0;
}

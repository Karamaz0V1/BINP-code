#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "imagesRW.h"

#include <iostream>



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

  int J = sizeX;
  int I = sizeY;

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

// Renvoi la valeur minimum des prédecesseurs et son adresse &min et &addr_i_min
void min_previous(double *score, double &min, int &addr_i_min, int sizeX, int i, int j) {
        min = score[(i-1)*sizeX+j-1];
        for(int precedent=0; precedent<2; precedent++)
            if (score[(i+precedent)*sizeX+j-1]<min) {
                min = score[(i+precedent)*sizeX+j-1];
                addr_i_min = i+precedent;
            }
        std::cout<<score[(i+0)*sizeX+j-1]<<" : "<<min<<endl;
}

// Recherche du chemin d'energie minimale dans imgIn 
void min_path(unsigned char *imgIn, int *seam, int sizeX, int sizeY) 
{
    double score[sizeX*sizeY];
    int addr_score[sizeX*sizeY];

    // Initialisation de la première colonne du score
    for (int i=0; i<sizeY; i++)
        score[i*sizeX] = imgIn[i*sizeX];

    // Calcul des scores
    for (int j=1; j<sizeX; j++) {
        for (int i=1; i<sizeY-1; i++) {
            min_previous(score,score[i*sizeX+j],addr_score[i*sizeX+j],sizeX,i,j);
            //std::cout<<score[i*sizeX+j]<<" ";
        }
        //std::cout<<std::endl;
    }
    

    // Repère la sortie de la couture la plus faible
    double min = score[1*sizeX+sizeX-1];
    for (int i=2; i<sizeY-1; i++)
        if (score[i*sizeX+sizeX-1]<min) {
            min = score[i*sizeX+sizeX-1];
            seam[sizeX-1] = addr_score[i*sizeX+sizeX-1];
        }

    // Relève la couture la plus faible
    for (int j=sizeX-2; j>=0; j--)
        seam[j] = addr_score[seam[j+1]];
}



int main(int argc, char **argv)
{
 
  // Lecture de l'image à redimensionner
  char fileName[250];
  //strcpy(fileName, "./test.pgm");
  strcpy(fileName, "./images/loup.pgm");
  int sizeY = 425;
  int sizeX = 290;
  unsigned char * im1 = new unsigned char [sizeX*sizeY];
  unsigned char * ime = new unsigned char [sizeX*sizeY];
  printf("\n Ouverture de %s de taille [%d,%d]", fileName, sizeY, sizeX);
  readPGM_Picture(fileName, im1, sizeX, sizeY);

  
  // Lecture d'un masque si besoin

  // 1) Calculer la matrice d'énergie de l'image 

  std::cout<<"Calcul du gradient \n";
  IMgradient(im1,ime,sizeX,sizeY);

  std::cout<<"Écriture du gradient \n";
  strcpy(fileName, "energie.pgm");
  writePGM_Picture(fileName, ime, sizeX, sizeY);

  // 2) Déterminer le chemin d'énergie minimale 

  std::cout<<"Min path \n";
  int seam[sizeX];
  min_path(ime, seam, sizeX, sizeY);

  // 3) L'enlever de l'image 
  //rm_seam(im1,ime,
  //
  for (int i=0; i<sizeX; i++)
      std::cout<<seam[i]<<" ";



    return 0;
}

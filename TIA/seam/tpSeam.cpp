#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "imagesRW.h"

#include <iostream>
#include <limits>



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
        addr_i_min = i-1;
        for(int precedent=0; precedent<2; precedent++)
            if (score[(i+precedent)*sizeX+j-1]<min) {
                min = score[(i+precedent)*sizeX+j-1];
                addr_i_min = i+precedent;
            }
}

// Recherche du chemin d'energie minimale dans imgIn 
void min_path(unsigned char *imgIn, int *seam, int sizeX, int sizeY) 
{
    double score[sizeX*sizeY];
    int addr_score[sizeX*sizeY];

    std::cout<<"\tbords"<<std::endl;
    // Initialisation des scores (aux bords)
    for (int i=0; i<sizeY; i+=sizeY-1) 
        for (int j=0; j<sizeX; j++)
            score[i*sizeX+j] = std::numeric_limits<double>::max();

    std::cout<<"\t1er col"<<std::endl;
    // Initialisation de la première colonne du score
    for (int i=0; i<sizeY; i++)
        score[i*sizeX] = imgIn[i*sizeX];

    std::cout<<"\tscores"<<std::endl;
    // Calcul des scores
    for (int j=1; j<sizeX; j++)
        for (int i=1; i<sizeY-1; i++) {
            min_previous(score,score[i*sizeX+j],addr_score[i*sizeX+j],sizeX,i,j);
            score[i*sizeX+j]+=imgIn[i*sizeX+j];
        }

    std::cout<<"\tsortie"<<std::endl;
    // Repère la sortie de la couture la plus faible
    double min = score[1*sizeX+sizeX-1];
    for (int i=2; i<sizeY-1; i++)
        if (score[i*sizeX+sizeX-1]<min) {
            min = score[i*sizeX+sizeX-1];
            seam[sizeX-1] = addr_score[i*sizeX+sizeX-1];
        }

    std::cout<<"\tcouture"<<std::endl;
    // Relève la couture la plus faible
    for (int j=sizeX-2; j>=0; j--)
        seam[j] = addr_score[seam[j+1]*sizeX+j];
}

// Copie la colone de 'im1' dans 'im2' en enlevant le pixel 'pixi' 'pixj'
void cp_col(unsigned char * im1, unsigned char * im2, int pixi, int pixj, int sizeX, int sizeY) {
    for (int i=0; i<sizeY; i++) {
        //std::cout<<pixi<<" : "<<i-((int)i>pixi)<<":"<<i<<std::endl;
        im2[(i-(i>pixi))*sizeX+pixj] = im1[i*sizeX+pixj];
    }
}

// Enleve la couture 'seam' de l'image 'im1'
void del_seam(unsigned char * im1, unsigned char *im2, int * seam, int sizeX, int sizeY) {
    for (int j=0; j<sizeX; j++) {
        im1[seam[j]*sizeX+j] = (unsigned char) 255;
        cp_col(im1, im2, seam[j], j, sizeX, sizeY);
    }
}

// Reduit de n pixels la hauteurs de l'image
void reduce(unsigned char **im1, int n, int &sizeX, int &sizeY) {
    for (int i=0; i<n; i++) {
        //std::cout<<i<<std::endl;
        unsigned char * ime = new unsigned char [sizeX*sizeY];
        unsigned char * im2 = new unsigned char [sizeX*(sizeY-1)];
        //std::cout<<"Gradient"<<std::endl;
        IMgradient(*im1,ime,sizeX,sizeY);
        int seam[sizeX];
        //std::cout<<"Seam"<<std::endl;
        min_path(ime, seam, sizeX, sizeY);
        //std::cout<<"Del"<<std::endl;
        del_seam(*im1,im2,seam,sizeX,sizeY);
        sizeY--;
        delete[] *im1;
        delete[] ime;
        *im1 = im2;
    }
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
  unsigned char * im2 = new unsigned char [sizeX*(sizeY-1)];
  unsigned char * ime = new unsigned char [sizeX*sizeY];
  printf("\n Ouverture de %s de taille [%d,%d]", fileName, sizeY, sizeX);
  readPGM_Picture(fileName, im1, sizeX, sizeY);
  
  // Lecture d'un masque si besoin

  /*
  // 1) Calculer la matrice d'énergie de l'image 
  IMgradient(im1,ime,sizeX,sizeY);

  strcpy(fileName, "energie.pgm");
  writePGM_Picture(fileName, ime, sizeX, sizeY);

  // 2) Déterminer le chemin d'énergie minimale 
  int seam[sizeX];
  min_path(ime, seam, sizeX, sizeY);

  // 3) L'enlever de l'image 
  del_seam(im1,im2,seam,sizeX,sizeY);
  //*/
  reduce(&im1,99,sizeX,sizeY);

  strcpy(fileName, "reduced.pgm");
  writePGM_Picture(fileName, im1, sizeX, sizeY-1);


    return 0;
}

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

// QUESTION 2 : LIMITE DE PERCEPTION VISUELLE
void question2(){

}

// QUESTION 3 : PERCEPTION DES COULEURS
void question3(){

}

// QUESTION 4 : ILLUSION DU GRADIENT
void question4(){

}

// QUESTION 5 : BANDES DE MACH
void question5(){

}

// QUESTION 6 : GRILLE DE HERMAN
void question6(){

}

// QUESTION 7 : EFFET DE MASQUAGE
void question7(){

}


int main(int argc, char **argv)
{

  cout << "BINP TP1 : PERCEPTION VISUELLE " << endl ;
  cout << "--" << endl ;


  // creation du menu
  int choix=0;
  while(choix<7) {

    cout << "1. Limite de perception visuelle" <<endl ;
    cout << "2. Perception des couleurs"<<endl;
	cout << "3. Illusion du gradient" << endl;
    cout << "4. Bandes de Mach"<<endl;
    cout << "5. Grille de Herman"<<endl;
    cout << "6. Effet de masquage"<<endl;
    cout << "7. Quitter"<<endl;

    cin >> choix ;

    switch(choix) {
    case 1:
      question2();
      break;

    case 2:
      question3();
      break;

    case 3:
      question4();
      break;

    case 4:
      question5();
      break;

    case 5:
      question6();
	  break;
	  
    case 6:
      question7();	  
	  
    default:
      break;
    }
  }

  cout << "Fin du programme " << endl ;
  return(0);
}
















#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>
#include "operateurs_morpho_binaire.h"
#include "traitements_morpho.h"
#include "morpho_fonctionnelle.h"


////////////////////////////////////////////////
//
//			TP MORPHOLOGIE MATHEMATIQUE
//
////////////////////////////////////////////////
//
//	NOMS-PRENOMS :
// -
// - 
//
////////////////////////////////////////////////


  //---------------------------------------------------//
  // FONCTIONS FOURNIES
  //---------------------------------------------------//


// La fonction rectangle cree une matrice binaire de taille n_l*n_c  fond noir (0) avec un rectangle
// blanc (255) dont le coin haut gauche est donne par les coordonnees i et j, et de
// largeur et longueur respectives lx et ly

imat rectangle(int n_l, int n_c, int i, int j, int lx, int ly){
	
	imat out = imat_new_zeros(n_l,n_c);
	int k,l;
	for(k=i;k<i+lx;k++){
		for(l=j;l<j+ly;l++){
			out[k][l] = 255;
		}
	}
	return out;
	
}

// Fonction d'affichage d'une image sur sortie standard
void affiche(imat im){
	int i,j;
	printf("\n ");
    for(i=0;i<imat_height(im);i++){
        for(j=0;j<imat_width(im);j++){
            printf("%d ",im[i][j]);
        }
		printf("\n ");
    }
}


//---------------------------------------------------//
// EROSION, DILATATION, OUVERTURE, FERMETURE
//	-> operateurs_morpho_binaire.c
//---------------------------------------------------//

//---------------------------------------------------//
// TOUT OU RIEN, SQUELETTISATION, PROBLEME
//	-> traitements_morpho.c
//---------------------------------------------------//

//---------------------------------------------------//
//  MORPHOLOGIE FONCTIONNELLE
//	-> moorpho_fonctionnelle.c
//---------------------------------------------------//

  //---------------------------------------------------//
  // PROGRAMME PRINCIPAL
  //---------------------------------------------------//

int main( int argc, char ** argv )
{
	parser_t * parser = parser_init( argc, argv,  /* Command line arguments */
									"tp_morpho.param", /* Parameter file    */
									NULL );      /* Default arguments */
	
	
	// lecture et affichage d'une image de test et des masques a partir du fichier de parametre
	imat imtest      = parser_get_imat( parser, "i_m" );
	imat masque      = parser_get_imat( parser, "masque" );
	imat masques[8];
	masques[0] = parser_get_imat( parser, "es1" );
	masques[1] = parser_get_imat( parser, "es2" );
	masques[2] = parser_get_imat( parser, "es3" );
	masques[3] = parser_get_imat( parser, "es4" );
	masques[4] = parser_get_imat( parser, "es5" );
	masques[5] = parser_get_imat( parser, "es6" );
	masques[6] = parser_get_imat( parser, "es7" );
	masques[7] = parser_get_imat( parser, "es8" );
	
	printf("\n affichage image test chargee :");
	affiche(imtest);
	printf("\n affichage de es3 : ");
	affiche(masques[2]);
	
	
	// lecture image
	imat im=imat_pgm_read("../images/image1_bin.pgm");//("../images/test_operateur_bin.pgm");
	if(im==NULL) {
		perror("imat_pgm_read");
		return(EXIT_FAILURE);
	}
	
	//imat im=rectangle(500,500,100,100,300,300);
	
	printf("\n Taille image  chargee : height(im) = %d\twidth(im) = %d\n", imat_height (im), imat_width (im));	 
	
	
	//im=squelette(im,masques);
	nbCarres(im);
	printf("Je suis là");
	// A COMPLETER
	
	
	// sauvegarde
	//imat_pgm_write("../results/out.pgm",im);
	
	
	// liberation memoire
	imat_delete(im);
	imat_delete(imtest);
	imat_delete(masque);
	int k;
	for (k=0; k<8; k++) imat_delete(masques[k]);
	
	return 0;
}
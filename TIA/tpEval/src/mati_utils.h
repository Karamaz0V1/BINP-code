/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __MATI_UTILS_H__
#define __MATI_UTILS_H__

#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>

/** avec un filtre 1D **/
imat filtrage_monodimensionnel(imat image, imat filtre);

/** avec un filtre 2D separable, filtre param 1D **/
imat filtrage_bidimensionnel(imat image, imat filtre);

/** avec un filtre 2D **/
imat filtrage_bidimensionnel_inseparable(imat image, imat filtre);

/** avec un filtre reel 2D **/
imat fltrage_bidimensionnel_inseparable(imat image, mat filtre);

/** Limite la valeur max de l'image à 255 **/
int clamp(int val);

/** Clamp image **/
imat imat_clamp(imat image);

/** Multiplie l'image par coeff **/
imat imat_coeff(imat image, float coeff);

/** Valeurs absolue dans l'image **/
imat imat_abs(imat image);

/** Additione 2 images en bornant le resultat **/
imat imat_add_clamp(imat image1, imat image2);

/** Recalibre proportionellement les valeurs entre 0 et 255 **/
imat imat_rescale_value(imat image);

/** Detecte les passages par zéro de image, selon seuil **/
imat imat_zero(imat image, int seuil);

/** Fait un seuillage de image selon la valeur seuil **/
imat imat_seuil(imat image, int seuil);

#endif /* __MATI_UTILS_H__ */

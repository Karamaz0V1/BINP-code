/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "mati_utils.h"

#include <it/io.h>
#include <it/mat.h>
#include <it/parser.h>

imat filtrage_monodimensionnel(imat image, imat filtre) {
    int i, j, j_f;
    imat tmp = imat_clone(image);
    int offset = imat_width(filtre)/2;

    int coeff = 0;
    for (j=0; j<imat_width(filtre); j++)
        coeff+=filtre[0][j];

    for (i=0; i<imat_height(image); i++)
        for (j=offset; j<imat_width(image)-offset; j++) {
            int value = 0;
            for (j_f=0; j_f<imat_width(filtre); j_f++)
                value+=image[i][j+j_f-offset] * filtre[0][j_f];
            tmp[i][j] = value / coeff;
        }

    return tmp;
}

imat filtrage_bidimensionnel(imat image, imat filtre) {
    imat tmp = filtrage_monodimensionnel(image, filtre);
    imat transpose = imat_new_transpose(tmp);
    filtrage_monodimensionnel(transpose, filtre);
    imat res = imat_new_transpose(transpose);
    imat_delete(transpose);
    imat_delete(tmp);
    return res;
}

int clamp(int val) {
    if (val > 255)
        return 255;
    else
        return val;
}

imat imat_clamp(imat image) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = clamp(image[i][j]);
    return tmp;
}

imat filtrage_bidimensionnel_inseparable(imat image, imat filtre) {
    int i, j, i_f, j_f;
    imat tmp = imat_clone(image);
    int offset = imat_width(filtre)/2;

    int coeff = 0;
    for (i=0; i<imat_height(filtre); i++)
        for (j=0; j<imat_width(filtre); j++)
            coeff+=filtre[i][j];
    if (coeff==0) coeff = 1;

    for (i=offset; i<imat_height(image)-offset; i++)
        for (j=offset; j<imat_width(image)-offset; j++) {
            int value = 0;
            for (i_f=0; i_f<imat_height(filtre); i_f++)
                for (j_f=0; j_f<imat_width(filtre); j_f++)
                    value+=image[i+i_f-offset][j+j_f-offset] * filtre[i_f][j_f];
            tmp[i][j] = clamp(value / coeff);
        }

    return tmp;
}

imat fltrage_bidimensionnel_inseparable(imat image, mat filtre) {
    int i, j, i_f, j_f;
    imat tmp = imat_clone(image);
    int offset = mat_width(filtre)/2;

    int coeff = 0;
    for (i=0; i<mat_height(filtre); i++)
        for (j=0; j<mat_width(filtre); j++)
            coeff+=filtre[i][j];
    if (coeff==0) coeff = 1;

    for (i=offset; i<imat_height(image)-offset; i++)
        for (j=offset; j<imat_width(image)-offset; j++) {
            int value = 0;
            for (i_f=0; i_f<mat_height(filtre); i_f++)
                for (j_f=0; j_f<mat_width(filtre); j_f++)
                    value+=image[i+i_f-offset][j+j_f-offset] * filtre[i_f][j_f];
            tmp[i][j] = clamp(value / coeff);
        }

    return tmp;
}

imat imat_coeff(imat image, float coeff) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = image[i][j] * coeff;
    return tmp;
}

imat imat_abs(imat image) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = abs(image[i][j]);
    return tmp;
}

imat imat_add_clamp(imat image1, imat image2) {
    int i, j;
    imat tmp = imat_clone(image1);
    for (i=0; i<imat_height(image1); i++)
        for (j=0; j<imat_width(image1); j++)
            tmp[i][j] = clamp(image1[i][j] + image2[i][j]);
    return tmp;
}

imat imat_rescale_value(imat image) {
    int i, j;
    int min = imat_min(image);
    int max = imat_max(image);
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = (image[i][j]-min)*255/(max-min);
    return tmp;
}

/** Detecte les passages par zéro de image **/
imat imat_zero(imat image, int seuil) {
    int i, j, I, J;
    imat tmp = imat_new_zeros(imat_height(image), imat_width(image));
    for (i=1; i<imat_height(image)-1; i++)
        for (j=1; j<imat_width(image)-1; j++) {
            int min = 0;
            int max = 0;
            for (I=-1; I<=1; I++)
                for (J=-1; J<=1; J++) {
                    if (image[i+I][j+J] < min) min = image[i+I][j+J];
                    if (image[i+I][j+J] > max) max = image[i+I][j+J];
                }
            if (max-min > seuil) tmp[i][j] = 255;
        }
    return tmp;
}

imat imat_seuil(imat image, int seuil) {
    int i, j;
    imat tmp = imat_clone(image);
    for (i=0; i<imat_height(image); i++)
        for (j=0; j<imat_width(image); j++)
            tmp[i][j] = (image[i][j] > seuil) * 255;
    return tmp;
}

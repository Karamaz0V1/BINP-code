#include "models/ResizeModel.h"

#include "ImageConverter.h"

ResizeModel::ResizeModel()
{
}

void ResizeModel::setScaleFactor(const double & factor) {
    m_factor = factor;
}

void ResizeModel::setInput(const vpImage<vpRGBa> &img) {
    m_img = img;
}

void ResizeModel::run(vpImage<vpRGBa> image,double factor) {
    setScaleFactor(factor);
    setInput(image);
    if(m_factor>0) {
        agrandissement_lineaire(m_img);
    }
    else {
        decimation_lineaire(m_img);
    }
}

vpImage<vpRGBa> ResizeModel::output(){
    return m_img;
}

/** BINP **/


/** Réduit lataille de l'image en prenant une valeur sur 2 **/
void ResizeModel::decimation_simple(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++)
        for (int j=0; j<Is.getWidth(); j++)
            Is[i][j] = I[i*2][j*2];
    I = Is;
}

/** Réduit la taille de l'image en moyennant les valeurs d'origine **/
void ResizeModel::decimation_lineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()/2,I.getWidth()/2);
    for (int i=0; i<Is.getHeight(); i++)
        for (int j=0; j<Is.getWidth(); j++) {
            Is[i][j].R = (I[i*2][j*2].R+I[i*2+1][j*2].R+I[i*2][j*2+1].R+I[i*2+1][j*2+1].R) / 4;
            Is[i][j].G = (I[i*2][j*2].G+I[i*2+1][j*2].G+I[i*2][j*2+1].G+I[i*2+1][j*2+1].G) / 4;
            Is[i][j].B = (I[i*2][j*2].B+I[i*2+1][j*2].B+I[i*2][j*2+1].B+I[i*2+1][j*2+1].B) / 4;
        }

    I = Is;
}

/** Effectue un agrandissement en dupliquant les pixels de l'image d'origine **/
void ResizeModel::agrandissement_simple(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()*2,I.getWidth()*2);
    for (int i=0; i<Is.getHeight(); i++)
        for (int j=0; j<Is.getWidth(); j++) {
            Is[i][j].R = I[i/2][j/2].R;
            Is[i][j].G = I[i/2][j/2].G;
            Is[i][j].B = I[i/2][j/2].B;
        }
    I = Is;
}

/** retourne le pixel aux coordonées i, j; en appliquant l'effet miroirs sur les bords
 *  de l'image quand les coordonnées sont trop grandes/petites. */
const vpRGBa & ResizeModel::access(const vpImage<vpRGBa> & I, int i, int j) {
    if (i >= (int)I.getHeight()) i = 2 * I.getHeight() - i -1;
    if (j >= (int)I.getWidth()) j = 2 * I.getWidth() - j -1;
    return I[(int)abs(i)][(int)abs(j)];
}

/** Donne la valeur du pixel i, j après interpolation bilinéaire **/
vpRGBa ResizeModel::interpol(const vpImage<vpRGBa> & src, int i, int j) {
    vpRGBa sortie;
    sortie.R = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).R * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).R * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).R * 0.25 + access(src,i/2,j/2).R * 0.75);
    sortie.G = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).G * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).G * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).G * 0.25 + access(src,i/2,j/2).G * 0.75);
    sortie.B = 0.25 * (access(src,i/2 - 1 + (i%2) * 2,j/2 - 1 + (j%2) *2).B * 0.25 + access(src,i/2 - 1 + (i%2) * 2,j/2).B * 0.75) + 0.75 * (access(src,i/2,j/2 - 1 + (j%2) * 2).B * 0.25 + access(src,i/2,j/2).B * 0.75);
    return sortie;
}

/** Calcule l'agrandissement linéaire d'une image **/
void ResizeModel::agrandissement_lineaire(vpImage<vpRGBa> & I) {
    vpImage<vpRGBa> Is(I.getHeight()*2,I.getWidth()*2);
    for (int i=0; i<Is.getHeight(); i++)
        for (int j=0; j<Is.getWidth(); j++)
            Is[i][j] = interpol(I, i, j);
    I = Is;
}

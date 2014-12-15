#ifndef RESIZEMODEL_H
#define RESIZEMODEL_H

#include "AbstractModel.h"

#include <visp/vpImage.h>

class ResizeModel : public AbstractModel
{
public:
    ResizeModel();
    void setScaleFactor(const double & factor);
    void setInput(const vpImage<vpRGBa> &img);
    void run(vpImage<vpRGBa> image,double factor);
    vpImage<vpRGBa> output();
private:
    void decimation_simple(vpImage<vpRGBa> & I);
    void decimation_lineaire(vpImage<vpRGBa> & I);
    void agrandissement_simple(vpImage<vpRGBa> & I);
    const vpRGBa & access(const vpImage<vpRGBa> & I, int i, int j);
    vpRGBa interpol(const vpImage<vpRGBa> & src, int i, int j);
    void agrandissement_lineaire(vpImage<vpRGBa> & I);

    vpImage<vpRGBa> m_img;
    double m_factor;
};

#endif // RESIZEMODEL_H

#include "InpaintingModel.h"

#define _USE_MATH_DEFINES
#include <cmath>

#include <visp/vpImageFilter.h>
#include <visp/vpImageConvert.h>
#include <visp/vpException.h>


#include <QDebug>

class InpaintingModelPrivate
{
public :
    vpImage<vpRGBa> input;
    vpImage<unsigned char> mask;
    vpImage<vpRGBa> output;
    unsigned int kernel_size;

    InpaintingModelPrivate():kernel_size(7){}

    vpImage<vpRGBa> inPaintingRGBA(const vpImage<vpRGBa> &inpt, const vpImage<unsigned char> &msk);
    vpImage<unsigned char> inPaintingMono(const vpImage<unsigned char> &inpt, const vpImage<unsigned char> &msk);

    void getGaussianKernel(double *filter, unsigned int size, double sigma = 0, bool normalize = true);
    void filter(const vpImage<double> &I, vpImage<double>& GI, const double *filter,unsigned  int size);
    void filterY(const vpImage<double> &I, vpImage<double>& dIy, const double *filter,unsigned  int size);
    void filterX(const vpImage<double> &I, vpImage<double>& dIx, const double *filter,unsigned  int size);

    static inline double filterX(const vpImage<double> &I,
                                 unsigned int r, unsigned int c,
                                 const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        result += filter[i]*(I[r][c+i] + I[r][c-i]) ;
      }
      return result+filter[0]*I[r][c];
    }

    static inline double filterXLeftBorder(const vpImage<double> &I,
                                           unsigned int r, unsigned int c,
                                           const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        if(c>i)
          result += filter[i]*(I[r][c+i] + I[r][c-i]) ;
        else
          result += filter[i]*(I[r][c+i] + I[r][i-c]) ;
      }
      return result+filter[0]*I[r][c];
    }

    static inline double filterXRightBorder(const vpImage<double> &I,
                                            unsigned int r, unsigned int c,
                                            const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        if(c+i<I.getWidth())
          result += filter[i]*(I[r][c+i] + I[r][c-i]) ;
        else
          result += filter[i]*(I[r][2*I.getWidth()-c-i-1] + I[r][c-i]) ;
      }
      return result+filter[0]*I[r][c];
    }

    static inline double filterY(const vpImage<double> &I,
                                 unsigned int r, unsigned int c,
                                 const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        result += filter[i]*(I[r+i][c] + I[r-i][c]) ;
      }
      return result+filter[0]*I[r][c];
    }

    static inline double filterYTopBorder(const vpImage<double> &I,
                                          unsigned int r, unsigned int c,
                                          const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        if(r>i)
          result += filter[i]*(I[r+i][c] + I[r-i][c]) ;
        else
          result += filter[i]*(I[r+i][c] + I[i-r][c]) ;
      }
      return result+filter[0]*I[r][c];
    }

    static inline double filterYBottomBorder(const vpImage<double> &I,
                                             unsigned int r, unsigned int c,
                                             const double *filter,unsigned  int size)
    {
      double result;
      result = 0;

      for(unsigned int i=1; i<=(size-1)/2; i++)
      {
        if(r+i<I.getHeight())
          result += filter[i]*(I[r+i][c] + I[r-i][c]) ;
        else
          result += filter[i]*(I[2*I.getHeight()-r-i-1][c] + I[r-i][c]) ;
      }
      return result+filter[0]*I[r][c];
    }
};

InpaintingModel::InpaintingModel(AbstractPresenter* parent): AbstractModel(parent),
    d(new InpaintingModelPrivate)
{
    qDebug() << "Constructing Pmaurel model...";
}


InpaintingModel::~InpaintingModel()
{
    delete d;
}

void InpaintingModel::setInput(const vpImage<vpRGBa> &img)
{
    d->input = img;
}

void InpaintingModel::setMask(const vpImage<unsigned char> &img)
{
    d->mask = img;
}

vpImage<vpRGBa> InpaintingModel::output() const
{
    return d->output;
}

void InpaintingModel::run()
{
    qDebug() << "Pmaurel inpainting";
    d->output = d->inPaintingRGBA(d->input, d->mask);
//    vpImageConvert::convert(d->mask, d->output);

    emit success();
}


vpImage<vpRGBa> InpaintingModelPrivate::inPaintingRGBA(const vpImage<vpRGBa> &inpt, const vpImage<unsigned char> &msk)
{
    // Allocate images:
    unsigned int h(inpt.getHeight()), w(inpt.getWidth());
    vpImage<vpRGBa> outpt(h,w);
    vpImage<unsigned char> inpt_R(h,w), inpt_G(h,w), inpt_B(h,w), inpt_A(h,w);
    for (int i=0; i<h ; i++)
    {
        for (int j=0; j<w ; j++)
        {
            inpt_R[i][j] = inpt[i][j].R;
            inpt_G[i][j] = inpt[i][j].G;
            inpt_B[i][j] = inpt[i][j].B;
            inpt_A[i][j] = inpt[i][j].A;
        }
    }


    // Process:
    inpt_R = this->inPaintingMono(inpt_R, msk);
    inpt_G = this->inPaintingMono(inpt_G, msk);
    inpt_B = this->inPaintingMono(inpt_B, msk);
    inpt_A = this->inPaintingMono(inpt_A, msk);

    // Construct output
    for (int i=0; i<h ; i++)
    {
        for (int j=0; j<w ; j++)
        {
            outpt[i][j].R = inpt_R[i][j];
            outpt[i][j].G = inpt_G[i][j];
            outpt[i][j].B = inpt_B[i][j];
            outpt[i][j].A = inpt_A[i][j];
        }
    }
    return outpt;
}

vpImage<unsigned char> InpaintingModelPrivate::inPaintingMono(const vpImage<unsigned char> &inpt, const vpImage<unsigned char> &msk)
{
    // Check sizes:
    unsigned int h, w;
    h = inpt.getHeight(), w = inpt.getWidth();
    if(msk.getHeight() != h || msk.getWidth() != w)
    {
        qDebug() << "from InpaintingModelPrivate::inPaintingMono -> input and mask have not the same sizes."
                 << "Can't perform inpainting...";

        return inpt;
    }

    // Allocate images:
    vpImage<unsigned char> outpt(h, w);
    vpImage<double> outpt_inpainted(h,w);
    vpImage<double> outpt_smoothed(h,w);
    for (int i=0; i<h ; i++)
        for (int j=0; j<w ; j++)
            outpt_inpainted[i][j] = inpt[i][j];


    // Allocate filter:
    double *fg = new double[(kernel_size + 1) / 2] ;
    this->getGaussianKernel(fg, kernel_size);
    // Process:
    double diff;
    do
    {
        diff = 0;
        InpaintingModelPrivate::filter(outpt_inpainted, outpt_smoothed, fg, kernel_size);

        for (int i=0; i<h ; i++)
        {
            for (int j=0; j<w ; j++)
            {
                if (msk[i][j])
                {
                    diff += std::abs(outpt_inpainted[i][j] - outpt_smoothed[i][j]);
                    outpt_inpainted[i][j] = outpt_smoothed[i][j];
                }
            }
        }
    }
    while(diff > 1);


    // construct outpt
    for (int i=0; i<h ; i++)
        for (int j=0; j<w ; j++)
            outpt[i][j] = std::floor(outpt_inpainted[i][j] + 0.5);
    return outpt;
}

void InpaintingModelPrivate::getGaussianKernel(double *filter, unsigned int size, double sigma, bool normalize)
{
  if (size%2 != 1)
    qDebug() << "Bad kernel size, it has to be odd.";

  if (sigma<= 0)
    sigma = (size-1)/6.0;

  int middle = (int)(size-1)/2;
  double sigma2 = vpMath::sqr(sigma);
  for( int i=0; i<= middle; i++)
  {
    filter[i] = (1./(sigma*sqrt(2.*M_PI)))*exp(-(i*i)/(2.*sigma2));
  }
  if (normalize) {
    //renormalization
    double sum=0;
    for(int i=1; i<=middle; i++)
    {
      sum += 2*filter[i] ;
    }
    sum += filter[0];

    for(int i=0; i<=middle; i++)
    {
      filter[i] = filter[i]/sum;
    }
  }
}

void InpaintingModelPrivate::filter(const vpImage<double> &I, vpImage<double>& GI, const double *filter,unsigned  int size)
{
  vpImage<double> GIx ;
  filterX(I, GIx,filter,size);
  filterY(GIx, GI,filter,size);
  GIx.destroy();
}

void InpaintingModelPrivate::filterX(const vpImage<double> &I, vpImage<double>& dIx, const double *filter,unsigned  int size)
{
  dIx.resize(I.getHeight(),I.getWidth()) ;
  for (unsigned int i=0 ; i < I.getHeight() ; i++)
  {
    for (unsigned int j=0 ; j < (size-1)/2 ; j++)
      dIx[i][j]=InpaintingModelPrivate::filterXLeftBorder(I,i,j,filter,size);
    for (unsigned int j=(size-1)/2 ; j < I.getWidth()-(size-1)/2 ; j++)
      dIx[i][j]=InpaintingModelPrivate::filterX(I,i,j,filter,size);
    for (unsigned int j=I.getWidth()-(size-1)/2 ; j < I.getWidth() ; j++)
      dIx[i][j]=InpaintingModelPrivate::filterXRightBorder(I,i,j,filter,size);
  }
}

void InpaintingModelPrivate::filterY(const vpImage<double> &I, vpImage<double>& dIy, const double *filter,unsigned  int size)
{
  dIy.resize(I.getHeight(),I.getWidth()) ;
  for (unsigned int i=0 ; i < (size-1)/2 ; i++)
    for (unsigned int j=0 ; j < I.getWidth() ; j++)
      dIy[i][j]=InpaintingModelPrivate::filterYTopBorder(I,i,j,filter,size);


  for (unsigned int i=(size-1)/2 ; i < I.getHeight()-(size-1)/2 ; i++)
    for (unsigned int j=0 ; j < I.getWidth() ; j++)
      dIy[i][j]=InpaintingModelPrivate::filterY(I,i,j,filter,size);

  for (unsigned int i=I.getHeight()-(size-1)/2 ; i < I.getHeight() ; i++)
    for (unsigned int j=0 ; j < I.getWidth() ; j++)
      dIy[i][j]=InpaintingModelPrivate::filterYBottomBorder(I,i,j,filter,size);
}

void InpaintingModel::setScaleFactor(const double & factor) {}

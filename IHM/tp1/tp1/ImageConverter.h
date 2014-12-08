#pragma once

#include <qimage.h>
#include <visp/vpImage.h>
class ImageConverter
{
public:
    static vpImage<vpRGBa> qImageToVpImageRGBA(QImage img)
    {
        vpImage<vpRGBa>  res(img.height(), img.width());
        for(int h = 0; h < img.height(); ++h)
        {
            for(int w = 0; w < img.width(); ++w)
            {
                QRgb qPix = img.pixel(w, h);
                vpRGBa vpPix(qRed(qPix), qGreen(qPix), qBlue(qPix), qAlpha(qPix));
                res[h][w] = vpPix;
            }
        }
        return res;
    }

    static QImage vpImageRGBAToQImage(vpImage<vpRGBa> img)
    {
        QImage res(img.getWidth(), img.getHeight(), QImage::Format_ARGB32);
        for(int h = 0; h < img.getHeight(); ++h)
        {
            for(int w = 0; w < img.getWidth(); ++w)
            {
                vpRGBa vpPix = img[h][w];
                QRgb qPix = qRgba(vpPix.R, vpPix.G, vpPix.B, vpPix.A);
                res.setPixel(w, h, qPix);
            }
        }
        return res;
    }

    static vpImage<unsigned char> qImageToVpImageUCHAR(QImage img)
    {
        vpImage<unsigned char>  res(img.height(), img.width());
        for(int h = 0; h < img.height(); ++h)
        {
            for(int w = 0; w < img.width(); ++w)
            {
                if(img.pixel(w, h) == qRgba(255,255,255,255))
                    res[h][w] = 255;
                else
                    res[h][w] = 0;
            }
        }
        return res;
    }

    static QImage vpImageUCHARToQImage(vpImage<unsigned char> img)
    {
        QImage res(img.getWidth(), img.getHeight(), QImage::Format_ARGB32);
        for(int h = 0; h < img.getHeight(); ++h)
        {
            for(int w = 0; w < img.getWidth(); ++w)
            {
                if (img[h][w] == 0)
                    res.setPixel(w, h, qRgba(0,0,0,255));
                else
                    res.setPixel(w, h, qRgba(255,255,255,255));
            }
        }
        return res;
    }

};

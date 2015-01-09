#pragma once

#include "AbstractModel.h"

#include <visp/vpImage.h>

#include "AbstractPresenter.h"

class InpaintingModelPrivate;
class InpaintingModel: public AbstractModel
{
    Q_OBJECT

public:
    InpaintingModel(AbstractPresenter *parent = NULL);
    virtual ~InpaintingModel();

public:
    virtual void run();

public:
    /**
     * Set the input image to modify.
     */
    void setInput(const vpImage<vpRGBa> &img);
    /**
     * Set the mask where to perform the inpainting on the input image.
     * The mask and the image to process have to have the same dimensions.
     */
    void setMask(const vpImage<unsigned char> &img);
    /**
     * Accessor to the image modify by the inpainting.
     * Return a copy of the input if run() has never been called.
     */
    vpImage<vpRGBa> output() const;

private:
    // Pointer to implementation:
    InpaintingModelPrivate *d;
};

/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __RESIZEPRESENTER_H__
#define __RESIZEPRESENTER_H__

class ResizePresenter: public AbstractPresenter {
   public:
        AbstractPresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget *parametersWidget);
        virtual ~AbstractPresenter();

    private:

    private slots:
        virtual void runModel();
        virtual void presentModelResults();
};


#endif /* __RESIZEPRESENTER_H__ */




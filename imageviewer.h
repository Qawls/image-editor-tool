#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#include <QPrinter>
#include <QVBoxLayout>
#include <QDialog>
#include "paintdraw.h"


class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QPushButton;
class QWidget;
class QVBoxLayout;
class QDialog;

class buttonsandarea;

class buttonsandarea : public QDialog
{
    Q_OBJECT
public:
    buttonsandarea(QDialog *parent=0);
    QPushButton *normal;
    //QPushButton *fittowindow;
    QPushButton *zoomin;
    QPushButton *zoomout;
    QLabel *imageLabel;

    QScrollArea *scrollArea;
    testdraw *newtest;


};

/*
class used
{
public:
    void zoomIn(buttonsandarea *work);
    void zoomOut(buttonsandarea *work);
    void normalSize(buttonsandarea *work);
    void scaleImage(buttonsandarea *work, double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
};
*/

/*
class combined:public QMainWindow,public QDialog
{
public:
    int c;
};
*/

class ImageViewer : public QMainWindow
{
    Q_OBJECT

public:
    int count;
    ImageViewer();

    buttonsandarea *workarea[20];
    //void scaleImage(testdraw *, double factor);
    //void adjustScrollBar(double factor);
    //bool linedecider;


private slots:
    void open();
    //void print();

    //void fitToWindow();

    void about();
    void ColorPanel();
    void PenWidthSetter();
    void linedrawdecider();
    void freehanddecider();

    void clearimagecaller();

    void zoomIncaller();
    void zoomOutcaller();
    void normalcaller();
    void cropcaller();
    //void rotatecaller();
   // void zoomOut();
    //void normalSize();



private:
    void createActions();
    void createMenus();
    //void updateActions();

   // void scaleImage(buttonsandarea *work, double factor);
 //   void adjustScrollBar(QScrollBar *scrollBar, double factor);

//#ifndef QT_NO_PRINTER
   // QPrinter printer;
//#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    //QAction *zoomInAct;
    //QAction *zoomOutAct;
    //QAction *normalSizeAct;
    //QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *ColorPanelAct;
    QAction *PenWidthAct;
    QAction *LineDrawAct;
    QAction *FreeHandAct;
    QAction *ClearImageAct;

    QAction *ZoomInAct;
    QAction *ZoomOutAct;
    QAction *NormalAct;
    //QAction *Rotate_90Act;

    QAction *CropAct;

    QTabWidget *tabwidget;

    QMenu *fileMenu;
    QMenu *PaintFunctionsMenu;
    QMenu *ZoomFunctionsMenu;
    QMenu *PhotoshopFunctionsMenu;
    //QMenu *viewMenu;
    QMenu *helpMenu;

};

#endif

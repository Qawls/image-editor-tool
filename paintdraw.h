#ifndef PAINTDRAW_H
#define PAINTDRAW_H

#include <QWidget>
#include <QtGui>

class QWidget;
class QImage;
class QPoint;
class QColor;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;

/*
class forimage:public QWidget
{
    Q_OBJECT
public:
    QImage *image;
    forimage(QWidget *parent=0);
};
*/

class testdraw: public QWidget
{
public:
    testdraw(QWidget *parent2=0);

/*
    forimage imageobj;
    QPushButton *colordialogbutton;
    QPushButton *penwidthbutton;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout;
    QVBoxLayout *mainlayout;
*/
    QPoint lastpoint;
    int penwidth;
    QColor pencolor;
    QImage image;
    QImage originalimage;
    bool drawing;
    void drawline(const QPoint &endPoint);
    void resizeImage(QImage *image, const QSize &newSize);
    void takeimage(QImage);
    void getpencolor(QColor);
    void getpenwidth(int);
    int currentpenwidth();

    bool linedraw;
    void linedrawset(bool);

    void clearimage();

    QImage returnimage();

    void getimage(QImage);

    void zoomerin();
    void zoomerout();
    void normal();
    void cropper();

    //void rotator();

    void cropswitcherreceiver(bool);


    int cropfactor;
    int cropdecider;

    bool cropswitcher;

    int zoomingfactorheight;
    int zoomingfactorwidth;

    QPoint lastPoint1;
    QPoint lastPoint2;


protected:

    void mousePressEvent(QMouseEvent *mouseevent);
    void mouseMoveEvent(QMouseEvent *mouseevent);
    void mouseReleaseEvent(QMouseEvent *mouseevent);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);


};


#endif // PAINTDRAW_H

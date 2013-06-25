#include "paintdraw.h"
#include <QtGui>

/*
forimage::forimage(QWidget *parent):QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
}
*/

testdraw::testdraw(QWidget *parent2): QWidget(parent2)
{
   /*
 colordialogbutton=new QPushButton("Color Dialog");
    penwidthbutton=new QPushButton("Pen Width");


    imageobj=new forimage;
*/


    setAttribute(Qt::WA_StaticContents);
    //pencolor=QColorDialog::getColor();
    pencolor=Qt::black;
    penwidth=2;

    drawing=false;
    linedraw=false;

    cropfactor=0;
    cropdecider=0;
    cropswitcher=false;

/*
    hlayout=new QHBoxLayout;
    vlayout=new QVBoxLayout;
    mainlayout=new QVBoxLayout;


    hlayout->addWidget(colordialogbutton);
    hlayout->addWidget(penwidthbutton);
    vlayout->addWidget(imageobj);

    mainlayout->addLayout(vlayout);
    mainlayout->addLayout(vlayout);

    setLayout(mainlayout);
*/
}

void testdraw::clearimage()
{
    image.fill(qRgb(255,255,255));
    update();

}

QImage testdraw::returnimage()
{
    return image;
}

int testdraw::currentpenwidth()
{
    return penwidth;
}

void testdraw::linedrawset(bool decision)
{
    linedraw=decision;
}

void testdraw::getpenwidth(int a)
{
    penwidth=a;
}


void testdraw::getpencolor(QColor colory)
{
    pencolor=colory;
}


void testdraw::getimage(QImage imager)
{
    image=imager;
    update();
}


void testdraw::takeimage(QImage imagery)
{
    originalimage=imagery;
    QSize newSize = imagery.size().expandedTo(size());
    resizeImage(&imagery, newSize);
    image = imagery;



    zoomingfactorheight=image.height();
    zoomingfactorwidth=image.width();

    update();
}


void testdraw::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0,0), *image);
    *image = newImage;
}


void testdraw::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, image, dirtyRect);
}


void testdraw::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());

        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void testdraw::mousePressEvent(QMouseEvent *mouseevent)
{


    if(mouseevent->button()==Qt::LeftButton)
    {
        lastpoint=mouseevent->pos();
        drawing=true;


        if(cropswitcher==true)
        {
        if(cropfactor==0)
        {
            lastPoint1 = mouseevent->pos();
            cropfactor=1;
            cropdecider++;
        }
        else
        {
            lastPoint2=mouseevent->pos();
            cropfactor=0;
            cropdecider++;
            cropswitcher=false;
        }
        }
    }

       if(cropdecider==2)
          {
           cropper();
           cropdecider=0;
          }


}


void testdraw::mouseMoveEvent(QMouseEvent *mouseevent)
{
    if((mouseevent->buttons()&Qt::LeftButton)&&drawing)
    {
        if(linedraw==false)
        drawline(mouseevent->pos());

    }
}

void testdraw::mouseReleaseEvent(QMouseEvent *mouseevent)
{
    if((mouseevent->button()==Qt::LeftButton)&&drawing==true)
    {
        drawing=false;
        drawline(mouseevent->pos());
    }
}

void testdraw::drawline(const QPoint &endpoint)
{
    QPainter painter(&image);

    painter.setPen(QPen(pencolor,penwidth,Qt::SolidLine,Qt::RoundCap,Qt::RoundJoin));

    painter.drawLine(lastpoint,endpoint);

    update();
    lastpoint=endpoint;
}

void testdraw::zoomerin()
{

    QImage newimage;
    zoomingfactorheight+=10;
    zoomingfactorwidth+=10;
    newimage=image.scaled(QSize(zoomingfactorwidth,zoomingfactorheight),Qt::IgnoreAspectRatio,Qt::FastTransformation);

    image=newimage;
    update();
}

void testdraw::zoomerout()
{


    QImage newimage;
    zoomingfactorheight-=10;
    zoomingfactorwidth-=10;
    newimage=image.scaled(QSize(zoomingfactorwidth,zoomingfactorheight),Qt::KeepAspectRatioByExpanding,Qt::FastTransformation);

    image=newimage;
    update();
}

void testdraw::normal()
{
    image=originalimage;
    update();
}

void testdraw::cropper()
{
    QImage newimg;
    newimg=image.copy(QRect::QRect(lastPoint1,lastPoint2));

    image=newimg;
    update();
}

void testdraw::cropswitcherreceiver(bool decisionforcrop)
{
    cropswitcher=decisionforcrop;
}

/*
void testdraw::rotator()
{
    QMatrix rm;
    rm.rotate(90);

    image=image.transformed(rm,Qt::FastTransformation);
    update();
}
*/

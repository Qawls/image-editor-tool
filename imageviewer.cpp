#include <QtGui>

#include "imageviewer.h"
#include "paintdraw.h"

double scaleFactor;

buttonsandarea::buttonsandarea(QDialog *parent):QDialog(parent)
{
    normal=new QPushButton("Normal");
    zoomin=new QPushButton("Zoom In");
    zoomout=new QPushButton("Zoom Out");
    //fittowindow=new QPushButton("Fit To Window");

    scrollArea=new QScrollArea;
    imageLabel=new QLabel;

    newtest=new testdraw;

    //QHBoxLayout *hlayout=new QHBoxLayout;

//    hlayout->addWidget(normal);
//    hlayout->addWidget(zoomin);
   // hlayout->addWidget(newtest);
    //hlayout->addWidget(fittowindow);

    scrollArea->setWidget(newtest);

    QVBoxLayout *vlayout=new QVBoxLayout;
    vlayout->addWidget(scrollArea);

    QVBoxLayout *mainlayout=new QVBoxLayout;

    mainlayout->addLayout(vlayout);
  //  mainlayout->addLayout(hlayout);

    setLayout(mainlayout);

}

ImageViewer::ImageViewer()
{
    count=0;
    workarea[count]=new buttonsandarea;




    //imageLabel->setBackgroundRole(QPalette::Base);
    workarea[count]->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    workarea[count]->imageLabel->setScaledContents(true);


    //scrollArea->setBackgroundRole(QPalette::Dark);

    //workarea[count]->scrollArea->setWidget(workarea[count]->newtest);

    tabwidget=new QTabWidget;
    setCentralWidget(tabwidget);
    tabwidget->addTab(workarea[count]->newtest,"Free Draw");

    createActions();
    createMenus();

    setWindowTitle(tr("Image Viewer"));
    resize(500, 400);
}

void ImageViewer::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage images(fileName);


        ZoomFunctionsMenu->setEnabled(true);

        if (images.isNull()) {
            QMessageBox::information(this, tr("Image Viewer"),
                                     tr("Cannot load %1.").arg(fileName));
            return;
        }

        /*
        imageLabel = new QLabel;
        //imageLabel->setBackgroundRole(QPalette::Base);
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        imageLabel->setScaledContents(true);

        scrollArea = new QScrollArea;
        //scrollArea->setBackgroundRole(QPalette::Dark);
        scrollArea->setWidget(imageLabel);

        */

        //setCentralWidget(tabwidget);

        count++;

        workarea[count]=new buttonsandarea;
        //workarea[count]->imageLabel->setPixmap(QPixmap::fromImage(images));

        workarea[count]->newtest->takeimage(images);

        //workarea[count]->imageLabel->setPixmap(QPixmap::fill((QWidget *)workarea[count]->newtest,0));


        /*
        scaleFactor = 1.0;
        workarea[count]->imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        workarea[count]->imageLabel->setScaledContents(true);
        */


/*
        normal=new QPushButton("Normal");
        fittowindow=new QPushButton("Fit To Window");
        zoomin=new QPushButton("Zoom In");
        zoomout=new QPushButton("Zoom out");



         vlayout=new QVBoxLayout;
        vlayout->addWidget(scrollArea);
        vlayout->addWidget(normal);
        vlayout->addWidget(fittowindow);
        vlayout->addWidget(zoomin);
        vlayout->addWidget(zoomout);



*/

        //workarea[count]->scrollArea->setWidget(workarea[count]->imageLabel);

        tabwidget->addTab(workarea[count]->newtest,fileName);
/*
        connect(workarea[count]->zoomin,SIGNAL(clicked()),workarea[count],SLOT(zoomIn(workarea[count])));
        connect(workarea[count]->zoomout,SIGNAL(clicked()),workarea[count],SLOT(zoomOut(workarea[count])));
        connect(workarea[count]->normal,SIGNAL(clicked()),workarea[count],SLOT(normalSize(workarea[count])));
*/
/*
        printAct->setEnabled(true);
        fitToWindowAct->setEnabled(true);
        updateActions();

        if (!fitToWindowAct->isChecked())
            workarea[count]->imageLabel->adjustSize();

*/

}
}

void ImageViewer::ColorPanel()
{
   QColor col;
   col=QColorDialog::getColor();

   buttonsandarea *current;
   current=new buttonsandarea;

   current->newtest=(testdraw *)tabwidget->currentWidget();

   current->newtest->getpencolor(col);
}

void ImageViewer::PenWidthSetter()
{
    bool ok;

    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    int newWidth = QInputDialog::getInteger(current->newtest, tr("PenWidth Selector"),
                                            tr("Select pen width:"),
                                            current->newtest->currentpenwidth(),
                                            1, 50, 1, &ok);
    if(ok)
    {
        current->newtest->getpenwidth(newWidth);
    }
}

void ImageViewer::linedrawdecider()
{

    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->linedrawset(true);
    LineDrawAct->setEnabled(false);
    FreeHandAct->setEnabled(true);
}

void ImageViewer::freehanddecider()
{

    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->linedrawset(false);
    LineDrawAct->setEnabled(true);
    FreeHandAct->setEnabled(false);
}

void ImageViewer::clearimagecaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->clearimage();
}

/*
void ImageViewer::print()
{
    Q_ASSERT(workarea[count]->imageLabel->pixmap());
#ifndef QT_NO_PRINTER
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = workarea[count]->imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(workarea[count]->imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *workarea[count]->imageLabel->pixmap());
    }
#endif
}
*/

void ImageViewer::zoomIncaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->zoomerin();
}

void ImageViewer::zoomOutcaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();
    current->newtest->zoomerout();
}

void ImageViewer::normalcaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();
    current->newtest->normal();

}

void ImageViewer::cropcaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->cropswitcherreceiver(true);
}

/*
void ImageViewer::rotatecaller()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();

    current->newtest->rotator();
}
*/
/*
void ImageViewer::zoomIn()
{
   // buttonsandarea *current;
   // current=new buttonsandarea;

   // current->newtest=(testdraw *)tabwidget->currentWidget();


    //scaleImage(current->newtest,1.25);
}

void ImageViewer::zoomOut()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();


    scaleImage(current->newtest,0.8);
}

void ImageViewer::normalSize()
{
    buttonsandarea *current;
    current=new buttonsandarea;

    current->newtest=(testdraw *)tabwidget->currentWidget();
    //work->imageLabel->adjustSize();
    //scaleFactor = 1.0;
}
*/

/*void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    workarea[count]->scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
       // normalSize();
    }
    updateActions();
}
*/

void ImageViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>Image Viewer UAS PROJECT Copyright October, 2012</p>"));
}

void ImageViewer::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    /*
    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));
*/
    ColorPanelAct=new QAction(tr("&ColorPanel"),this);
    connect(ColorPanelAct,SIGNAL(triggered()),this,SLOT(ColorPanel()));
    PenWidthAct=new QAction(tr("&Pen Width"),this);
    connect(PenWidthAct,SIGNAL(triggered()),this,SLOT(PenWidthSetter()));
    LineDrawAct=new QAction(tr("Draw Line"),this);
    connect(LineDrawAct,SIGNAL(triggered()),this,SLOT(linedrawdecider()));
    FreeHandAct=new QAction(tr("Free Hand"),this);
    connect(FreeHandAct,SIGNAL(triggered()),this,SLOT(freehanddecider()));
    FreeHandAct->setEnabled(false);
    ClearImageAct=new QAction(tr("Clear Screen"),this);
    connect(ClearImageAct,SIGNAL(triggered()),this,SLOT(clearimagecaller()));

    ZoomInAct=new QAction(tr("Zoom In"),this);
    connect(ZoomInAct,SIGNAL(triggered()),this,SLOT(zoomIncaller()));
    ZoomOutAct=new QAction(tr("Zoom Out"),this);
    connect(ZoomOutAct,SIGNAL(triggered()),this,SLOT(zoomOutcaller()));
    NormalAct=new QAction(tr("Normal"),this);
    connect(NormalAct,SIGNAL(triggered()),this,SLOT(normalcaller()));

    CropAct=new QAction(tr("Crop"),this);
    connect(CropAct,SIGNAL(triggered()),this,SLOT(cropcaller()));

    /*
    Rotate_90Act=new QAction(tr("Rotate 90 degrees"),this);
    connect(Rotate_90Act,SIGNAL(triggered()),this,SLOT(rotatecaller()));
    */
    /*
    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));
*/
    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageViewer::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    //fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
/*
    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);
*/
    PaintFunctionsMenu=new QMenu(tr("Paint Functions"),this);
    PaintFunctionsMenu->addAction(ColorPanelAct);
    PaintFunctionsMenu->addAction(PenWidthAct);
    PaintFunctionsMenu->addAction(LineDrawAct);
    PaintFunctionsMenu->addAction(FreeHandAct);
    PaintFunctionsMenu->addAction(ClearImageAct);

    ZoomFunctionsMenu=new QMenu(tr("Zoom Functions"),this);
    ZoomFunctionsMenu->addAction(ZoomInAct);
    ZoomFunctionsMenu->addAction(ZoomOutAct);
    ZoomFunctionsMenu->addAction(NormalAct);
    ZoomFunctionsMenu->setEnabled(false);

    PhotoshopFunctionsMenu=new QMenu(tr("Photoshop Functions"),this);
    PhotoshopFunctionsMenu->addAction(CropAct);
    //PhotoshopFunctionsMenu->addAction(Rotate_90Act);


    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(PaintFunctionsMenu);
    menuBar()->addMenu(ZoomFunctionsMenu);
    menuBar()->addMenu(PhotoshopFunctionsMenu);
    //menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);

}

/*
void ImageViewer::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
}
*/
/*
void ImageViewer::scaleImage(testdraw *newdraw, double factor)
{
    //Q_ASSERT(work->imageLabel->pixmap());


    scaleFactor *= factor;
   QSize newsize;
   newsize=newdraw->returnimage().size();//->resize(scaleFactor * work->imageLabel->pixmap()->size());

   newsize=newsize*2;

   QImage imaging;

   imaging=newdraw->returnimage();

   imaging.scaled(newsize,Qt::IgnoreAspectRatio,Qt::FastTransformation);

   newdraw->getimage(imaging);

}

//void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
//{
//    scrollBar->setValue(int(factor * scrollBar->value()
//                            + ((factor - 1) * scrollBar->singleStep()/2)));
//}


*/

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainter>

#include "stdafx.h"
#include "AA+.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Draw reference frame
//    painter.drawLine( width(), height() / 2 , 0, height() / 2 );
    painter.drawLine( width() / 2, 0 , width() / 2, height() );

    unsigned int year = 2021;
    unsigned int month = 9;
    CAADate begin_date(year, month, 1, 0, 0, 0, true);
//    CAADate end_date(year, month, 31, 23, 59, 59, true);

    CAAGalileanMoonsDetails GalileanDetails;
    const int maxX = 27; // Callisto is max 27 jupiter radii away
    const int maxY = 31; // max # days per month
    int scaleX = width() / (2*maxX);
    int scaleY = height() / maxY;
    int offsetX = width() / 2; // r=0, or jupiter, is middle of screen

    // draw horizontal lines every day at 0h UT
    for ( int y = 0; y < 32; y++  ) {  // res = 1d
        painter.drawLine( 0, y * scaleY, width(), y * scaleY);
        painter.drawText(width() - 20, y * scaleY, QString::number(y));
    }

    GalileanDetails = CAAGalileanMoons::Calculate(begin_date, true);
    QPointF prevsat1(GalileanDetails.Satellite1.ApparentRectangularCoordinates.X * scaleX + offsetX, 0); // maybe also add offsetY here not to start from the edge?
    QPointF prevsat2(GalileanDetails.Satellite2.ApparentRectangularCoordinates.X * scaleX + offsetX, 0);
    QPointF prevsat3(GalileanDetails.Satellite3.ApparentRectangularCoordinates.X * scaleX + offsetX, 0);
    QPointF prevsat4(GalileanDetails.Satellite4.ApparentRectangularCoordinates.X * scaleX + offsetX, 0);

    // iterate over the 31 days of one month
    for ( double t = begin_date; t< (begin_date+32); t+=(1.0/(12)) ) {  // res = 2h
        GalileanDetails = CAAGalileanMoons::Calculate(t, true);

        QPointF nextsat1(GalileanDetails.Satellite1.ApparentRectangularCoordinates.X * scaleX + offsetX, (t - begin_date) * scaleY);
        painter.setPen(QPen(Qt::black,1,Qt::DashLine));
        painter.drawLine( prevsat1 , nextsat1 );

        QPointF nextsat2(GalileanDetails.Satellite2.ApparentRectangularCoordinates.X * scaleX + offsetX, (t - begin_date) * scaleY);
        painter.setPen(QPen(Qt::black,1,Qt::DotLine));
        painter.drawLine( prevsat2 , nextsat2 );

        QPointF nextsat3(GalileanDetails.Satellite3.ApparentRectangularCoordinates.X * scaleX + offsetX, (t - begin_date) * scaleY);
        painter.setPen(QPen(Qt::black,1,Qt::DashDotLine));
        painter.drawLine( prevsat3 , nextsat3 );

        QPointF nextsat4(GalileanDetails.Satellite4.ApparentRectangularCoordinates.X * scaleX + offsetX, (t - begin_date) * scaleY);
        painter.setPen(QPen(Qt::black,1,Qt::DashDotDotLine));
        painter.drawLine( prevsat4 , nextsat4 );

        prevsat1 = nextsat1;
        prevsat2 = nextsat2;
        prevsat3 = nextsat3;
        prevsat4 = nextsat4;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


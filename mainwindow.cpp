#include "mainwindow.h"
#include <QtWidgets>
#include <QPixmap>
#include <QPainter>
#include <time.h>
#include <math.h>

int maxX=800, maxY=800;

float PL(float f, float d)
{
    return 28 + 22 * log10(d) + 20*log10(f);
}

float delay(int N, float f)
{
    if (N == 3)
    {
        return 23+0.3*f;
    }
    if (N == 2)
    {
        return 2+0.2*f;
    }
    if (N == 1)
    {
        return 4.85+0.12*f;
    }
    if (N == 0)
    {
        return 5+4*f;
    }

    else
    {
        return 0;
    }
}

int DrawPixel(QPainter* Pix, int x, int y)
{
    Pix->drawPoint(x + 1, y + 1);
    Pix->drawPoint(x + 1, y - 1);
    Pix->drawPoint(x - 1, y + 1);
    Pix->drawPoint(x - 1, y - 1);
    Pix->drawPoint(x, y);
    Pix->drawPoint(x, y - 1);
    Pix->drawPoint(x, y + 1);
    Pix->drawPoint(x - 1, y);
    Pix->drawPoint(x + 1, y);
    return 0;
}


void Pen_Color (QPainter* p,float sigPower)
{
    if(sigPower >= -54)
    {
        p->setPen(QColor(255, 0, 0, 255)); // <-- задание цвета красный
    }
    if (sigPower < -54 && sigPower >= -59)
    {
        p->setPen(QColor(246, 70, 0, 255)); //
    }
    if (sigPower < -59 && sigPower >= -64)
    {
        p->setPen(QColor(228, 110, 0, 255)); // красноорнжевый
    }
    if (sigPower < -64 && sigPower >= -69)
    {
        p->setPen(QColor(228, 140, 0, 255)); //
    }
    if (sigPower < -69 && sigPower >= -74)
    {
        p->setPen(QColor(255, 175, 0, 255)); //оранжевый
    }
    if (sigPower < -74 && sigPower >= -79)
    {
        p->setPen(QColor(255, 200, 0, 255)); //
    }
    if (sigPower < -79 && sigPower >= -84)
    {
        p->setPen(QColor(255, 255, 0, 255)); //желтый
    }
    if (sigPower < -84 && sigPower >= -89)
    {
        p->setPen(QColor(230, 255, 0, 255)); //
    }
    if (sigPower < -89 && sigPower >= -94)
    {
        p->setPen(QColor(216, 255, 0, 255)); //лаймовый
    }
    if (sigPower < -94 && sigPower >= -99)
    {
        p->setPen(QColor(150, 255, 0, 255)); //
    }
    if (sigPower < -99 && sigPower >= -104)
    {
        p->setPen(QColor(36, 255, 0, 255)); //зелёный
    }
    if (sigPower < -104 && sigPower >= -109)
    {
        p->setPen(QColor(0, 255, 70, 255)); //
    }
    if (sigPower < -109 && sigPower >= -114)
    {
        p->setPen(QColor(0, 255, 143, 255)); //зелёноголубой
    }
    if (sigPower < -114 && sigPower >= -119)
    {
        p->setPen(QColor(0, 255, 180, 255)); //
    }
    if (sigPower < -119 && sigPower >= -124)
    {
        p->setPen(QColor(0, 255, 255, 255)); //голубой
    }
    if (sigPower < -124 && sigPower >= -129)
    {
        p->setPen(QColor(0, 180, 255, 255)); //
    }
    if (sigPower < -129 && sigPower >= -134)
    {
        p->setPen(QColor(0, 130, 255, 255)); //синий
    }
    if (sigPower < -134)
    {
        p->setPen(QColor(40, 0, 255, 255)); //глубокий синий
    }
}


void Fill_Field(QPainter* p, QPixmap* map, QImage* image, int cellPosX, int cellPosY, int onePixDistance, int TxPower, int antGain, float freq) {
    float fi3db = 65.0f;
    float Amax = 30.0f;
    float SLA = 30.0f;
    for(int i = 0; i < maxX; i++) {
        for(int j = 0; j < maxY; j++) {
            float distance = sqrt(pow(abs(cellPosX - i), 2) + pow(abs(cellPosY - j), 2)) * onePixDistance;
            float sigPower = TxPower + antGain - PL(freq, distance);
            float angle = atan2(j - cellPosY, i - cellPosX) * (180.0 / M_PI);

            float antennaAngle = antennaAngle = angle;

            if (antennaAngle <= 180) {
                float fiRatio = antennaAngle / fi3db;
                float attenuation = 12.0 * pow(fiRatio, 2);
                float signalStrength = -1.0f * std::min(attenuation, Amax);

                float fiRatio2 = (antennaAngle - 90.0)/ fi3db;
                float attenuation2 = 12.0 * pow(fiRatio2, 2);
                float signalStrength2 = -1.0f * std::min(attenuation2, SLA);


                signalStrength = -std::min(-1.0f * (signalStrength2 + signalStrength), Amax);

                if (antennaAngle > 180.0 && antennaAngle < -180.0) {
                    signalStrength = 0.0;
                 }
                if (antennaAngle > 180.0 && antennaAngle < 0.0) {
                    signalStrength2 = 0.0;
                 }
                sigPower += signalStrength;
                if (sigPower < -110) {
                   p->setPen(QColor(14,41,75));
                } else {
                    Pen_Color(p, sigPower);
                }


            } else {
                p->setPen(QColor(0, 0, 0, 255));
            }
QRgb color = image->pixel(i, j);
int red = qRed(color);
int green = qGreen(color);
int blue = qBlue(color);

if (red == 34 && green == 34 && blue == 34) {
p->setPen(QColor(34, 34, 34, 255));
    }

    p->drawPoint(i, j);
       }
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    QGraphicsScene* scene = new QGraphicsScene();
    int onePixDistance = 100; //m
    int TxPower = 23;
    int antGain = 12;
    float freq=2.5;
    srand(time(NULL));
    int cellPosX =maxX/2;
    int cellPosY=maxY/2;
    QPixmap map(maxX, maxY);
    QPainter p(&map);


    QImage image = map.toImage();
    Fill_Field(&p, &map,&image, cellPosX, cellPosY, onePixDistance, TxPower, antGain, freq);

    p.setPen(QColor(255, 255, 255, 255));
    p.drawPoint(cellPosX, cellPosY);

    p.end();
    scene->addPixmap(map);
    QGraphicsView* view = new QGraphicsView(scene);
    setCentralWidget(view);
}

MainWindow::~MainWindow()
{
}

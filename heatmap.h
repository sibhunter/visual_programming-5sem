#ifndef HEATMAP_H
#define HEATMAP_H

#include <QColor>
#include <QPixmap>
#include <QPainter>

class Heatmap {
public:
    Heatmap(int maxX, int maxY);
    ~Heatmap();

    QPixmap generateHeatmap(int **map_obj, int cellPosX, int cellPosY, int maxX, int maxY,
                            int TxPower, int antGain, float freq, double onePixDistance);

private:
    double formula(double f, double d);
    float calculate(int x1, int x2, int y1, int y2);
    float pix_translate(float x, int pix_distance);
    int drawBresenhamLine(QPainter *p, int **map_obj, int x1, int y1, int x2, int y2);
};

#endif // HEATMAP_H

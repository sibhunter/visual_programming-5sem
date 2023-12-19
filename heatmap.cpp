#include "heatmap.h"
#include <cmath>


QPixmap Heatmap::generateHeatmap(int **map_obj, int cellPosX, int cellPosY, int maxX, int maxY,
                                 int TxPower, int antGain, float freq, double onePixDistance) {
    QPixmap heatmap(maxX, maxY);
    QPainter p(&heatmap);

    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            float distance = calculate(cellPosX, i, cellPosY, j);
            distance = pix_translate(distance, onePixDistance);
            float Signal_Power = TxPower + antGain - formula(freq, distance);

            int df = drawBresenhamLine(&p, map_obj, cellPosX, cellPosY, i, j);
            Signal_Power -= df;

            if (Signal_Power < -44 && Signal_Power >= -54) {
                p.setPen(QColor(255, 0, 0, 255));
            } else if (Signal_Power < -54 && Signal_Power >= -64) {
                p.setPen(QColor(220, 50, 0, 255));
            } else if (Signal_Power < -64 && Signal_Power >= -74) {
                p.setPen(QColor(255, 165, 0, 255));
            } else if (Signal_Power < -74 && Signal_Power >= -84) {
                p.setPen(QColor(255, 255, 0, 255));
            } else if (Signal_Power < -84 && Signal_Power >= -94) {
                p.setPen(QColor(173, 255, 47, 255));
            } else if (Signal_Power < -94 && Signal_Power >= -104) {
                p.setPen(QColor(0, 255, 0, 255));
            } else if (Signal_Power < -104 && Signal_Power >= -114) {
                p.setPen(QColor(0, 250, 154, 255));
            } else if (Signal_Power < -114 && Signal_Power >= -124) {
                p.setPen(QColor(102, 205, 170, 255));
            } else if (Signal_Power < -124 && Signal_Power >= -134) {
                p.setPen(QColor(65, 105, 225, 255));
            } else if (Signal_Power < -134 && Signal_Power >= -144) {
                p.setPen(QColor(0, 0, 255, 255));
            }

            p.drawPoint(i, j);
        }
    }

    p.end();
    return heatmap;
}



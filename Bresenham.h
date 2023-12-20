#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <QPainter>

class Bresenham {
public:
    static double drawBresenhamLine(QPainter *p, int **map_obj, int x1, int y1, int x2, int y2);
};

#endif // BRESENHAM_H

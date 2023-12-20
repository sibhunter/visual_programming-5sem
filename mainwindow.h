#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int maxX;
    int maxY;
    void add_material_to_map(int **map, int px, int py, int sx, int sy, int type);
    double formula(double f, double d);
    float calculate(int x1, int x2, int y1, int y2);
    float pix_translate(float x, int pix_distance);
    double drawBresenhamLine(QPainter *p, int **map_obj, int x1, int y1, int x2, int y2);

    QGroupBox* gradientGroupBox_;
    QLabel* label_;
    int** map_obj;
};

#endif // MAINWINDOW_H

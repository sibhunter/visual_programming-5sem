#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGroupBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>

enum class type_material {
    NO_MATERIAL,
    GLASS,
    IRR_GLASS,
    CONCRETE,
    WOOD,
    COUNT_MATERIAL
};

struct Material {
    QColor color;   // Цвет материала
    double absorption;  // Сила поглощения
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QGraphicsScene* scene;
    int maxX;
    int maxY;
    double onePixDistance; //[m]
    int TxPower; // [dBm]
    int antGain; // [dBi]
    float freq; // [GHz]
    int cellPosX;
    int cellPosY;
    QPixmap map;
    QPainter p;

    Material materials[(int)type_material::COUNT_MATERIAL];
    QColor color_material[(int)type_material::COUNT_MATERIAL];

    double formula(double f, double d);
    float calculate(int x1, int x2, int y1, int y2);
    float pix_translate(float x, int pix_distance);
    double drawBresenhamLine(QPainter *p, int **map_obj, int x1, int y1, int x2, int y2);
    void add_material_to_map(int **map, int px, int py, int sx, int sy, int type);
};

#endif // MAINWINDOW_H

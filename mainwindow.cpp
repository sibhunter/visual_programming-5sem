#include "mainwindow.h"
#include "heatmap.h"
#include "Bresenham.h"
#include "material.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene();
    map_obj = new int *[maxY];
    for (int i = 0; i < maxY; ++i) {
        map_obj[i] = new int[maxX]{};
    }
    add_material_to_map(map_obj, 500, 350, 20, 30, (int)type_material::GLASS);
    add_material_to_map(map_obj, 500, 700, 30, 40, (int)type_material::CONCRETE);
    add_material_to_map(map_obj, 700, 500, 50, 80, (int)type_material::WOOD);

    Heatmap heatmap(maxX, maxY);
    QPixmap heatmapPixmap = heatmap.generateHeatmap(map_obj, cellPosX, cellPosY, maxX, maxY, TxPower, antGain, freq, onePixDistance);

    scene->addPixmap(heatmapPixmap);

    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);
    view->setGeometry(300, 0, maxX, maxY);
    this->layout()->addWidget(view);

    gradientGroupBox_ = new QGroupBox(QStringLiteral("Signal Strength"));
    int height = 400;
    int width = 150;
    int border = 10;
    QLinearGradient gr(0, 0, 1, height - 2 * border);
    gr.setColorAt(1.0f, Qt::blue);
    gr.setColorAt(0.8f, Qt::cyan);
    gr.setColorAt(0.6f, Qt::green);
    gr.setColorAt(0.4f, Qt::yellow);
    gr.setColorAt(0.0f, Qt::red);

    QPixmap pm(width, height);
    pm.fill(Qt::transparent);
    QPainter pmp(&pm);
    pmp.setBrush(QBrush(gr));
    pmp.setPen(Qt::NoPen);
    pmp.drawRect(border, border, 35, height - 2 * border);
    pmp.setPen(Qt::black);
    int step = (height - 2 * border) / 10;
    for (int i = 0; i < 11; i++) {
        int yPos = i * step + border;
        pmp.drawLine(border, yPos, 55, yPos);
        pmp.drawText(60, yPos + 2, QString("%1 [dBm]").arg(-44 - (i * 10)));
    }

    label_ = new QLabel();
    label_->setPixmap(pm);

    QVBoxLayout *colorMapVBox = new QVBoxLayout;
    colorMapVBox->addWidget(label_);
    gradientGroupBox_->setLayout(colorMapVBox);
    gradientGroupBox_->setGeometry(50, 100, 200, 700);
    this->layout()->addWidget(gradientGroupBox_);
}

MainWindow::~MainWindow() {
    for (int i = 0; i < maxY; ++i) {
        delete[] map_obj[i];
    }
    delete[] map_obj;
}

#include "mainwindow.h"
#include <QtWidgets>

double MainWindow::formula(double f, double d) {
    return 28 + 22 * log10(f) + 20 * log10(d);
}

float MainWindow::calculate(int x1, int x2, int y1, int y2) {
    return sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
}

float MainWindow::pix_translate(float x, int pix_distance) {
    return x * pix_distance;
}

double MainWindow::drawBresenhamLine(QPainter *p, int **map_obj, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    double f = 0;

    while (true) {
        if (x1 == x2 && y1 == y2) {
            break;
        }

        int err2 = 2 * err;

        if (err2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (err2 < dx) {
            err += dx;
            y1 += sy;
        }
        switch (map_obj[y1][x1]) {
            case (int)type_material::NO_MATERIAL:
                break;
            default:
                f += materials[map_obj[y1][x1] - 1].absorption;
                p->setPen(materials[map_obj[y1][x1] - 1].color);
                p->drawPoint(x1, y1);
                break;
        }
    }

    return f;
}

void MainWindow::add_material_to_map(int **map, int px, int py, int sx, int sy, int type) {
    for (int y = py; y < py + sy; ++y) {
        for (int x = px; x < px + sx; ++x) {
            map[y][x] = type;
        }
    }
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene();
    map_obj = new int *[maxY];
    for (int i = 0; i < maxY; ++i) {
        map_obj[i] = new int[maxX]{};
    }
    add_material_to_map(map_obj, 500, 350, 20, 30, (int)type_material::GLASS);
    add_material_to_map(map_obj, 500, 700, 30, 40, (int)type_material::CONCRETE);
    add_material_to_map(map_obj, 700, 500, 50, 80, (int)type_material::WOOD);
    for (int i = 0; i < maxY; i++) {
        for (int j = 0; j < maxX; j++) {
            float distance = 0;
            distance = calculate(cellPosX, i, cellPosY, j);
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
    scene->addPixmap(map);
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

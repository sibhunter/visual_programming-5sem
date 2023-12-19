#ifndef MATERIAL_H
#define MATERIAL_H

#include <QColor>

enum class type_material {
    NO_MATERIAL,
    GLASS,
    IRR_GLASS,
    CONCRETE,
    WOOD,
    COUNT_MATERIAL
};

struct Material {
    QColor color;       // Material color
    double absorption;  // Absorption strength
};

#endif // MATERIAL_H

#ifndef AXISALIGNEDBOUNDINGBOX_H
#define AXISALIGNEDBOUNDINGBOX_H
#include <vector>
#include <QPointF>
#include <QRectF>

using namespace std;
using PointList = vector<QPointF>;

class AxisAlignedBoundingBox{
public:
    AxisAlignedBoundingBox(PointList list);
    bool intersects(const AxisAlignedBoundingBox& other) const;
    QRectF intersected(const AxisAlignedBoundingBox& other) const;

    QRectF rectangle;

    ~AxisAlignedBoundingBox() = default;
};

#endif // AXISALIGNEDBOUNDINGBOX_H

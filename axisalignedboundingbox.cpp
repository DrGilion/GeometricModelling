#include "axisalignedboundingbox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(PointList list){
    QPointF upperLeft = list[0];
    QPointF bottomRight;
    for(auto&& point : list){
        //find new upper left point
        if(point.x() < upperLeft.x()){
            upperLeft.rx() = point.x();
        }
        if(point.y() < upperLeft.y()){
            upperLeft.ry() = point.y();
        }

        //find new bottom right point
        if(point.x() > bottomRight.x()){
            bottomRight.rx() = point.x();
        }
        if(point.y() > bottomRight.y()){
            bottomRight.ry() = point.y();
        }
    }
    rectangle = QRectF(upperLeft,bottomRight);
}


bool AxisAlignedBoundingBox::intersects(const AxisAlignedBoundingBox &other) const{
    return rectangle.intersects(other.rectangle);
}

QRectF AxisAlignedBoundingBox::intersected(const AxisAlignedBoundingBox &other) const{
    return rectangle.intersected(other.rectangle);
}

#include "axisalignedboundingbox.h"

AxisAlignedBoundingBox::AxisAlignedBoundingBox(PointList list){
    QPointF upperLeft;
    QPointF bottomRight;
    for(auto&& point : list){
        //find new lower left point
        if(point.x() < upperLeft.x() && point.y() < upperLeft.y()){
            upperLeft = point;
        }
        //find new upper right point
        if(point.x() > bottomRight.x() && point.y() > bottomRight.y()){
            bottomRight = point;
        }
    }
    rectangle = QRectF(upperLeft,bottomRight);
}


bool AxisAlignedBoundingBox::intersects(const AxisAlignedBoundingBox &other) const{
    return rectangle.intersects(other.rectangle);
}

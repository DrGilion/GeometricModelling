#pragma once

#include <QPointF>

namespace gmutil{

    inline int clamp(int num,int min,int max){
        return std::max(min, std::min(num, max));
    }

    inline QPointF lerpPoints(const QPointF& p1,const QPointF& p2, qreal ratio = 0.5){
        return  p1 + ((p2 - p1) * ratio);
    }
}

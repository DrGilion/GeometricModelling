#ifndef BEZIER_H
#define BEZIER_H

#include <limits>
#include <QPointF>
#include <QLineF>
#include <QRectF>
#include <vector>
#include <utility>

#include "axisalignedboundingbox.h"

using namespace std;
using PointList = vector<QPointF>;
using PointList2D = vector<PointList>;

namespace bezier{

    static double EPSILON = 0.1;

    bool isFlat(const PointList& points){
        double maxFlatness = numeric_limits<double>::max();
        for(unsigned int i = 1; i< points.size()-1; ++i){
            double flatness = QLineF(points[i+1] - points[i],points[i] - points[i-1]).length();
            if(flatness < maxFlatness){
                maxFlatness = flatness;
            }
        }
        return maxFlatness < EPSILON;
    }

    QPointF lerpPoints(const QPointF& p1,const QPointF& p2, qreal ratio = 0.5){
        return  p1 + ((p2 - p1) * ratio);
    }

    pair<PointList,PointList> deCasteljau(PointList points){
        size_t pointSize = points.size();
        PointList2D curvepoints;
        curvepoints.push_back(points);

        for(unsigned int i = 0 ; i < pointSize-1; i++){
            curvepoints.push_back(PointList(pointSize));
        }

        for(unsigned int iter = 1; iter < pointSize; iter++){
            for(unsigned int pos = 0; pos < pointSize - iter; pos++){
                QPointF result = lerpPoints(curvepoints[iter-1][pos], curvepoints[iter-1][pos+1]);
                curvepoints[iter][pos] = result;
            }
        }

        PointList curve1;
        for(unsigned int iter = 0; iter < pointSize; iter++){
            curve1.push_back(curvepoints[iter][0]);
        }

        PointList curve2;
        for(unsigned int iter = 0; iter < pointSize; iter++){
           curve2.push_back(curvepoints[curvepoints[0].size()-1-iter][iter]);
        }

        return make_pair(curve1,curve2);
    }

    void calculateBezier(PointList curve,PointList2D& resultList){

        if(isFlat(curve)){
            resultList.push_back(curve);
        }else{
            pair<PointList,PointList> points = deCasteljau(curve);
            calculateBezier(points.first,resultList);
            calculateBezier(points.second,resultList);
        }
    }

    void intersect(PointList list1, PointList list2,vector<QRectF>& intersections){
        AxisAlignedBoundingBox box1(list1);
        AxisAlignedBoundingBox box2(list2);

        if(box1.intersects(box2)){
            if(!isFlat(list1)){
                //compute composite bezier polygon for first PointList
                pair<PointList,PointList> points = deCasteljau(list1);
                intersect(points.first,list2,intersections);
                intersect(points.second,list2,intersections);
            }else{
                if(!isFlat(list2)){
                    //compute composite bezier polygon for second PointList
                    pair<PointList,PointList> points = deCasteljau(list2);
                    intersect(list1,points.first,intersections);
                    intersect(list1,points.second,intersections);
                }else{
                    //intersect points
                    intersections.push_back(box1.intersected(box2));
                }
            }
        }
    }
}

#endif // BEZIER_H

#ifndef LINE_H
#define LINE_H

#include "point.h"

class Line{
public:
    Line(Point& start,Point& end);

private:
    Point startPoint;
    Point endPoint;
};

#endif // LINE_H

#ifndef CUSTOMPOINT_H
#define CUSTOMPOINT_H

#include <QPoint>

int square(int num);

class CustomPoint : public QPoint
{
public:
    CustomPoint();
    CustomPoint(int xpos, int ypos);

    friend inline bool operator<(const QPoint p1, const QPoint p2)
    {
        if (p1.x() < p2.x())
        {
            return true;
        }
        else if ((p1.x() == p2.x()) && (p1.y() < p2.y()))
        {
            return true;
        }
        return false;
//        return ((square(p1.x()) + square(p1.y())) < (square(p2.x()) + square(p2.y())));
    }
};



#endif // CUSTOMPOINT_H

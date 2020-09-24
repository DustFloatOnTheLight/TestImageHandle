#include "CustomPoint.h"

CustomPoint::CustomPoint():
    QPoint ()
{

}

CustomPoint::CustomPoint(int xpos, int ypos):
    QPoint (xpos, ypos)
{

}

int square(int num)
{
    return num * num;
}

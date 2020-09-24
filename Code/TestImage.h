#ifndef TESTIMAGE_H
#define TESTIMAGE_H

#include <QColor>

#include "CustomPoint.h"

class TestImage
{
public:
    TestImage();

    void start();

private:
    void execute();

    void fillBlurMetrix(QVector<CustomPoint> &metrix, CustomPoint curPoint);
    QColor resultPixel(QVector<CustomPoint> &metrix, QMap<CustomPoint, QColor> &originImageMap);

    int m_nOriginWidth;
    int m_nOriginHeight;

    int m_nResultWidth;
    int m_nResultHeight;
};

#endif // TESTIMAGE_H

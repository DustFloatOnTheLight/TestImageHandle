#include "TestImage.h"
#include "TestImageConsts.h"

#include <QImage>
#include <QMessageBox>

#include <QDebug>

DEFINE_CONSISTER(c_sOriginPicturePath, "G:\\ImageTest\\test.jpg")
DEFINE_CONSISTER(c_sResultPicturePath, "G:\\ImageTest\\result.jpg")

DEFINE_CONSISTER(c_sProcess, "%1%2%")

DEFINE_CONSISTINT(c_nBlurMetrixSideLength, 3)

TestImage::TestImage()
{

}

void TestImage::start()
{
    execute();
}

void TestImage::execute()
{
#ifdef QT_DEBUG
    QMessageBox::about(nullptr, "Debug", "Please Debug!");
#endif

    QImage oOriginImage(c_sOriginPicturePath);
    if (!(QImage::Format_RGB32 == oOriginImage.format()) && !(QImage::Format_ARGB32 == oOriginImage.format()))
    {
        QMessageBox::about(nullptr, "Warnning", "The image's format is not required");
        return;
    }

    m_nOriginWidth = oOriginImage.width();
    m_nOriginHeight = oOriginImage.height();
    qDebug() << m_nOriginWidth << m_nOriginHeight;

    QMap<CustomPoint, QColor> oOriginImageMap;
    for (int i = 0; i < m_nOriginWidth; i++)
    {
        for (int j = 0; j < m_nOriginHeight; j++)
        {
            oOriginImageMap.insert(CustomPoint(i, j), QColor(oOriginImage.pixel(i, j)));
        }
    }

    m_nResultWidth = m_nOriginWidth - c_nBlurMetrixSideLength + 1;
    m_nResultHeight = m_nOriginHeight - c_nBlurMetrixSideLength + 1;
    QMap<CustomPoint, QColor> oResultImageMap;
    QVector<CustomPoint> oBlurMetrix;

    qDebug() << "Calculate";
    int nCurIndex = 0;
    for (QMap<CustomPoint, QColor>::iterator oIter = oOriginImageMap.begin(); oIter != oOriginImageMap.end(); ++ oIter)
    {
        oBlurMetrix.clear();
        fillBlurMetrix(oBlurMetrix, oIter.key());

        if (oBlurMetrix.count() > 0)
        {
            oResultImageMap.insert(oIter.key(), resultPixel(oBlurMetrix, oOriginImageMap));
        }
        qDebug() << c_sProcess.arg("Calculating: ").arg(100 * (nCurIndex++) /  oOriginImageMap.count());
    }


    QImage oResultImage(m_nResultWidth, m_nResultHeight, QImage::Format_RGB32);

    qDebug() << "Generate Image";
    nCurIndex = 0;
    for (QMap<CustomPoint, QColor>::iterator oIter = oResultImageMap.begin(); oIter != oResultImageMap.end(); ++oIter)
    {
        CustomPoint oCurPoint = oIter.key();
        QColor oCurPixel = oIter.value();

        oResultImage.setPixelColor(oCurPoint, oCurPixel);
    }

    oResultImage.save(c_sResultPicturePath);

}

void TestImage::fillBlurMetrix(QVector<CustomPoint> &metrix, CustomPoint curPoint)
{
    if ((m_nResultWidth <= curPoint.x()) || (m_nResultHeight <= curPoint.y()))
    {
        return;
    }
    for (int i = curPoint.x(); i < (curPoint.x() + c_nBlurMetrixSideLength); i++)
    {
        for (int j = curPoint.y(); j < (curPoint.y() + c_nBlurMetrixSideLength); j++)
        {
            metrix.push_back(CustomPoint(i, j));
        }
    }
}

QColor TestImage::resultPixel(QVector<CustomPoint> &metrix, QMap<CustomPoint, QColor> &originImageMap)
{
    int nSumValue[3] = {0};
    for (int i = 0; i < metrix.count(); i++)
    {
        QMap<CustomPoint, QColor>::iterator oIter = originImageMap.find(metrix[i]);
        if (oIter == originImageMap.end())
        {
            continue;
        }
        nSumValue[0] += oIter.value().red();
        nSumValue[1] += oIter.value().green();
        nSumValue[2] += oIter.value().blue();
    }

    return QColor(nSumValue[0] / metrix.count(), nSumValue[1] / metrix.count(), nSumValue[2] / metrix.count());
}


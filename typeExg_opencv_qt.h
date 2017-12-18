#ifndef OPENCV_TO_QT_IMG_H
#define OPENCV_TO_QT_IMG_H

#include "opencv2/opencv.hpp"
#include <QImage>
#include <QPixmap>
#include <QVector>

inline QImage cvMatToQImage( const cv::Mat &inMat )
{
    switch ( inMat.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable;

        // only create our color table once

        QImage image( inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8 );
        return image;
    }

    default:
    {
       break;
    }

    }

    return QImage();
}

inline QPixmap cvMatToQPixmap( const cv::Mat &inMat )
{
    return QPixmap::fromImage( cvMatToQImage( inMat ) );
}

inline void imshow_qt(const cv::Mat &img, QLabel *label)
{
	// make sure the the displayed image is automatically resized to given label size.
	QPixmap p = cvMatToQPixmap(img);
	int w = label->width();
	int h = label->height();
	label->setPixmap(p.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	label->setMinimumSize(1, 1); // not sure why this is necessary. 
}

#endif //OPENCV_TO_QT_IMG_H
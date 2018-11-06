//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_IMAGEPROCESSER_H
# define OPENCV_SRV_IMAGEPROCESSER_H

#include <cv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>

#include "Frame.h"
#include "ImageAdditionner.h"
#include "output_static_object/Log.hh"

class ImageProcesser
{
public:
    ImageProcesser();
    ~ImageProcesser();

    cv::Mat                             differenceImg(cv::Mat firstImg, cv::Mat secondImg);
    cv::Mat                             threshImg(const cv::Mat &img);
    std::vector<std::vector<cv::Point>> findContoursFromImg(const cv::Mat &img);
    std::vector<std::vector<cv::Point>> findConvexHullsFromContours(const std::vector<std::vector<cv::Point>> &contours);
};


#endif //OPENCV_SRV_IMAGEPROCESSER_H

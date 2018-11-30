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
#include "output_static_object/Error.hh"

class ImageProcesser
{
public:
    ImageProcesser();
    ~ImageProcesser();

    void                                imgToHSV(cv::Mat &img);
    cv::Mat                             differenceImgGray(cv::Mat firstImg, cv::Mat secondImg);
    void                                threshImg(cv::Mat &img);
    std::vector<std::vector<cv::Point>> findContoursFromImg(const cv::Mat &img);
    std::vector<std::vector<cv::Point>> findConvexHullsFromContours(const std::vector<std::vector<cv::Point>> &contours);

private:
    cv::Mat                             differenceImg(cv::Mat firstImg, cv::Mat secondImg);
};


#endif //OPENCV_SRV_IMAGEPROCESSER_H

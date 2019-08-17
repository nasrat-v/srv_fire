//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_IMAGEPROCESSER_H
# define OPENCV_SRV_IMAGEPROCESSER_H

#include <opencv2/opencv.hpp> //cv
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>

#include "Frame.hh"
#include "ImageAdditionner.hh"
#include "../Log/Log.hh"
#include "../Log/Error.hh"

class ImageProcesser
{
public:
    ImageProcesser();
    ~ImageProcesser();

    typedef struct  s_colorRange
    {
        cv::Scalar  firstRange;
        cv::Scalar  secondRange;
    }               t_colorRange;

    void                                imgToHSV(cv::Mat &img, const t_colorRange &range);
    cv::Mat                             differenceImgGray(cv::Mat firstImg, cv::Mat secondImg);
    void                                threshImg(cv::Mat &img);
    std::vector<std::vector<cv::Point>> findContoursFromImg(const cv::Mat &img);
    std::vector<std::vector<cv::Point>> findConvexHullsFromContours(const std::vector<std::vector<cv::Point>> &contours);

private:
    cv::Mat                             differenceImg(cv::Mat firstImg, cv::Mat secondImg);
};


#endif //OPENCV_SRV_IMAGEPROCESSER_H

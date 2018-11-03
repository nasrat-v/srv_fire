//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAMESUBSTRACTION_H
#define OPENCV_SRV_FRAMESUBSTRACTION_H

#include <cv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/mat.hpp>

#include "../header/Frame.h"

class FrameSubstraction
{
public:
    FrameSubstraction();
    ~FrameSubstraction();

    void            substractInfos(Frame &frame);

private:
    /* Methods */
    void            threshImg(cv::Mat firstFrameCopy, cv::Mat secondFrameCopy);
    void            contoursImg(Frame &frame);
    void            convexHullsImg(Frame &frame);

    /* Attributes */
    cv::Mat         _imgThresh;
    cv::Mat         _imgDifference;
};


#endif //OPENCV_SRV_FRAMESUBSTRACTION_H

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAMEADDITION_H
#define OPENCV_SRV_FRAMEADDITION_H

# define SCALAR_BLACK   cv::Scalar(0.0, 0.0, 0.0)
# define SCALAR_WHITE   cv::Scalar(255.0, 255.0, 255.0)
# define SCALAR_YELLOW  cv::Scalar(0.0, 255.0, 255.0)
# define SCALAR_GREEN   cv::Scalar(0.0, 200.0, 0.0)
# define SCALAR_RED     cv::Scalar(0.0, 0.0, 255.0)

#include "Entity.h"

#include <cv.hpp>

class FrameAddition
{
public:
    FrameAddition();
    ~FrameAddition();

    void drawAndShowContours(cv::Size imageSize, std::vector<Entity> entities, std::string strImageName);
    void drawAndShowContours(cv::Size imageSize, std::vector<std::vector<cv::Point>> contours, std::string strImageName);
    void drawTrackEntitiesOnImage(std::vector<Entity> &entities, cv::Mat &imgFrame);
    void drawNumberEntitiesOnImage(std::vector<Entity> &entities, cv::Mat &imgFrame);
};


#endif //OPENCV_SRV_FRAMEADDITION_H

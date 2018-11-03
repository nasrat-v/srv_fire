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

class FrameAddition
{
public:
    FrameAddition();
    ~FrameAddition();

    void drawAndShowContours(cv::Size imageSize, std::vector<Entity> blobs, std::string strImageName);
};


#endif //OPENCV_SRV_FRAMEADDITION_H

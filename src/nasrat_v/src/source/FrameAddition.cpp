//
// Created by nasrat_v on 11/3/18.
//

#include <cv.hpp>
#include "../header/FrameAddition.h"

FrameAddition::FrameAddition()
{
}

FrameAddition::~FrameAddition()
{
}

void FrameAddition::drawAndShowContours(cv::Size imageSize, std::vector<Entity> blobs, std::string strImageName)
{
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto &blob : blobs)
    {
        if (blob.getStillBeingTracked())
            contours.push_back(blob.getContour());
    }
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    cv::imshow(strImageName, image);
}
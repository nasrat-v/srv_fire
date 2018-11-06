//
// Created by nasrat_v on 11/3/18.
//

#include "../header/ImageAdditionner.h"

ImageAdditionner::ImageAdditionner() = default;

ImageAdditionner::~ImageAdditionner() = default;

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<Entity> &entities, std::string strImageName)
{
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto &entity : entities)
    {
        if (entity.getStillBeingTracked())
            contours.push_back(entity.getContour());
    }
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    cv::imshow(strImageName, image);
}

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<std::vector<cv::Point>> &contours, std::string strImageName)
{
    cv::Mat image(imageSize, CV_8UC3, SCALAR_BLACK);

    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    cv::imshow(strImageName, image);
}


void ImageAdditionner::drawTrackEntitiesOnImage(const std::vector<Entity> &entities, cv::Mat &img)
{
    for (auto &entity : entities)
    {
        if (entity.getStillBeingTracked())
            cv::rectangle(img, entity.getCurrentBoundingRect(), SCALAR_RED, 2);
    }
}

void ImageAdditionner::drawNumberEntitiesOnImage(const std::vector<Entity> &entities, cv::Mat &img)
{
    int nb = 0;
    double fontScale;
    int intFontThickness;

    for (auto &entity : entities)
    {
        if (entity.getStillBeingTracked())
        {
            fontScale = (entity.getCurrentDiagonalSize() / 60.0);
            intFontThickness = (int)std::round(fontScale * 1.0);
            cv::putText(img, std::to_string(nb), entity.getCenterPositions().back(), CV_FONT_HERSHEY_SIMPLEX, fontScale, SCALAR_GREEN, intFontThickness);
        }
        nb++;
    }
}

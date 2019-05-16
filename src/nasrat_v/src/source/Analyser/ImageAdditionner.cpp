#include <utility>

//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/ImageAdditionner.hh"

ImageAdditionner::ImageAdditionner() = default;

ImageAdditionner::~ImageAdditionner() = default;

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<Entity> &entities,
                                            const std::string &strImageName)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto &entity : entities)
        contours.push_back(entity.getContour());
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    imshow(strImageName, image);
}

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<std::vector<cv::Point>> &contours,
                                            const std::string &strImageName, const Entity::entityTemperature &temp)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);

    if (temp == Entity::entityTemperature::WARM)
        cv::drawContours(image, contours, -1, SCALAR_YELLOW, -1);
    else if (temp == Entity::entityTemperature::HOT)
        cv::drawContours(image, contours, -1, SCALAR_ORANGE, -1);
    else
        cv::drawContours(image, contours, -1, SCALAR_RED, -1);
    imshow(strImageName, image);
}

void ImageAdditionner::drawTrackEntitiesOnImage(const std::vector<Entity> &savedEntities,
                                                const std::vector<Entity> &frameEntities, cv::Mat &img)
{
    for (auto &savedEntity : savedEntities)
    {
        for (auto &frameEntity : frameEntities)
        {
            if (savedEntity.isSame(frameEntity) && savedEntity.isStillBeingTracked())
            {
                if (savedEntity.getTemperatureType() == Entity::entityTemperature::WARM)
                    cv::rectangle(img, savedEntity.getBoundingRect(), SCALAR_YELLOW, 2);
                else if (savedEntity.getTemperatureType() == Entity::entityTemperature::HOT)
                    cv::rectangle(img, savedEntity.getBoundingRect(), SCALAR_ORANGE, 2);
                else
                    cv::rectangle(img, savedEntity.getBoundingRect(), SCALAR_RED, 2);
            }
        }
    }
}

void ImageAdditionner::drawNumberEntitiesOnImage(const std::vector<Entity> &entities, cv::Mat &img)
{
    double fontScale;
    int intFontThickness;

    for (auto &entity : entities)
    {
        fontScale = (entity.getDiagonalSize() / 60.0);
        intFontThickness = (int)std::round(fontScale * 1.0);
        if (entity.getTemperatureType() == Entity::entityTemperature::WARM)
            cv::putText(img, "warm", entity.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_WHITE, intFontThickness);
        else if (entity.getTemperatureType() == Entity::entityTemperature::HOT)
            cv::putText(img, "hot", entity.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_GREEN, intFontThickness);
        else
            cv::putText(img, "very_hot", entity.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_BLUE, intFontThickness);
    }
}

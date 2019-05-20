
//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/ImageAdditionner.hh"

ImageAdditionner::ImageAdditionner() = default;

ImageAdditionner::~ImageAdditionner() = default;

void ImageAdditionner::drawContours(cv::Mat &img, const std::vector<std::vector<cv::Point>> &contours)
{
    cv::drawContours(img, contours, -1, SCALAR_WHITE, -1);
}

void ImageAdditionner::drawAndShowContours(const cv::Size &imageSize, const std::vector<Blob> &blobs,
                                            const std::string &strImageName)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto &blob : blobs)
        contours.push_back(blob.getContour());
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    imshow(strImageName, image);
}

void ImageAdditionner::drawAndShowContours(const cv::Size &imageSize,
                                            const std::vector<std::vector<cv::Point>> &contours,
                                            const std::string &strImageName,
                                            const ScalarColor::t_colorRange &colorRange)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);

    cv::drawContours(image, contours, -1, colorRange._displayColor, -1);
    imshow(strImageName, image);
}

void ImageAdditionner::drawTrackBlobsOnImage(cv::Mat &img, const std::vector<Blob> &savedBlobs,
                                             const std::vector<Blob> &frameBlobs)
{
    for (auto &savedBlob : savedBlobs)
    {
        for (auto &frameBlob : frameBlobs)
        {
            if (savedBlob.isSame(frameBlob) && savedBlob.isStillBeingTracked())
                drawRectangleForBlobs(img, savedBlob);
        }
    }
}

void ImageAdditionner::drawTrackEntitiesOnImage(cv::Mat &img, const std::vector<Entity> &savedEntities,
                                                const std::vector<Entity> &frameEntities)
{
    for (auto &savedEntity : savedEntities)
    {
        for (auto &frameEntity : frameEntities)
        {
            if (savedEntity.isSame(frameEntity) && savedEntity.isStillBeingTracked())
                drawRectangleForBlobs(img, savedEntity);
        }
    }
}

void ImageAdditionner::drawNumberEntitiesOnImage(cv::Mat &img, const std::vector<Entity> &savedEntities,
                                                 const std::vector<Entity> &frameEntities)
{
    double fontScale;
    int intFontThickness;

    for (auto &savedEntity : savedEntities)
    {
        for (auto &frameEntity : frameEntities)
        {
            if (savedEntity.isSame(frameEntity) && savedEntity.isStillBeingTracked())
            {
                fontScale = (savedEntity.getDiagonalSize() / 60.0);
                intFontThickness = (int) std::round(fontScale * 1.0);
                cv::putText(img, std::to_string(savedEntity.getId()),
                            savedEntity.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                            fontScale, savedEntity.getColorRange()._displayColor, intFontThickness);
            }
        }
    }
}

void ImageAdditionner::drawRectangleForBlobs(cv::Mat &img, const Blob &blob)
{
    cv::rectangle(img, blob.getBoundingRect(), blob.getColorRange()._displayColor, 2);
}

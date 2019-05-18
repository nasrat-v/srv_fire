
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

void ImageAdditionner::drawTrackBlobsOnImage(const std::vector<Blob> &savedBlobs,
                                                const std::vector<Blob> &frameBlobs, cv::Mat &img)
{
    for (auto &savedBlob : savedBlobs)
    {
        for (auto &frameBlob : frameBlobs)
        {
            if (savedBlob.isSame(frameBlob) && savedBlob.isStillBeingTracked())
                cv::rectangle(img, savedBlob.getBoundingRect(), savedBlob.getColorRange()._displayColor, 2);
        }
    }
}

void ImageAdditionner::drawNumberBlobsOnImage(const std::vector<Blob> &blobs, cv::Mat &img)
{
    double fontScale;
    int intFontThickness;

    for (auto &blob : blobs)
    {
        fontScale = (blob.getDiagonalSize() / 60.0);
        intFontThickness = (int)std::round(fontScale * 1.0);
        cv::putText(img, "blob", blob.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                        fontScale, blob.getColorRange()._displayColor, intFontThickness);
    }
}

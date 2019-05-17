
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

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<Blob> &blobs,
                                            const std::string &strImageName)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point> > contours;

    for (auto &entity : blobs)
        contours.push_back(entity.getContour());
    cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
    imshow(strImageName, image);
}

void ImageAdditionner::drawAndShowContours(cv::Size imageSize, const std::vector<std::vector<cv::Point>> &contours,
                                            const std::string &strImageName, const Blob::blobTemperature &temp)
{
    cv::Mat image(std::move(imageSize), CV_8UC3, SCALAR_BLACK);

    if (temp == Blob::blobTemperature::WARM)
        cv::drawContours(image, contours, -1, SCALAR_YELLOW, -1);
    else if (temp == Blob::blobTemperature::HOT)
        cv::drawContours(image, contours, -1, SCALAR_ORANGE, -1);
    else if (temp == Blob::blobTemperature::VERY_HOT)
        cv::drawContours(image, contours, -1, SCALAR_RED, -1);
    else
        cv::drawContours(image, contours, -1, SCALAR_WHITE, -1);
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
            {
                if (savedBlob.getTemperatureType() == Blob::blobTemperature::WARM)
                    cv::rectangle(img, savedBlob.getBoundingRect(), SCALAR_YELLOW, 2);
                else if (savedBlob.getTemperatureType() == Blob::blobTemperature::HOT)
                    cv::rectangle(img, savedBlob.getBoundingRect(), SCALAR_ORANGE, 2);
                else if (savedBlob.getTemperatureType() == Blob::blobTemperature::VERY_HOT)
                    cv::rectangle(img, savedBlob.getBoundingRect(), SCALAR_RED, 2);
                else
                    cv::rectangle(img, savedBlob.getBoundingRect(), SCALAR_WHITE, 2);
            }
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
        if (blob.getTemperatureType() == Blob::blobTemperature::WARM)
            cv::putText(img, "warm", blob.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_BLACK, intFontThickness);
        else if (blob.getTemperatureType() == Blob::blobTemperature::HOT)
            cv::putText(img, "hot", blob.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_GREEN, intFontThickness);
        else if (blob.getTemperatureType() == Blob::blobTemperature::VERY_HOT)
            cv::putText(img, "very_hot", blob.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                    fontScale, SCALAR_BLUE, intFontThickness);
        else
            cv::putText(img, "blob", blob.getCenterPositions().back(), cv::FONT_HERSHEY_SIMPLEX,
                        fontScale, SCALAR_WHITE, intFontThickness);
    }
}

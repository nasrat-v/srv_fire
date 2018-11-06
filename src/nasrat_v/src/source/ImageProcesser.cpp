//
// Created by nasrat_v on 11/3/18.
//

#include "../header/ImageProcesser.h"

ImageProcesser::ImageProcesser() = default;

ImageProcesser::~ImageProcesser() = default;

cv::Mat ImageProcesser::differenceImg(cv::Mat firstImg, cv::Mat secondImg, const Entity::entityType &type)
{
    cv::Mat imgDifference;

    if (type == Entity::entityType::FIRE)
    {
        cv::cvtColor(firstImg, firstImg, CV_BGR2HSV);
        cv::inRange(firstImg, cv::Scalar(0, 180, 180), cv::Scalar(20, 255, 255), firstImg);
        cv::cvtColor(secondImg, secondImg, CV_BGR2HSV);
        cv::inRange(secondImg, cv::Scalar(0, 160, 160), cv::Scalar(30, 255, 255), secondImg);
    }
    else
    {
        cv::cvtColor(firstImg, firstImg, CV_BGR2GRAY);
        cv::cvtColor(secondImg, secondImg, CV_BGR2GRAY);
    }
    cv::GaussianBlur(firstImg, firstImg, cv::Size(5, 5), 0);
    cv::GaussianBlur(secondImg, secondImg, cv::Size(5, 5), 0);
    cv::absdiff(firstImg, secondImg, imgDifference);
    return (imgDifference);
}

cv::Mat ImageProcesser::threshImg(const cv::Mat &img)
{
    cv::Mat imgThresh;
    cv::Mat structuringElement1x1;
    cv::Mat structuringElement3x3;
    cv::Mat structuringElement5x5;
    cv::Mat structuringElement7x7;
    cv::Mat structuringElement9x9;

    cv::threshold(img, imgThresh, 30, 255.0, CV_THRESH_BINARY);
    structuringElement1x1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1));
    structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
    cv::erode(imgThresh, imgThresh, structuringElement1x1);
    cv::erode(imgThresh, imgThresh, structuringElement3x3);
    cv::dilate(imgThresh, imgThresh, structuringElement5x5);
    cv::dilate(imgThresh, imgThresh, structuringElement7x7);
    cv::dilate(imgThresh, imgThresh, structuringElement9x9);
    return (imgThresh);
}

std::vector<std::vector<cv::Point>> ImageProcesser::findContoursFromImg(const cv::Mat &img)
{
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(img, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    return (contours);
}

std::vector<std::vector<cv::Point>> ImageProcesser::findConvexHullsFromContours(const std::vector<std::vector<cv::Point>> &contours)
{
    size_t  i = 0;
    size_t  contoursSize = contours.size();
    std::vector<std::vector<cv::Point>> convexHulls(contoursSize);

    if (contoursSize == 0)
        Error::logError(Error::ErrorType::NO_CONTOUR, "Cannot find convexhulls");
    while (i < contoursSize)
    {
        cv::convexHull(contours[i], convexHulls[i]);
        i++;
    }
    return (convexHulls);
}

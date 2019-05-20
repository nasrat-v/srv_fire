//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/ImageProcesser.hh"

ImageProcesser::ImageProcesser() = default;

ImageProcesser::~ImageProcesser() = default;

void ImageProcesser::imgToHSV(cv::Mat &img, const ScalarColor::t_colorRange &range)
{
    cv::cvtColor(img, img, cv::COLOR_BGR2HSV);
    cv::inRange(img, range._firstRange, range._secondRange, img);
}

void ImageProcesser::imgToGray(cv::Mat &img)
{
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
}

cv::Mat ImageProcesser::differenceImgGray(cv::Mat firstImg, cv::Mat secondImg)
{
    imgToGray(firstImg);
    imgToGray(secondImg);
    return (differenceImg(firstImg, secondImg));
}

cv::Mat ImageProcesser::differenceImg(cv::Mat firstImg, cv::Mat secondImg)
{
    cv::Mat imgDifference;

    cv::GaussianBlur(firstImg, firstImg, cv::Size(5, 5), 0);
    cv::GaussianBlur(secondImg, secondImg, cv::Size(5, 5), 0);
    cv::absdiff(firstImg, secondImg, imgDifference);
    return (imgDifference);
}

void ImageProcesser::threshImg(cv::Mat &img)
{
    cv::Mat structuringElement1x1;
    cv::Mat structuringElement3x3;
    cv::Mat structuringElement5x5;
    cv::Mat structuringElement7x7;
    cv::Mat structuringElement9x9;

    cv::threshold(img, img, 30, 255.0, cv::THRESH_BINARY);
    structuringElement1x1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1));
    structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
    cv::erode(img, img, structuringElement1x1);
    /*cv::erode(img, img, structuringElement3x3);*/
    cv::dilate(img, img, structuringElement3x3);
    cv::dilate(img, img, structuringElement5x5);
    cv::dilate(img, img, structuringElement7x7);
    cv::dilate(img, img, structuringElement9x9);
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
    std::vector<cv::Point> point;

    /*if (contoursSize == 0)
        std::cout << "Cannot find convexhulls" << std::endl;*/
    while (i < contoursSize)
    {
        cv::convexHull(contours[i], convexHulls[i]);
        i++;
    }
    return (convexHulls);
}
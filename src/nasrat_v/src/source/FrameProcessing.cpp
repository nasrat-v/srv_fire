//
// Created by nasrat_v on 11/3/18.
//

#include "../header/FrameProcessing.h"

FrameProcessing::FrameProcessing()
{
}

FrameProcessing::~FrameProcessing()
{
}

void FrameProcessing::substractInfos(Frame &frame, Log::debugMode mode)
{
    _debugMode = mode;
    threshImg(frame.getFirstImg().clone(), frame.getSecondImg().clone());
    contoursImg(frame);
    convexHullsImg(frame);
}

const cv::Mat &FrameProcessing::getImgThresh() const
{
    return (_imgThresh);
}

void FrameProcessing::threshImg(cv::Mat firstImgCopy, cv::Mat secondImgCopy)
{
    cv::Mat structuringElement1x1;
    cv::Mat structuringElement3x3;
    cv::Mat structuringElement5x5;
    cv::Mat structuringElement7x7;
    cv::Mat structuringElement9x9;

    cv::cvtColor(firstImgCopy, firstImgCopy, CV_BGR2GRAY);
    cv::cvtColor(secondImgCopy, secondImgCopy, CV_BGR2GRAY);
    cv::GaussianBlur(firstImgCopy, firstImgCopy, cv::Size(5, 5), 0);
    cv::GaussianBlur(secondImgCopy, secondImgCopy, cv::Size(5, 5), 0);
    cv::absdiff(firstImgCopy, secondImgCopy, _imgDifference);
    cv::threshold(_imgDifference, _imgThresh, 30, 255.0, CV_THRESH_BINARY);
    if (_debugMode & Log::debugMode::THRESH)
        cv::imshow("imgThresh", _imgThresh);
    if (_debugMode & Log::debugMode::DIFFERENCE)
        cv::imshow("imgDifference", _imgDifference);
    structuringElement1x1 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, 1));
    structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
    cv::erode(_imgThresh, _imgThresh, structuringElement1x1);
    cv::erode(_imgThresh, _imgThresh, structuringElement3x3);
    cv::dilate(_imgThresh, _imgThresh, structuringElement5x5);
    cv::dilate(_imgThresh, _imgThresh, structuringElement7x7);
    cv::dilate(_imgThresh, _imgThresh, structuringElement9x9);
}

void FrameProcessing::contoursImg(Frame &frame)
{
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(_imgThresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    frame.setAllContours(contours);
    if (_debugMode & Log::debugMode::CONTOUR)
        _frameAdditionner.drawAndShowContours(_imgThresh.size(), contours, "imgContours");
}

void FrameProcessing::convexHullsImg(Frame &frame)
{
    size_t  i = 0;
    size_t  contoursSize = frame.getAllContours().size();
    std::vector<std::vector<cv::Point>> convexHulls(contoursSize);

    while (i < contoursSize)
    {
        cv::convexHull(frame.getAllContours()[i], convexHulls[i]);
        i++;
    }
    frame.setAllConvexHulls(convexHulls);
    if (_debugMode & Log::debugMode::CONVEXHULLS)
        _frameAdditionner.drawAndShowContours(_imgThresh.size(), convexHulls, "imgConvexHulls");
}

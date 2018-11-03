//
// Created by nasrat_v on 11/3/18.
//

#include "../header/FrameSubstraction.h"

FrameSubstraction::FrameSubstraction()
{
}

FrameSubstraction::~FrameSubstraction()
{
}

void FrameSubstraction::substractInfos(Frame &frame)
{
    threshImg(frame.getFirstImg().clone(), frame.getSecondImg().clone());
    contoursImg(frame);
    convexHullsImg(frame);
}

void FrameSubstraction::threshImg(cv::Mat firstImgCopy, cv::Mat secondImgCopy)
{
    cv::cvtColor(firstImgCopy, firstImgCopy, CV_BGR2GRAY);
    cv::cvtColor(secondImgCopy, secondImgCopy, CV_BGR2GRAY);
    cv::GaussianBlur(firstImgCopy, firstImgCopy, cv::Size(5, 5), 0);
    cv::GaussianBlur(secondImgCopy, secondImgCopy, cv::Size(5, 5), 0);
    cv::absdiff(firstImgCopy, secondImgCopy, _imgDifference);
    cv::threshold(_imgDifference, _imgThresh, 30, 255.0, CV_THRESH_BINARY);
    cv::imshow("imgThresh", _imgThresh);
    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));
    /*
    cv::dilate(imgThresh, imgThresh, structuringElement7x7);
    cv::erode(imgThresh, imgThresh, structuringElement3x3);
    */
    cv::dilate(_imgThresh, _imgThresh, structuringElement5x5);
    cv::dilate(_imgThresh, _imgThresh, structuringElement5x5);
    cv::erode(_imgThresh, _imgThresh, structuringElement5x5);
}

void FrameSubstraction::contoursImg(Frame &frame)
{
    std::vector<std::vector<cv::Point>> contours;

    cv::findContours(_imgThresh.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    frame.setAllContours(contours);
    //drawAndShowContours(_imgThresh.size(), contours, "imgContours");
}

void FrameSubstraction::convexHullsImg(Frame &frame)
{
    ssize_t  i = -1;
    size_t  contoursSize = frame.getAllContours().size();
    std::vector<std::vector<cv::Point>> convexHulls(contoursSize);

    while (++i < contoursSize)
        cv::convexHull(frame.getAllContours()[i], convexHulls[i]);
    frame.setAllConvexHulls(convexHulls);
    //drawAndShowContours(_imgThresh.size(), convexHulls, "imgConvexHulls");
}
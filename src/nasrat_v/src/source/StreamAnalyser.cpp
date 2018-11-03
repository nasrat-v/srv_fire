//
// Created by nasrat_v on 11/3/18.
//

#include "../header/StreamAnalyser.h"

StreamAnalyser::StreamAnalyser()
{
    _frameCnt = 2;
}

StreamAnalyser::~StreamAnalyser()
{
}


void StreamAnalyser::initAnalyser(const std::string &videoPath)
{
    openVideo(videoPath);
    readFrame();
}

void StreamAnalyser::openVideo(const std::string &videoPath)
{
    _capVideo.open(videoPath);
    if (!_capVideo.isOpened())
        Error::logErrorAbort(Error::ErrorType::OPEN_VID, videoPath);
    else if (_capVideo.get(CV_CAP_PROP_FRAME_COUNT) < MIN_FRAME_VID)
        Error::logErrorAbort(Error::ErrorType::TRUNCATED_VID, videoPath);
}


void StreamAnalyser::readFrame()
{
    cv::Mat first_img;
    cv::Mat second_img;

    _capVideo.read(first_img);
    _capVideo.read(second_img);
    _frame.setFirstImg(first_img);
    _frame.setSecondImg(second_img);
}

void StreamAnalyser::analyseVideo(cv::VideoCapture &capVideo)
{
    while (_capVideo.isOpened())
    {
        _frameSubstracter.substractInfos(_frame);
        _frame.findEntitiesWithInfos();
    }
}

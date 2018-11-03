//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_STREAMANALYSER_H
# define OPENCV_SRV_STREAMANALYSER_H

# define VIDEO_PATH     "768x576.avi"

#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>
#include <string>

#include "../header/output_static_object/Error.hh"
#include "../header/Frame.h"
#include "FrameSubstraction.h"
#include "FrameAddition.h"


class FrameAnalyser
{
public:
    FrameAnalyser();
    ~FrameAnalyser();

    void    initAnalyser(const std::string &videoPath);
    void    analyseFrame(cv::VideoCapture &capVideo);

private:
    /* Methods */
    void    openVideo(const std::string &videoPath);
    void    readFrame();
    void    initSavedEntities();
    void    matchFrameEntitiesToSavedEntities();
    void    setSavedEntityToFrameEntity(const Entity &frameEntity, int &intIndex);
    void    addNewSavedEntity(Entity &frameEntity);
    double  distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint);

    /* Attributes */
    FrameSubstraction   _frameSubstracter;
    FrameAddition       _frameAdditionner;
    cv::VideoCapture    _capVideo;
    std::vector<Entity> _savedEntities;
    Frame               _frame;
    int                 _frameCnt;
    bool                _firstFrame;
};


#endif //OPENCV_SRV_STREAMANALYSER_H

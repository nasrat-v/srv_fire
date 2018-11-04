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
#include "FrameProcessing.h"
#include "FrameAddition.h"


class FrameAnalyser
{
public:
    FrameAnalyser();
    ~FrameAnalyser();

    void                initAnalyser(const std::string &videoPath, Log::debugMode mode);
    int                 analyseFrame();

private:
    /* Attributes */
    FrameProcessing     _frameProcesser;
    FrameAddition       _frameAdditionner;
    cv::VideoCapture    _capVideo;
    std::vector<Entity> _savedEntities;
    Frame               _frame;
    int                 _frameCnt;
    bool                _firstFrame;
    Log::debugMode      _debugMode;

    typedef struct      s_distance
    {
        double          leastDistance;
        size_t          indexEntity;
    }                   t_distance;

    /* Methods */
    void                openVideo(const std::string &videoPath);
    void                readFrame();
    void                initSavedEntities();
    void                matchFrameEntitiesToSavedEntities();
    void                setSavedEntityToFrameEntity(const Entity &frameEntity, size_t index);
    void                addNewSavedEntity(const Entity &frameEntity, int index);
    double              distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint);
    void                predictNextPositionSavedEntities();
    void                checkConsecutiveFrameWithoutMatchSavedEntities();
    void                findClosestFrameEntityForSavedEntity(const Entity &frameEntity, t_distance *distance);
    void                debugPredictedPosition(const Entity &frameEntity, const Entity &savedEntity);
    void                displayImg(cv::Mat img);
};


#endif //OPENCV_SRV_STREAMANALYSER_H

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_STREAMANALYSER_H
# define OPENCV_SRV_STREAMANALYSER_H

# define VIDEO_PATH     "../input/video/video-incendie-pompiers.mp4"

#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>
#include <string>

#include "output_static_object/Error.hh"
#include "Frame.h"
#include "ImageService.h"

class FrameAnalyser
{
public:
    FrameAnalyser(const DebugManager::debugMode &mode, const std::string &videoPath);
    ~FrameAnalyser();

    Error::ErrorType        initAnalyser();
    Error::ErrorType        analyseFrame();

private:
    /* Attributes */
    bool                    _isInit;
    std::vector<Entity>     _savedEntities;
    Frame                   _frame;
    bool                    _firstFrame;
    DebugManager::debugMode _debugMode;
    ImageService            _imageService;

    typedef struct          s_distance
    {
        double              leastDistance;
        size_t              indexEntity;
    }                       t_distance;

    /* Methods */
    void                    findEntities();
    void                    findAllEntitiesWithInfos();
    void                    findEntitiesInMovementWithInfos();
    bool                    isPossibleEntity(const Entity &possibleEntity);
    void                    findClosestMovementEntity(const Entity &entity, t_distance *distance);
    double                  distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint);
    /*void                    initSavedEntities();
    void                    matchFrameEntitiesToSavedEntities();
    void                    setSavedEntityFromFrameEntity(const Entity &frameEntity, size_t index);
    void                    addNewSavedEntity(const Entity &frameEntity, int index);
    void                    predictNextPositionSavedEntities();
    void                    checkConsecutiveFrameWithoutMatchSavedEntities();
    void                    debugPredictedPosition(const Entity &frameEntity);*/
};


#endif //OPENCV_SRV_STREAMANALYSER_H

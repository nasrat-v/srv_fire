//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_STREAMANALYSER_H
# define OPENCV_SRV_STREAMANALYSER_H

# define VIDEO_PATH                 "../input/video/video-incendie-pompiers.mp4"
# define MAX_FRAME_WITHOUT_MATCH    20

#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>
#include <string>

#include "../Log/Error.hh"
#include "Frame.hh"
#include "ImageService.hh"

static std::vector<ScalarColor::t_colorRange> colorToAnalyse = { YELLOW_RANGE, ORANGE_RANGE, RED_RANGE };

class FrameAnalyser
{
public:
    FrameAnalyser(const DebugManager::debugMode &mode, ImageProvider *imageProvider);
    ~FrameAnalyser();

    Error::ErrorType        initAnalyser(bool openVideo);
    Error::ErrorType        analyseFrame();

private:
    /* Attributes */
    bool                    _isInit;
    std::vector<Blob>       _savedBlobs;
    Frame                   _frame;
    bool                    _firstFrame;
    DebugManager::debugMode _debugMode;
    ImageService            _imageService;

    typedef struct          s_distance
    {
        double              leastDistance;
        size_t              indexSavedBlob;
    }                       t_distance;

    /* Methods */
    Error::ErrorType        checkInitialisation(bool &end);
    void                    logicForEachFrame(bool &end);
    void                    findBlobs();
    void                    findEntities();
    void                    findAllBlobsWithInfos();
    bool                    isPossibleBlob(const Blob &possibleBlob);
    void                    findClosestSavedBlob(const Blob &blob, t_distance *distance);
    double                  distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint);
    void                    initSavedBlobs();
    void                    matchFrameBlobsToSavedBlobs();
    void                    setNewValueSavedBlob(const Blob &frameBlob, size_t index);
    void                    addNewSavedBlob(const Blob &frameBlob);
    void                    checkConsecutiveFrameWithoutMatchSavedBlobs();
    /*void                    predictNextPositionSavedEntities();
    void                    debugPredictedPosition(const Entity &frameEntity);
    void                    findEntitiesInMovementWithInfos();*/
};


#endif //OPENCV_SRV_STREAMANALYSER_H

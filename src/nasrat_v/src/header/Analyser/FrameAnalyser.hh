//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_STREAMANALYSER_H
# define OPENCV_SRV_STREAMANALYSER_H

# define VIDEO_PATH                     "../input/video/video-incendie-pompiers.mp4"
# define MAX_FRAME_WITHOUT_MATCH_BLOB   20
# define MAX_FRAME_WITHOUT_MATCH_ENTITY 10
# define INDEX_SAVED_BLOB_NOT_FOUND     (size_t)-1

#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>
#include <iostream>
#include <string>

#include "Frame.hh"
#include "ImageService.hh"
#include "BlobFilter.hh"
#include "EntityFilter.hh"
#include "IdManager.hpp"
#include "../Log/Error.hh"

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
    std::vector<Entity>     _savedEntities;
    Frame                   _frame;
    bool                    _firstFrameBlob;
    bool                    _firstFrameEntity;
    DebugManager::debugMode _debugMode;
    ImageService            _imageService;
    BlobFilter              _blobFilter;
    EntityFilter            _entityFilter;

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
    void                    findAllEntitiesWithInfos();
    void                    findContoursAllBlobs(std::vector<std::vector<cv::Point>> &allContours);
    void                    findClosestSavedBlob(const Blob &blob, t_distance *distance);
    void                    findClosestSavedEntity(const Blob &blob, t_distance *distance);
    double                  distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint);
    void                    initSavedBlobs();
    void                    initSavedEntities();
    void                    matchFrameBlobsToSavedBlobs();
    void                    matchFrameEntitiesToSavedEntities();
    void                    matchSavedBlobsToSavedEntities();
    void                    mergeSavedBlobAndFrameBlob(const Blob &frameBlob, size_t index);
    void                    mergeSavedEntityAndFrameEntity(const Entity &frameEntity, size_t index);
    Blob                    mergeBlobs(const Blob &savedBlob, const Blob &frameBlob);
    void                    addNewSavedBlob(const Blob &frameBlob);
    void                    addNewSavedEntity(const Entity &frameEntity);
    void                    checkConsecutiveFrameWithoutMatchSavedBlobs();
    void                    checkConsecutiveFrameWithoutMatchSavedEntities();
    /*void                    predictNextPositionSavedEntities();
    void                    debugPredictedPosition(const Entity &frameEntity);
    void                    findEntitiesInMovementWithInfos();*/
};


#endif //OPENCV_SRV_STREAMANALYSER_H

//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGESERVICE_H
# define OPENCV_SRV_IMAGESERVICE_H

# define NB_IMG_INCR    2

#include "ImageProvider.h"
#include "ImageProcesser.h"
#include "ImageAdditionner.h"
#include "DebugManager.h"

class ImageService
{
public:
    ImageService(const DebugManager::debugMode &mode, const std::string &videoPath);
    ~ImageService();

    void                        substractInfosAllEntities(Frame &frame);
    void                        substractInfosEntitiesInMovement(Frame &frame);
    ImageProvider::statusVideo  openVideo();
    ImageProvider::statusVideo  getNextImg(Frame &frame);
    void                        displayImg(cv::Mat img, /*const std::vector<Entity> &savedEntities,*/ const std::vector<Entity> &frameEntities);

private:
    /* Methods */
    void                        substractColor(cv::Mat &imgProcessed);
    void                        differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed);
    void                        threshImg(cv::Mat &imgProcessed);
    void                        setAllContoursFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setAllConvexHullsFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setContoursMovementFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setConvexHullsMovementFrame(Frame &frame, const cv::Mat &imgProcessed);
    ImageProvider::statusVideo  incrementImg(Frame &frame);
    ImageProvider::statusVideo  initImg(Frame &frame);

    /* Attributes */
    bool                        _firstTime;
    DebugManager::debugMode     _debugMode;
    ImageProvider               _imageProvider;
    ImageProcesser              _imageProcesser;
    ImageAdditionner            _imageAdditionner;
};


#endif //OPENCV_SRV_IMAGESERVICE_H

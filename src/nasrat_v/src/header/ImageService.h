//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGESERVICE_H
# define OPENCV_SRV_IMAGESERVICE_H

# define NB_IMG_INCR    5

#include "ImageProvider.h"
#include "ImageProcesser.h"
#include "ImageAdditionner.h"

class ImageService
{
public:
    ImageService(const Log::debugMode &mode, const std::string &videoPath);
    ~ImageService();

    void                        substractInfos(Frame &frame, const Entity::entityType &type);
    ImageProvider::statusVideo  openVideo();
    ImageProvider::statusVideo  getNextImg(Frame &frame);
    void                        displayImg(cv::Mat img, /*const std::vector<Entity> &savedEntities,*/ const std::vector<Entity> &frameEntities);

private:
    /* Methods */
    void                        differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed, const Entity::entityType &type);
    void                        threshImg(cv::Mat &imgProcessed, const Entity::entityType &type);
    void                        setContoursFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setConvexHullsFrame(Frame &frame, const cv::Mat &imgProcessed);
    ImageProvider::statusVideo  incrementImg(Frame &frame);
    ImageProvider::statusVideo  initImg(Frame &frame);

    /* Attributes */
    bool                        _firstTime;
    Log::debugMode              _debugMode;
    ImageProvider               _imageProvider;
    ImageProcesser              _imageProcesser;
    ImageAdditionner            _imageAdditionner;
};


#endif //OPENCV_SRV_IMAGESERVICE_H

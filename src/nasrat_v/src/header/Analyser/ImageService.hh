//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGESERVICE_H
# define OPENCV_SRV_IMAGESERVICE_H

# define NB_IMG_INCR    2

#include "ImageProvider.hh"
#include "ImageProcesser.hh"
#include "ImageAdditionner.hh"
#include "../Launcher/DebugManager.hh"

#define RED_RANGE       ImageProcesser::t_colorRange { "Red Range", cv::Scalar(0, 150, 100), cv::Scalar(10, 255, 255) }
#define ORANGE_RANGE    ImageProcesser::t_colorRange { "Orange Range", cv::Scalar(11, 150, 100), cv::Scalar(20, 255, 255) }
#define YELLOW_RANGE    ImageProcesser::t_colorRange { "Yellow Range", cv::Scalar(21, 150, 100), cv::Scalar(30, 255, 255) }

class ImageService
{
public:
    ImageService(const DebugManager::debugMode &mode, ImageProvider *imageProvider);
    ~ImageService();

    void                        substractInfosAllEntities(Frame &frame);
    void                        substractInfosEntitiesInMovement(Frame &frame);
    ImageProvider::statusVideo  openVideo();
    ImageProvider::statusVideo  getNextImg(Frame &frame);
    void                        displayImg(cv::Mat img, const std::vector<Entity> &savedEntities,
                                                        const std::vector<Entity> &frameEntities);
    ImageProvider::statusVideo  createSampleImgFromVideo();

private:
    /* Methods */
    void                        substractColor(cv::Mat &imgProcessed, const ImageProcesser::t_colorRange &range);
    void                        differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed);
    void                        threshImg(cv::Mat &imgProcessed);
    void                        mergeAllContours(cv::Mat &img, Frame &frame);
    void                        mergeAllConvexHulls(cv::Mat &img, Frame &frame);
    void                        setContoursMergedFrame(Frame &frame);
    void                        setConvexHullsMergedFrame(Frame &frame);
    void                        setContoursWarmFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setConvexHullsWarmFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setContoursHotFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setConvexHullsHotFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setContoursVeryHotFrame(Frame &frame, const cv::Mat &imgProcessed);
    void                        setConvexHullsVeryHotFrame(Frame &frame, const cv::Mat &imgProcessed);
    //void                        setContoursMovementFrame(Frame &frame, const cv::Mat &imgProcessed);
    //void                        setConvexHullsMovementFrame(Frame &frame, const cv::Mat &imgProcessed);
    ImageProvider::statusVideo  incrementImg(Frame &frame);
    ImageProvider::statusVideo  initImg(Frame &frame);

    /* Attributes */
    bool                        _firstTime;
    DebugManager::debugMode     _debugMode;
    ImageProvider               *_imageProvider;
    ImageProcesser              _imageProcesser;
    ImageAdditionner            _imageAdditionner;
};


#endif //OPENCV_SRV_IMAGESERVICE_H

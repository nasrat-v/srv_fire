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

class ImageService
{
public:
    ImageService(const DebugManager::debugMode &mode, ImageProvider *imageProvider);
    ~ImageService();

    void                        substractInfosPossibleBlobs(Frame &frame,
                                                            const std::vector<ScalarColor::t_colorRange> &colorRanges);
    void                        substractInfosPossibleEntities(Frame &frame,
                                                                const std::vector<std::vector<cv::Point>> &allContours);
    void                        substractInfosBlobsInMovement(Frame &frame);
    ImageProvider::statusVideo  openVideo();
    ImageProvider::statusVideo  getNextImg(Frame &frame);
    void                        displayImg(cv::Mat img, const std::vector<Blob> &savedBlobs,
                                                        const std::vector<Blob> &frameBlobs,
                                                        const std::vector<Entity> &savedEntities,
                                                        const std::vector<Entity> &frameEntities);
    ImageProvider::statusVideo  createSampleImgFromVideo();

private:
    /* Methods */
    void                        substractColor(cv::Mat &imgProcessed, const ScalarColor::t_colorRange &range);
    void                        differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed);
    void                        threshImg(cv::Mat &imgProcessed);
    void                        addFormBlob(Frame &frame, const cv::Mat &imgProcessed,
                                            const ScalarColor::t_colorRange &colorRange);
    void                        addFormEntity(Frame &frame, const cv::Mat &imgMerge);
    void                        findContoursFrame(const cv::Mat &imgProcessed,
                                                    const ScalarColor::t_colorRange &colorRange,
                                                    std::vector<std::vector<cv::Point>> &contours);
    void                        findConvexHullsFrame(const cv::Size &imageSize,
                                                    const ScalarColor::t_colorRange &colorRange,
                                                    const std::vector<std::vector<cv::Point>> &contours,
                                                    std::vector<std::vector<cv::Point>> &convexHulls);
    void                        mergeAllContours(cv::Mat &img, const std::vector<std::vector<cv::Point>> &allContours);
    void                        findContoursMergedFrame(const cv::Mat &imgMerge,
                                                        std::vector<std::vector<cv::Point>> &contoursMerged);
    void                        findConvexHullsMergedFrame(const cv::Size &imageSize,
                                                           const std::vector<std::vector<cv::Point>> &contoursMerged,
                                                           std::vector<std::vector<cv::Point>> &convexHullsMerged);
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

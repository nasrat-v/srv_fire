//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGEPROVIDER_H
# define OPENCV_SRV_IMAGEPROVIDER_H

#include <thread>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>

#include "Log/Error.hh"
#include "Frame.hh"
#include "DebugManager.hh"
#include "ParamManager.hh"

# define IMG_PATH "../input/image/sample-image"
# define IMG_FORMAT ".jpg"

class ImageProvider
{
public:
    explicit ImageProvider(const std::string &videoPath);
    ~ImageProvider();

    enum class statusVideo
    {
        OPEN,
        START,
        CONTINUE,
        END,
        ERROR
    };

    statusVideo         openVideo();
    statusVideo         initImg(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImg(cv::Mat &nextImage, size_t nbImgIncr);
    statusVideo         videoContinues();
    void                createSampleImgFromVideo();
    void                setCanReadImage(bool status);
    void                setImageNetworkPath(const std::string &path);
    void                setDebugMode(const DebugManager::debugMode &mode);
    void                setParamMode(const ParamManager::paramMode &mode);

private:
    /* Methods */
    statusVideo         openImg(const std::string &path, cv::Mat &imgRead);
    statusVideo         initImgVideo(std::vector<cv::Mat> &imgs, size_t nbImgIncr); // default
    statusVideo         incrementImgVideo(cv::Mat &nextImage); // default
    statusVideo         initImgPng(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImgPng(cv::Mat &nextImage, size_t nbImgIncr);
    statusVideo         initImgNetwork(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImgNetwork(cv::Mat &nextImage);
    void                resetImageNetworkPath();

    /* Attributes */
    DebugManager::debugMode _debugMode;
    ParamManager::paramMode _paramMode;
    cv::VideoCapture        _capVideo;
    std::string             _videoPath;
    bool                    _canReadImage;
    std::string             _imageNetworkPath;
};


#endif //OPENCV_SRV_IMAGEPROVIDER_H

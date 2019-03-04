//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGEPROVIDER_H
# define OPENCV_SRV_IMAGEPROVIDER_H

#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>

#include "Log/Error.hh"
#include "Frame.h"
#include "DebugManager.h"

# define IMG_PATH "../input/image/sample-image"
# define IMG_FORMAT ".jpg"

class ImageProvider
{
public:
    explicit ImageProvider(const DebugManager::debugMode &mode, const std::string &videoPath);
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

private:
    /* Methods */
    statusVideo         openImg(size_t idPath, cv::Mat &imgRead);
    statusVideo         initImgVideo(std::vector<cv::Mat> &imgs, size_t nbImgIncr); // default
    statusVideo         incrementImgVideo(cv::Mat &nextImage); // default
    statusVideo         initImgPng(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImgPng(cv::Mat &nextImage, size_t nbImgIncr);

    /* Attributes */
    DebugManager::debugMode _debugMode;
    cv::VideoCapture        _capVideo;
    std::string             _videoPath;
};


#endif //OPENCV_SRV_IMAGEPROVIDER_H

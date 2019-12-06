//
// Created by nasrat_v on 11/6/18.
//

#ifndef OPENCV_SRV_IMAGEPROVIDER_H
# define OPENCV_SRV_IMAGEPROVIDER_H

#include <thread>
#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/videoio/videoio_c.h>

#include "../Log/Error.hh"
#include "Frame.hh"
#include "../Launcher/DebugManager.hh"
#include "../Launcher/ParamManager.hh"

# define IMG_PATH "../input/image/sample-image"
# define IMG_FORMAT ".jpg"

class ImageProvider
{
public:
    ImageProvider(const char *defaultVideoPath,
                            const DebugManager::debugMode &debugMode);
    ~ImageProvider();

    enum class statusVideo
    {
        OPEN,
        START,
        CONTINUE,
        END,
        ERROR,
        IGNORE_WAIT
    };

    statusVideo         openVideo();
    statusVideo         initImg(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImg(cv::Mat &nextImage, size_t nbImgIncr);
    statusVideo         videoContinues();
    void                createSampleImgFromVideo();
    //void                setCanReadImage(bool status);
    //void                setImageNetworkPath(const std::string &path);

private:
    /* Methods */
    statusVideo         openImg(const std::string &path, cv::Mat &imgRead);
    statusVideo         initImgVideo(std::vector<cv::Mat> &imgs, size_t nbImgIncr); // default
    statusVideo         incrementImgVideo(cv::Mat &nextImage); // default
    statusVideo         initImgPng(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    statusVideo         incrementImgPng(cv::Mat &nextImage, size_t nbImgIncr);
    //statusVideo         initImgNetwork(std::vector<cv::Mat> &imgs, size_t nbImgIncr);
    //statusVideo         incrementImgNetwork(cv::Mat &nextImage);
    //void                resetImageNetworkPath();

    /* Attributes */
    DebugManager::debugMode _debugMode;
    cv::VideoCapture        _capVideo;
    const char              *_videoPath;
};


#endif //OPENCV_SRV_IMAGEPROVIDER_H

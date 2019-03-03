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
    statusVideo         incrementImg(cv::Mat &nextImage);
    statusVideo         videoContinues();

private:
    cv::VideoCapture    _capVideo;
    std::string         _videoPath;
};


#endif //OPENCV_SRV_IMAGEPROVIDER_H

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_IMAGEADDITIONNER_H
# define OPENCV_SRV_IMAGEADDITIONNER_H

#include "Blob.hh"
#include "ScalarColor.hpp"

#include <opencv2/highgui/highgui.hpp>

class ImageAdditionner
{
public:
    ImageAdditionner();
    ~ImageAdditionner();

    void                drawContours(cv::Mat &img, const std::vector<std::vector<cv::Point>> &contours);
    void                drawAndShowContours(const cv::Size &imageSize,
                                            const std::vector<Blob> &blobs,
                                            const std::string &strImageName);
    void                drawAndShowContours(const cv::Size &imageSize,
                                            const std::vector<std::vector<cv::Point>> &contours,
                                            const std::string &strImageName,
                                            const ScalarColor::t_colorRange &colorRange);
    void                drawTrackBlobsOnImage(const std::vector<Blob> &savedBlobs,
                                                 const std::vector<Blob> &frameBlobs,cv::Mat &img);
    void                drawNumberBlobsOnImage(const std::vector<Blob> &blobs, cv::Mat &img);
};


#endif //OPENCV_SRV_IMAGEADDITIONNER_H

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_IMAGEADDITIONNER_H
# define OPENCV_SRV_IMAGEADDITIONNER_H

# define SCALAR_BLACK   cv::Scalar(0.0, 0.0, 0.0)
# define SCALAR_WHITE   cv::Scalar(255.0, 255.0, 255.0)
# define SCALAR_YELLOW  cv::Scalar(0.0, 255.0, 255.0)
# define SCALAR_GREEN   cv::Scalar(0.0, 200.0, 0.0)
# define SCALAR_RED     cv::Scalar(0.0, 0.0, 255.0)
# define SCALAR_BLUE    cv::Scalar(255.0, 0.0, 0.0)
# define SCALAR_ORANGE  cv::Scalar(0.0 ,165.0 , 255.0)

#include "Blob.hh"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageAdditionner
{
public:
    ImageAdditionner();
    ~ImageAdditionner();

    void                drawContours(cv::Mat &img, const std::vector<std::vector<cv::Point>> &contours);
    void                drawAndShowContours(cv::Size imageSize,
                                            const std::vector<Blob> &blobs,
                                            const std::string &strImageName);
    void                drawAndShowContours(cv::Size imageSize,
                                            const std::vector<std::vector<cv::Point>> &contours,
                                            const std::string &strImageName,
                                            const Blob::blobTemperature &temp = Blob::blobTemperature::NO_TEMP);
    void                drawTrackBlobsOnImage(const std::vector<Blob> &savedBlobs,
                                                 const std::vector<Blob> &frameBlobs,cv::Mat &img);
    void                drawNumberBlobsOnImage(const std::vector<Blob> &blobs, cv::Mat &img);
};


#endif //OPENCV_SRV_IMAGEADDITIONNER_H

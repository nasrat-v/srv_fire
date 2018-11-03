//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAME_H
#define OPENCV_SRV_FRAME_H

#include <opencv2/core/mat.hpp>

#include "Entity.h"

class Frame
{
public:
    Frame();
    ~Frame();

    void                                        setFirstImg(const cv::Mat &img);
    void                                        setSecondImg(const cv::Mat &img);
    void                                        setAllContours(std::vector<std::vector<cv::Point>> contours);
    void                                        setAllConvexHulls(std::vector<std::vector<cv::Point>> convexHulls);
    const cv::Mat                               &getFirstImg() const;
    const cv::Mat                               &getSecondImg() const;
    const std::vector<Entity>                   &getEntity();
    const std::vector<std::vector<cv::Point>>   &getAllContours() const;
    const std::vector<std::vector<cv::Point>>   &getAllConvexHulls() const;
    void                                        findEntitiesWithInfos();

private:
    /* Methods*/
    void                                        analyseInfos();

    /* Attributes */
    char                                _readyForAnalyse;
    cv::Mat                             _firstImg;
    cv::Mat                             _secondImg;
    std::vector<Entity>                 _blobs;
    std::vector<std::vector<cv::Point>> _allContours;
    std::vector<std::vector<cv::Point>> _allConvexHulls;
};


#endif //OPENCV_SRV_FRAME_H

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAME_H
# define OPENCV_SRV_FRAME_H

#include <opencv2/core/mat.hpp>

#include "Entity.h"
#include "output_static_object/Error.hh"
#include "ImageProcesser.h"

class Frame
{
public:
    Frame();
    ~Frame();

    void                                        setFirstImg(const cv::Mat &img);
    void                                        setSecondImg(const cv::Mat &img);
    void                                        setAllContours(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setAllConvexHulls(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setCurrentMatchFoundOrNewEntity(int index, bool val);
    const cv::Mat                               &getFirstImg() const;
    const cv::Mat                               &getSecondImg() const;
    const std::vector<Entity>                   &getEntities() const;
    const std::vector<std::vector<cv::Point>>   &getAllContours() const;
    const std::vector<std::vector<cv::Point>>   &getAllConvexHulls() const;
    Error::ErrorType                            findEntitiesWithInfos(const Entity::entityType &type);
    void                                        clearEntities();

private:
    /* Methods*/
    void                                        analyseInfos(const Entity::entityType &type);

    /* Attributes */
    short                                       _readyForAnalyse;
    cv::Mat                                     _firstImg;
    cv::Mat                                     _secondImg;
    std::vector<Entity>                         _entities;
    std::vector<std::vector<cv::Point>>         _allContours;
    std::vector<std::vector<cv::Point>>         _allConvexHulls;
};


#endif //OPENCV_SRV_FRAME_H

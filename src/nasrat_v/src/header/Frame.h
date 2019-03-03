//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAME_H
# define OPENCV_SRV_FRAME_H

#include <opencv2/core/mat.hpp>

#include "Entity.h"
#include "Log/Error.hh"
#include "ImageProcesser.h"

class Frame
{
public:
    Frame();
    ~Frame();

    void                                        addImage(const cv::Mat &img);
    void                                        setImage(const cv::Mat &img, size_t index);
    void                                        setContoursWarm(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setConvexHullsWarm(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setContoursHot(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setConvexHullsHot(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setContoursVeryHot(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setConvexHullsVeryHot(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setContoursMovement(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setConvexHullsMovement(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setCurrentMatchFoundOrNewEntity(int index, bool val);
    void                                        setMovementTypeEntity(size_t index, const Entity::entityMovement &type);
    void                                        setTemperatureTypeEntity(size_t index, const Entity::entityTemperature &type);
    const std::vector<cv::Mat>                  &getImages() const;
    const std::vector<Entity>                   &getEntities() const;
    const std::vector<std::vector<cv::Point>>   &getContoursWarm() const;
    const std::vector<std::vector<cv::Point>>   &getConvexHullsWarm() const;
    const std::vector<std::vector<cv::Point>>   &getContoursHot() const;
    const std::vector<std::vector<cv::Point>>   &getConvexHullsHot() const;
    const std::vector<std::vector<cv::Point>>   &getContoursVeryHot() const;
    const std::vector<std::vector<cv::Point>>   &getConvexHullsVeryHot() const;
    const std::vector<std::vector<cv::Point>>   &getContoursMovement() const;
    const std::vector<std::vector<cv::Point>>   &getConvexHullsMovement() const;
    void                                        clearEntities();
    void                                        predictNextPositionEntities();
    void                                        addEntity(const Entity &entity);

private:
    /* Attributes */
    std::vector<cv::Mat>                        _images;
    std::vector<Entity>                         _entities;
    std::vector<std::vector<cv::Point>>         _contoursWarm;
    std::vector<std::vector<cv::Point>>         _convexHullsWarm;
    std::vector<std::vector<cv::Point>>         _contoursHot;
    std::vector<std::vector<cv::Point>>         _convexHullsHot;
    std::vector<std::vector<cv::Point>>         _contoursVeryHot;
    std::vector<std::vector<cv::Point>>         _convexHullsVeryHot;
    std::vector<std::vector<cv::Point>>         _contoursMovement;
    std::vector<std::vector<cv::Point>>         _convexHullsMovement;
};


#endif //OPENCV_SRV_FRAME_H

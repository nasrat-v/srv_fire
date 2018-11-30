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

    void                                        addImage(const cv::Mat &img);
    void                                        setImage(const cv::Mat &img, size_t index);
    void                                        setAllContours(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setAllConvexHulls(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setContoursMovement(const std::vector<std::vector<cv::Point>> &contours);
    void                                        setConvexHullsMovement(const std::vector<std::vector<cv::Point>> &convexHulls);
    void                                        setCurrentMatchFoundOrNewEntity(int index, bool val);
    void                                        setTypeEntity(int index, const Entity::entityType &type);
    const std::vector<cv::Mat>                  &getImages() const;
    const std::vector<Entity>                   &getEntities() const;
    const std::vector<std::vector<cv::Point>>   &getAllContours() const;
    const std::vector<std::vector<cv::Point>>   &getAllConvexHulls() const;
    const std::vector<std::vector<cv::Point>>   &getContoursMovement() const;
    const std::vector<std::vector<cv::Point>>   &getConvexHullsMovement() const;
    void                                        clearEntities();
    void                                        predictNextPositionEntities();
    void                                        addEntity(const Entity &entity);

private:
    /* Attributes */
    std::vector<cv::Mat>                        _images;
    std::vector<Entity>                         _entities;
    std::vector<std::vector<cv::Point>>         _allContours;
    std::vector<std::vector<cv::Point>>         _allConvexHulls;
    std::vector<std::vector<cv::Point>>         _contoursMovement;
    std::vector<std::vector<cv::Point>>         _convexHullsMovement;
};


#endif //OPENCV_SRV_FRAME_H

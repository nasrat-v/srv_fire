//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/Frame.hh"

Frame::Frame() = default;

Frame::~Frame() = default;

void Frame::addImage(const cv::Mat &img)
{
    _images.push_back(img);
}

void Frame::setImage(const cv::Mat &img, size_t index)
{
    _images.at(index) = img;
}

void Frame::setContoursWarm(const std::vector<std::vector<cv::Point>> &contours)
{
    _contoursWarm = contours;
}

void Frame::setConvexHullsWarm(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _convexHullsWarm = convexHulls;
}

void Frame::setContoursHot(const std::vector<std::vector<cv::Point>> &contours)
{
    _contoursHot = contours;
}

void Frame::setConvexHullsHot(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _convexHullsHot = convexHulls;
}

void Frame::setContoursVeryHot(const std::vector<std::vector<cv::Point>> &contours)
{
    _contoursVeryHot = contours;
}

void Frame::setConvexHullsVeryHot(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _convexHullsVeryHot = convexHulls;
}

void Frame::setContoursMerged(const std::vector<std::vector<cv::Point>> &contours)
{
    _contoursMerged = contours;
}

void Frame::setConvexHullsMerged(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _convexHullsMerged = convexHulls;
}

void Frame::setMovementTypeEntity(size_t index, const Entity::entityMovement &type)
{
    _entities.at(index).setMovementType(type);
}

void Frame::setTemperatureTypeEntity(size_t index, const Entity::entityTemperature &type)
{
    _entities.at(index).setTemperatureType(type);
}

const std::vector<cv::Mat> &Frame::getImages() const
{
    return (_images);
}

const std::vector<Entity> &Frame::getEntities() const
{
    return (_entities);
}

const std::vector<std::vector<cv::Point>> &Frame::getContoursWarm() const
{
    return (_contoursWarm);
}

const std::vector<std::vector<cv::Point>> &Frame::getConvexHullsWarm() const
{
    return (_convexHullsWarm);
}

const std::vector<std::vector<cv::Point>> &Frame::getContoursHot() const
{
    return (_contoursHot);
}

const std::vector<std::vector<cv::Point>> &Frame::getConvexHullsHot() const
{
    return (_convexHullsHot);
}

const std::vector<std::vector<cv::Point>> &Frame::getContoursVeryHot() const
{
    return (_contoursVeryHot);
}

const std::vector<std::vector<cv::Point>> &Frame::getConvexHullsVeryHot() const
{
    return (_convexHullsVeryHot);
}

const std::vector<std::vector<cv::Point>> &Frame::getContoursMerged() const
{
    return (_contoursMerged);
}

const std::vector<std::vector<cv::Point>> &Frame::getConvexHullsMerged() const
{
    return (_convexHullsMerged);
}

void Frame::clearEntities()
{
    _entities.clear();
}

void Frame::predictNextPositionEntities()
{
    for (auto &entity : _entities)
        entity.predictNextPosition();
}

void Frame::addEntity(const Entity &entity)
{
    _entities.push_back(entity);
}
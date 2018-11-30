//
// Created by nasrat_v on 11/3/18.
//

#include "../header/Frame.h"

Frame::Frame()
{
}

Frame::~Frame() = default;

void Frame::addImage(const cv::Mat &img)
{
    _images.push_back(img);
}

void Frame::setImage(const cv::Mat &img, size_t index)
{
    _images.at(index) = img;
}

void Frame::setAllContours(const std::vector<std::vector<cv::Point>> &contours)
{
    _allContours = contours;
}

void Frame::setAllConvexHulls(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _allConvexHulls = convexHulls;
}

void Frame::setContoursMovement(const std::vector<std::vector<cv::Point>> &contours)
{
    _contoursMovement = contours;
}

void Frame::setConvexHullsMovement(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _convexHullsMovement = convexHulls;
}

void Frame::setCurrentMatchFoundOrNewEntity(int index, bool val)
{
    _entities[index].setCurrentMatchFoundOrNewEntity(val);
}

void Frame::setTypeEntity(int index, const Entity::entityType &type)
{
    _entities.at(index).setType(type);
}

const std::vector<cv::Mat> &Frame::getImages() const
{
    return (_images);
}

const std::vector<Entity> &Frame::getEntities() const
{
    return (_entities);
}

const std::vector<std::vector<cv::Point>> &Frame::getAllContours() const
{
    return (_allContours);
}

const std::vector<std::vector<cv::Point>> &Frame::getAllConvexHulls() const
{
    return (_allConvexHulls);
}

const std::vector<std::vector<cv::Point>> &Frame::getContoursMovement() const
{
    return (_contoursMovement);
}

const std::vector<std::vector<cv::Point>> &Frame::getConvexHullsMovement() const
{
    return (_convexHullsMovement);
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
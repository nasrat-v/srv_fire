//
// Created by nasrat_v on 11/3/18.
//

#include "../header/Frame.h"

Frame::Frame()
{
    _readyForAnalyse = 0;
}

Frame::~Frame() = default;

void Frame::setFirstImg(const cv::Mat &img)
{
    _firstImg = img;
}

void Frame::setSecondImg(const cv::Mat &img)
{
    _secondImg = img;
}

void Frame::setAllContours(const std::vector<std::vector<cv::Point>> &contours)
{
    _allContours = contours;
    _readyForAnalyse += 1;
}

void Frame::setAllConvexHulls(const std::vector<std::vector<cv::Point>> &convexHulls)
{
    _allConvexHulls = convexHulls;
    _readyForAnalyse += 1;
}

void Frame::setCurrentMatchFoundOrNewEntity(int index, bool val)
{
    _entities[index].setCurrentMatchFoundOrNewEntity(val);
}

const cv::Mat &Frame::getFirstImg() const
{
    return (_firstImg);
}

const cv::Mat &Frame::getSecondImg() const
{
    return (_secondImg);
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

void Frame::clearEntities()
{
    _entities.clear();
}

void Frame::analyseInfos(const Entity::entityType &type)
{
    for (auto &convexHull : _allConvexHulls)
    {
        Entity possibleBlob(convexHull);

        if (possibleBlob.getCurrentBoundingRect().area() > 100 && possibleBlob.getCurrentAspectRatio() >= 0.2 &&
            possibleBlob.getCurrentAspectRatio() <= 1.25 && possibleBlob.getCurrentBoundingRect().width > 20 &&
            possibleBlob.getCurrentBoundingRect().height > 20 && possibleBlob.getCurrentDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleBlob.getContour()) / (double)possibleBlob.getCurrentBoundingRect().area()) > 0.40)
        {
            possibleBlob.setType(type);
            _entities.push_back(possibleBlob);
        }
    }
}

Error::ErrorType Frame::findEntitiesWithInfos(const Entity::entityType &type)
{
    if (_readyForAnalyse > 1)
    {
        analyseInfos(type);
        _readyForAnalyse = 0;
        return (Error::ErrorType::NO_ERROR);
    }
    Error::logError(Error::ErrorType::MISSING_FRAME_INFOS);
    return (Error::ErrorType::NO_ERROR);
}
//
// Created by nasrat_v on 11/3/18.
//

#include "../header/Entity.h"

Entity::Entity(const std::vector<cv::Point> &contour)
{
    _contour = contour;
    initCurrentAttributes();
    initCenterPosition();
    _stillBeingTracked = true;
    _currentMatchFoundOrNewBlob = true;
    _numOfConsecutiveFramesWithoutMatch = 0;
}

Entity::~Entity()
{
}

void Entity::initCurrentAttributes()
{
    _currentBoundingRect = cv::boundingRect(_contour);
    _currentDiagonalSize = sqrt(pow(_currentBoundingRect.width, 2) + pow(_currentBoundingRect.height, 2));
    _currentAspectRatio = ((float)_currentBoundingRect.width / (float)_currentBoundingRect.height);
}

void Entity::initCenterPosition()
{
    cv::Point currentCenter;

    currentCenter.x = ((_currentBoundingRect.x + _currentBoundingRect.x + _currentBoundingRect.width) / 2);
    currentCenter.y = ((_currentBoundingRect.y + _currentBoundingRect.y + _currentBoundingRect.height) / 2);
    _centerPositions.push_back(currentCenter);
}

const double    &Entity::getCurrentAspectRatio()
{
    return (_currentAspectRatio);
}

const double    &Entity::getCurrentDiagonalSize()
{
    return (_currentDiagonalSize);
}

const cv::Rect  &Entity::getCurrentBoundingRect()
{
    return (_currentBoundingRect);
}

const std::vector<cv::Point>    &Entity::getContour()
{
    return (_contour);
}

const bool Entity::getStillBeingTracked()
{
    return (_stillBeingTracked);
}

void Entity::predictNextPosition()
{
    int deltaX;
    int deltaY;
    int n = 0;
    int sumOfChanges[2];
    auto numPositions = (int)_centerPositions.size();
    int i = numPositions;

    if (numPositions == 1)
    {
        _predictedNextPosition.x = _centerPositions.back().x;
        _predictedNextPosition.y = _centerPositions.back().y;
    }
    else if (numPositions > 1 && numPositions < 5)
    {
        while ((i - 2) >= 0)
            calculateSumOfChanges(sumOfChanges, &i, &n);
    }
    else
    {
        while (i > (numPositions - (5 - 1)))
            calculateSumOfChanges(sumOfChanges, &i, &n);
    }
    deltaX = (int)std::round((float)sumOfChanges[0] / ((n * 2) - 1));
    deltaY = (int)std::round((float)sumOfChanges[1] / ((n * 2) - 1));
    _predictedNextPosition.x = (_centerPositions.back().x + deltaX);
    _predictedNextPosition.y = (_centerPositions.back().y + deltaY);
}

void Entity::calculateSumOfChanges(int *sumOfChanges, int *i, int *n)
{
    sumOfChanges[0] += ((_centerPositions[(*i) - 2].x - _centerPositions[(*i) - 1].x) * (*n));
    sumOfChanges[1] += ((_centerPositions[(*i) - 2].y - _centerPositions[(*i) - 1].y) * (*n));
    i -= 1;
    n += 1;
}

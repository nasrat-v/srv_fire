//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/Entity.hh"

Entity::Entity(const std::vector<cv::Point> &contour)
{
    _contour = contour;
    initCurrentAttributes();
    initCenterPosition();
    _movementType = entityMovement::STATIC;
    _temperatureType = entityTemperature::WARM;
    _currentMatchFoundOrNewEntity = true;
    /*_stillBeingTracked = true;
    _numOfConsecutiveFramesWithoutMatch = 0;*/
}

Entity::~Entity() = default;

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

double Entity::getCurrentAspectRatio() const
{
    return (_currentAspectRatio);
}

double Entity::getCurrentDiagonalSize() const
{
    return (_currentDiagonalSize);
}

const cv::Rect &Entity::getCurrentBoundingRect() const
{
    return (_currentBoundingRect);
}

const std::vector<cv::Point> &Entity::getContour() const
{
    return (_contour);
}

const std::vector<cv::Point> &Entity::getCenterPositions() const
{
    return (_centerPositions);
}

const Entity::entityMovement &Entity::getMovementType() const
{
    return (_movementType);
}

const Entity::entityTemperature &Entity::getTemperatureType() const
{
    return (_temperatureType);
}

void Entity::setCurrentMatchFoundOrNewEntity(bool val)
{
    _currentMatchFoundOrNewEntity = val;
}

void Entity::setMovementType(const Entity::entityMovement &type)
{
    _movementType = type;
}

void Entity::setTemperatureType(const Entity::entityTemperature &type)
{
    _temperatureType = type;
}

void Entity::predictNextPosition()
{
    short deltaX;
    short deltaY;
    t_sumOfChanges sumOfChanges;
    short numPositions = (short)_centerPositions.size();
    sumOfChanges.posX = 0;
    sumOfChanges.posY = 0;
    sumOfChanges.changesLeft = numPositions;
    sumOfChanges.nbChanges = 0;

    if (numPositions == 1)
    {
        _predictedNextPosition.x = _centerPositions.back().x;
        _predictedNextPosition.y = _centerPositions.back().y;
    }
    else if (numPositions > 1 && numPositions < NB_FRAME_MOVE_PREDICTION)
    {
        while ((sumOfChanges.changesLeft - 2) >= 0)
            calculateSumOfChanges(sumOfChanges);
    }
    else
    {
        while (sumOfChanges.changesLeft > (numPositions - (NB_FRAME_MOVE_PREDICTION - 1)))
            calculateSumOfChanges(sumOfChanges);
    }
    deltaX = (short)std::round((float)sumOfChanges.posX / ((sumOfChanges.nbChanges * 2) - 1));
    deltaY = (short)std::round((float)sumOfChanges.posY / ((sumOfChanges.nbChanges * 2) - 1));
    _predictedNextPosition.x = (_centerPositions.back().x + deltaX);
    _predictedNextPosition.y = (_centerPositions.back().y + deltaY);
}

void Entity::calculateSumOfChanges(t_sumOfChanges &sumOfChanges)
{
    sumOfChanges.posX += ((_centerPositions[sumOfChanges.changesLeft - 2].x - _centerPositions[sumOfChanges.changesLeft - 1].x) * sumOfChanges.nbChanges);
    sumOfChanges.posY += ((_centerPositions[sumOfChanges.changesLeft - 2].y - _centerPositions[sumOfChanges.changesLeft - 1].y) * sumOfChanges.nbChanges);
    sumOfChanges.changesLeft -= 1;
    sumOfChanges.nbChanges += 1;
}




/*
const cv::Point &Entity::getPredictedNextPosition() const
{
    return (_predictedNextPosition);
}

void Entity::setStillBeingTracked(bool val)
{
    _stillBeingTracked = val;
}

void Entity::setNumOfConsecutiveFramesWithoutAMatch(int val)
{
    _numOfConsecutiveFramesWithoutMatch = val;
}

bool Entity::getStillBeingTracked() const
{
    return (_stillBeingTracked);
}

bool Entity::getCurrentMatchFoundOrNewEntity() const
{
    return (_currentMatchFoundOrNewEntity);
}

int Entity::getNumOfConsecutiveFramesWithoutMatch() const
{
    return (_numOfConsecutiveFramesWithoutMatch);
}


void Entity::setCurrentBoundingRect(const cv::Rect &rect)
{
    _currentBoundingRect = rect;
}

void Entity::setContour(const std::vector<cv::Point> &contour)
{
    _contour = contour;
}

void Entity::addCenterPosition(const cv::Point &centerPosition)
{
    _centerPositions.push_back(centerPosition);
}

void Entity::setCurrentAspectRatio(double val)
{
    _currentAspectRatio = val;
}

void Entity::setCurrentDiagonalSize(double val)
{
    _currentDiagonalSize = val;
}
 */
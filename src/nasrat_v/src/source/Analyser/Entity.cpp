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
    _predictedNextPosition = { 0 };
    _nbEntity = DEFAULT_NB_ENTITY;
    _matchFoundOrNewEntity = true;
    _numOfConsecutiveFramesWithoutMatch = 0;
    _stillBeingTracked = true;
}

Entity::~Entity() = default;

void Entity::initCurrentAttributes()
{
    _boundingRect = cv::boundingRect(_contour);
    _diagonalSize = sqrt(pow(_boundingRect.width, 2) + pow(_boundingRect.height, 2));
    _aspectRatio = ((float)_boundingRect.width / (float)_boundingRect.height);
}

void Entity::initCenterPosition()
{
    cv::Point currentCenter;

    currentCenter.x = ((_boundingRect.x + _boundingRect.x + _boundingRect.width) / 2);
    currentCenter.y = ((_boundingRect.y + _boundingRect.y + _boundingRect.height) / 2);
    _centerPositions.push_back(currentCenter);
}

void Entity::clone(const Entity &entity)
{
    _aspectRatio = entity._aspectRatio;
    _diagonalSize = entity._diagonalSize;
    _boundingRect = entity._boundingRect;
    _predictedNextPosition = entity._predictedNextPosition;
    _centerPositions = std::vector<cv::Point>(entity._centerPositions);
    _contour = std::vector<cv::Point>(entity._contour);
    _movementType = entity._movementType;
    _temperatureType = entity._temperatureType;
    _nbEntity = entity._nbEntity;
    _matchFoundOrNewEntity = entity._matchFoundOrNewEntity;
    _numOfConsecutiveFramesWithoutMatch = entity._numOfConsecutiveFramesWithoutMatch;
    _stillBeingTracked = entity._stillBeingTracked;
}

bool Entity::isSame(const Entity &entity) const
{
    return (_aspectRatio == entity._aspectRatio &&
            _diagonalSize == entity._diagonalSize &&
            _boundingRect == entity._boundingRect &&
            _predictedNextPosition == entity._predictedNextPosition &&
            _centerPositions.back() == entity._centerPositions.back() &&
            _contour.back() == entity._contour.back() &&
            _movementType == entity._movementType &&
            _temperatureType == entity._temperatureType);
}

double Entity::getAspectRatio() const
{
    return (_aspectRatio);
}

double Entity::getDiagonalSize() const
{
    return (_diagonalSize);
}

const cv::Rect &Entity::getBoundingRect() const
{
    return (_boundingRect);
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

int Entity::getNbEntity() const
{
    return (_nbEntity);
}

bool Entity::getMatchFoundOrNewEntity() const
{
    return (_matchFoundOrNewEntity);
}

int Entity::getNumOfConsecutiveFramesWithoutMatch() const
{
    return (_numOfConsecutiveFramesWithoutMatch);
}

bool Entity::isStillBeingTracked() const
{
    return (_stillBeingTracked);
}

void Entity::setAspectRatio(double val)
{
    _aspectRatio = val;
}

void Entity::setDiagonalSize(double val)
{
    _diagonalSize = val;
}

void Entity::setBoundingRect(const cv::Rect &rect)
{
    _boundingRect = rect;
}

void Entity::setContour(const std::vector<cv::Point> &contour)
{
    _contour = contour;
}

void Entity::setMovementType(const Entity::entityMovement &type)
{
    _movementType = type;
}

void Entity::setTemperatureType(const Entity::entityTemperature &type)
{
    _temperatureType = type;
}

void Entity::setNbEntity(int nb)
{
    _nbEntity = nb;
}

void Entity::setMatchFoundOrNewEntity(bool match)
{
    _matchFoundOrNewEntity = match;
}

void Entity::setNumOfConsecutiveFramesWithoutAMatch(int val)
{
    _numOfConsecutiveFramesWithoutMatch = val;
}

void Entity::setStillBeingTracked(bool tracked)
{
    _stillBeingTracked = tracked;
}

void Entity::predictNextPosition()
{
    short deltaX;
    short deltaY;
    t_sumOfChanges sumOfChanges;
    auto numPositions = (short)_centerPositions.size();
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

void Entity::addCenterPosition(const cv::Point &centerPosition)
{
    _centerPositions.push_back(centerPosition);
}*/
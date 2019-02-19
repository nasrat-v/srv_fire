//
// Created by nasrat_v on 11/3/18.
//

#include "../header/FrameAnalyser.h"

FrameAnalyser::FrameAnalyser(const DebugManager::debugMode &mode, const std::string &videoPath) :    _debugMode(mode),
                                                                                                     _imageService(mode, videoPath)
{
    _firstFrame = false;
    _isInit = false;
}

FrameAnalyser::~FrameAnalyser() = default;

Error::ErrorType FrameAnalyser::initAnalyser()
{
    if (_imageService.openVideo() == ImageProvider::statusVideo::ERROR)
        return (Error::ErrorType::OPEN_VID);
    _isInit = true;
    return (Error::ErrorType::NO_ERROR);
}

Error::ErrorType FrameAnalyser::analyseFrame()
{
    bool end = false;

    if (!_isInit)
    {
        Error::logError(Error::ErrorType::MISSING_INIT);
        return (Error::ErrorType::MISSING_INIT);
    }
    if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
        end = true;
    while (!end)
    {
        findEntities();
        /*if (_firstFrame)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();*/
        _imageService.displayImg(_frame.getImages().front(), /*_savedEntities,*/ _frame.getEntities());
        _frame.clearEntities();
        if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
            end = true;
        cv::waitKey(1);
    }
    return (Error::ErrorType::NO_ERROR);
}

void FrameAnalyser::findEntities()
{
    _imageService.substractInfosAllEntities(_frame);
    findAllEntitiesWithInfos();
    //_imageService.substractInfosEntitiesInMovement(_frame);
    //findEntitiesInMovementWithInfos();
}

void FrameAnalyser::findAllEntitiesWithInfos()
{
    for (auto &convexHull : _frame.getConvexHullsWarm())
    {
        Entity possibleEntity(convexHull);

        if (isPossibleEntity(possibleEntity))
        {
            possibleEntity.setTemperatureType(Entity::entityTemperature::WARM);
            _frame.addEntity(possibleEntity);
        }
    }
    for (auto &convexHull : _frame.getConvexHullsHot())
    {
        Entity possibleEntity(convexHull);

        if (isPossibleEntity(possibleEntity))
        {
            possibleEntity.setTemperatureType(Entity::entityTemperature::HOT);
            _frame.addEntity(possibleEntity);
        }
    }
    for (auto &convexHull : _frame.getConvexHullsVeryHot())
    {
        Entity possibleEntity(convexHull);

        if (isPossibleEntity(possibleEntity))
        {
            possibleEntity.setTemperatureType(Entity::entityTemperature::VERY_HOT);
            _frame.addEntity(possibleEntity);
        }
    }
}

void FrameAnalyser::findEntitiesInMovementWithInfos()
{
    size_t index = 0;
    t_distance distance;

    for (auto &entity : _frame.getEntities())
    {
        findClosestMovementEntity(entity, &distance);
        if (distance.leastDistance < entity.getCurrentDiagonalSize() * 1.15)
            _frame.setMovementTypeEntity(index, Entity::entityMovement::MOVE);
        else
            _frame.setMovementTypeEntity(index, Entity::entityMovement::STATIC);
        index++;
    }
}

void FrameAnalyser::findClosestMovementEntity(const Entity &entity, t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexEntity = 0;
    distance->leastDistance = 100000.0;

    for (auto &convexHull : _frame.getConvexHullsMovement())
    {
        Entity possibleEntity(convexHull);

        if (isPossibleEntity(possibleEntity))
        {
            dist = distanceBetweenPoints(entity.getCenterPositions().back(), possibleEntity.getCenterPositions().back());
            if (dist < distance->leastDistance)
            {
                distance->leastDistance = dist;
                distance->indexEntity = i;
            }
            i++;
        }
    }
}

double FrameAnalyser::distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint)
{
    int intX = abs(firstPoint.x - secondPoint.x);
    int intY = abs(firstPoint.y - secondPoint.y);
    
    return (sqrt(pow(intX, 2) + pow(intY, 2)));
}

bool FrameAnalyser::isPossibleEntity(const Entity &possibleEntity)
{
    return (possibleEntity.getCurrentBoundingRect().area() > 150 && possibleEntity.getCurrentAspectRatio() >= 0.2 &&
            possibleEntity.getCurrentAspectRatio() <= 1.25 && possibleEntity.getCurrentBoundingRect().width > 30 &&
            possibleEntity.getCurrentBoundingRect().height > 30 && possibleEntity.getCurrentDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleEntity.getContour()) / (double)possibleEntity.getCurrentBoundingRect().area()) > 0.40);
}












/*void FrameAnalyser::initSavedEntities()
{
    for (auto &frameEntity : _frame.getEntities())
        _savedEntities.push_back(frameEntity);
    _firstFrame = false;
}

void FrameAnalyser::matchFrameEntitiesToSavedEntities()
{
    int index;
    t_distance  distance;

    predictNextPositionSavedEntities();
    for (auto &frameEntity : _frame.getEntities())
    {
        index = 0;
        findClosestFrameEntityForSavedEntity(frameEntity, &distance);
        if (distance.leastDistance < frameEntity.getCurrentDiagonalSize() * 1.15)
            setSavedEntityFromFrameEntity(frameEntity, distance.indexEntity);
        else
            addNewSavedEntity(frameEntity, index);
        index++;
    }
    checkConsecutiveFrameWithoutMatchSavedEntities();
}

void FrameAnalyser::predictNextPositionSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
    {
        savedEntity.setCurrentMatchFoundOrNewEntity(false);
        savedEntity.predictNextPosition();
    }
}

void FrameAnalyser::checkConsecutiveFrameWithoutMatchSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
    {
        if (!savedEntity.getCurrentMatchFoundOrNewEntity())
            savedEntity.setNumOfConsecutiveFramesWithoutAMatch(savedEntity.getNumOfConsecutiveFramesWithoutMatch() + 1);
        if (savedEntity.getNumOfConsecutiveFramesWithoutMatch() >= NB_FRAME_MOVE_PREDICTION)
            savedEntity.setStillBeingTracked(false);
    }
}

void FrameAnalyser::setSavedEntityFromFrameEntity(const Entity &frameEntity, size_t index)
{
    _savedEntities[index].setContour(frameEntity.getContour());
    _savedEntities[index].setCurrentBoundingRect(frameEntity.getCurrentBoundingRect());
    _savedEntities[index].addCenterPosition(frameEntity.getCenterPositions().back());
    _savedEntities[index].setCurrentDiagonalSize(frameEntity.getCurrentDiagonalSize());
    _savedEntities[index].setCurrentAspectRatio(frameEntity.getCurrentAspectRatio());
    _savedEntities[index].setCurrentMatchFoundOrNewEntity(true);
    _savedEntities[index].setType(frameEntity.getType());
    //debugPredictedPosition(frameEntity, _savedEntities[index]);
}

void FrameAnalyser::addNewSavedEntity(const Entity &frameEntity, int index)
{
    _frame.setCurrentMatchFoundOrNewEntity(index, true);
    _savedEntities.push_back(frameEntity);
}

void FrameAnalyser::debugPredictedPosition(const Entity &frameEntity)
{
    if (_debugMode & DebugManager::debugMode::OUTPUT_PREDICTION)
    {
        Log::logSomething("predicted X :\t" + std::to_string(frameEntity.getPredictedNextPosition().x));
        Log::logSomething("predicted Y :\t" + std::to_string(frameEntity.getPredictedNextPosition().y));
        Log::logSomething("real X :\t" + std::to_string(frameEntity.getCenterPositions().back().x));
        Log::logSomething("real Y :\t" + std::to_string(frameEntity.getCenterPositions().back().y));
        std::cout << std::endl;
    }
}*/

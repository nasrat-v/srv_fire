//
// Created by nasrat_v on 11/3/18.
//

#include "../header/FrameAnalyser.h"

FrameAnalyser::FrameAnalyser(const Log::debugMode &mode, const std::string &videoPath) :    _debugMode(mode),
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

void FrameAnalyser::initSavedEntities()
{
    for (auto &frameEntity : _frame.getEntities())
        _savedEntities.push_back(frameEntity);
    _firstFrame = false;
}

Error::ErrorType FrameAnalyser::analyseFrame()
{
    bool end = false;
    Error::ErrorType error;

    if (!_isInit)
    {
        Error::logError(Error::ErrorType::MISSING_INIT);
        return (Error::ErrorType::MISSING_INIT);
    }
    if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
        end = true;
    while (!end)
    {
        if ((error = findEntities()) != Error::ErrorType::NO_ERROR)
            return (error);
        /*if (_firstFrame)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();*/
        _imageService.displayImg(_frame.getImages().back(), /*_savedEntities,*/ _frame.getEntities());
        _frame.clearEntities();
        if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
            end = true;
        cv::waitKey(1);
    }
    return (Error::ErrorType::NO_ERROR);
}

Error::ErrorType FrameAnalyser::findEntities()
{
    Error::ErrorType error;

    /*_imageService.substractInfos(_frame, Entity::entityType::FIRE);
    if ((error = _frame.findEntitiesWithInfos(Entity::entityType::FIRE)) != Error::ErrorType::NO_ERROR)
        return (error);*/
    _imageService.substractInfos(_frame, Entity::entityType::HUMAN);
    if ((error = _frame.findEntitiesWithInfos(Entity::entityType::HUMAN)) != Error::ErrorType::NO_ERROR)
        return (error);
    return (Error::ErrorType::NO_ERROR);
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

void FrameAnalyser::findClosestFrameEntityForSavedEntity(const Entity &frameEntity, t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexEntity = 0;
    distance->leastDistance = 100000.0;

    for (auto &savedEntity : _savedEntities)
    {
        if (savedEntity.getStillBeingTracked() && (savedEntity.getType() == frameEntity.getType()))
        {
            dist = distanceBetweenPoints(frameEntity.getCenterPositions().back(), savedEntity.getPredictedNextPosition());
            if (dist < distance->leastDistance)
            {
                distance->leastDistance = dist;
                distance->indexEntity = i;
            }
        }
        i++;
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
    debugPredictedPosition(frameEntity, _savedEntities[index]);
}

void FrameAnalyser::addNewSavedEntity(const Entity &frameEntity, int index)
{
    _frame.setCurrentMatchFoundOrNewEntity(index, true);
    _savedEntities.push_back(frameEntity);
}

double FrameAnalyser::distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint)
{
    int intX = abs(firstPoint.x - secondPoint.x);
    int intY = abs(firstPoint.y - secondPoint.y);
    return (sqrt(pow(intX, 2) + pow(intY, 2)));
}

void FrameAnalyser::debugPredictedPosition(const Entity &frameEntity, const Entity &savedEntity)
{
    if (_debugMode & Log::debugMode::OUTPUT_PREDICTION)
    {
        Log::logSomething("predicted X :\t" + std::to_string(savedEntity.getPredictedNextPosition().x));
        Log::logSomething("predicted Y :\t" + std::to_string(savedEntity.getPredictedNextPosition().y));
        Log::logSomething("real X :\t" + std::to_string(frameEntity.getCenterPositions().back().x));
        Log::logSomething("real Y :\t" + std::to_string(frameEntity.getCenterPositions().back().y));
        std::cout << std::endl;
    }
}

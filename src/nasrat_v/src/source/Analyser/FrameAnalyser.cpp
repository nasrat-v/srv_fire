//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/FrameAnalyser.hh"

FrameAnalyser::FrameAnalyser(const DebugManager::debugMode &mode, ImageProvider *imageProvider) :    _debugMode(mode),
                                                                                                     _imageService(mode, imageProvider)
{
    _firstFrame = true;
    _isInit = false;
}

FrameAnalyser::~FrameAnalyser() = default;

Error::ErrorType FrameAnalyser::initAnalyser(bool openVideo)
{
    if (_debugMode & DebugManager::debugMode::CREATE_SAMPLE_IMG)
    {
        _imageService.createSampleImgFromVideo();
        return (Error::ErrorType::DEBUG_STOP);
    }
    if (openVideo)
    {
        if (_imageService.openVideo() == ImageProvider::statusVideo::ERROR)
            return (Error::ErrorType::OPEN_VID);
    }
    _isInit = true;
    return (Error::ErrorType::NO_ERROR);
}

Error::ErrorType FrameAnalyser::analyseFrame()
{
    bool end = false;
    ImageProvider::statusVideo status;

    if (!_isInit)
    {
        Error::logError(Error::ErrorType::MISSING_INIT);
        return (Error::ErrorType::MISSING_INIT);
    }
    if ((status = _imageService.getNextImg(_frame)) == ImageProvider::statusVideo::END)
        end = true;
    else if (status == ImageProvider::statusVideo::ERROR)
        return (Error::ErrorType::OPEN_VID);
    while (!end)
    {
        findEntities();
        if (_firstFrame)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();
        _imageService.displayImg(_frame.getImages().front(), _savedEntities, _frame.getEntities());
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

void FrameAnalyser::findClosestSavedEntity(const Entity &entity, t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexSavedEntity = 0;
    distance->leastDistance = 100000.0;

    for (auto &savedEntity : _savedEntities)
    {
        dist = distanceBetweenPoints(entity.getCenterPositions().back(), savedEntity.getCenterPositions().back());
        if (dist < distance->leastDistance)
        {
            distance->leastDistance = dist;
            distance->indexSavedEntity = i;
        }
        i++;
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
    return (possibleEntity.getBoundingRect().area() > 150 && possibleEntity.getAspectRatio() >= 0.2 &&
            possibleEntity.getAspectRatio() <= 1.25 && possibleEntity.getBoundingRect().width > 30 &&
            possibleEntity.getBoundingRect().height > 30 && possibleEntity.getDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleEntity.getContour()) / (double)possibleEntity.getBoundingRect().area()) > 0.40);
}

void FrameAnalyser::initSavedEntities()
{
    int index = 0;

    for (auto &frameEntity : _frame.getEntities())
    {
        Entity savedEntity(frameEntity.getContour());

        savedEntity.clone(frameEntity);
        savedEntity.setNbEntity(index);
        _savedEntities.push_back(savedEntity);
        _firstFrame = false;
        index++;
    }
}

void FrameAnalyser::matchFrameEntitiesToSavedEntities()
{
    t_distance  distance;

    //predictNextPositionSavedEntities();
    for (auto &frameEntity : _frame.getEntities())
    {
        findClosestSavedEntity(frameEntity, &distance);
        if (distance.leastDistance < (frameEntity.getDiagonalSize() * 1.15))
            setNewValueSavedEntity(frameEntity, distance.indexSavedEntity);
        else
            addNewSavedEntity(frameEntity);
    }
    checkConsecutiveFrameWithoutMatchSavedEntities();
}

void FrameAnalyser::setNewValueSavedEntity(const Entity &frameEntity, size_t index)
{
    _savedEntities[index].clone(frameEntity);
    _savedEntities[index].setMatchFoundOrNewEntity(true);
}

void FrameAnalyser::addNewSavedEntity(const Entity &frameEntity)
{
    Entity savedEntity(frameEntity.getContour());

    savedEntity.clone(frameEntity);
    savedEntity.setMatchFoundOrNewEntity(true);
    _savedEntities.push_back(savedEntity);
}

void FrameAnalyser::checkConsecutiveFrameWithoutMatchSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
    {
        if (!savedEntity.getMatchFoundOrNewEntity())
            savedEntity.setNumOfConsecutiveFramesWithoutAMatch(savedEntity.getNumOfConsecutiveFramesWithoutMatch() + 1);
        if (savedEntity.getNumOfConsecutiveFramesWithoutMatch() >= MAX_FRAME_WITHOUT_MATCH)
            savedEntity.setStillBeingTracked(false);
        savedEntity.setMatchFoundOrNewEntity(false);
    }
    _savedEntities.erase(std::remove_if(_savedEntities.begin(), _savedEntities.end(),
                    [](const Entity &entity) { return (!entity.isStillBeingTracked()); }), _savedEntities.end());
}


/*void FrameAnalyser::predictNextPositionSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
        savedEntity.predictNextPosition();
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
}

void FrameAnalyser::findEntitiesInMovementWithInfos()
{
   size_t index = 0;
   t_distance distance;

   for (auto &entity : _frame.getEntities())
   {
       findClosestSavedEntity(entity, &distance);
       if (distance.leastDistance < entity.getCurrentDiagonalSize() * 1.15)
           _frame.setMovementTypeEntity(index, Entity::entityMovement::MOVE);
       else
           _frame.setMovementTypeEntity(index, Entity::entityMovement::STATIC);
       index++;
   }
}*/
//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/FrameAnalyser.hh"

FrameAnalyser::FrameAnalyser(const DebugManager::debugMode &mode,
                            std::shared_ptr<ImageProvider> imageProvider) : _debugMode(mode),
                                                                            _imageService(mode, std::move(imageProvider))
{
    _firstFrameBlob = true;
    _firstFrameEntity = true;
    _isInit = false;
}

FrameAnalyser::~FrameAnalyser() = default;

Error::ErrorType FrameAnalyser::initAnalyser(bool openVideo)
{
    ImageProvider::statusVideo status;

    if (_debugMode & DebugManager::debugMode::CREATE_SAMPLE_IMG)
    {
        if ((status = _imageService.createSampleImgFromVideo()) != ImageProvider::statusVideo::OPEN)
            return (Error::ErrorType::OPEN_VID);
        return (Error::ErrorType::DEBUG_STOP);
    }
    if (openVideo)
    {
        if (_imageService.openVideo() == ImageProvider::statusVideo::ERROR)
            return (Error::ErrorType::OPEN_VID);
    }
    _isInit = true;
    return (Error::ErrorType::NOPE);
}

Error::ErrorType FrameAnalyser::checkInitialisation(bool &end)
{
    ImageProvider::statusVideo  status;

    if (!_isInit)
    {
        Error::logError(Error::ErrorType::MISSING_INIT);
        return (Error::ErrorType::MISSING_INIT);
    }
    if ((status = _imageService.getNextImg(_frame)) == ImageProvider::statusVideo::END)
        end = true;
    else if (status == ImageProvider::statusVideo::ERROR)
        return (Error::ErrorType::OPEN_VID);
    return (Error::ErrorType::NOPE);
}

Error::ErrorType FrameAnalyser::analyseFrame()
{
    bool                end = false;
    Error::ErrorType    status;

    if ((status = checkInitialisation(end)) != Error::ErrorType::NOPE)
        return (status);
    while (!end)
    {
        logicForEachFrame(end);
        cv::waitKey(1);
    }
    Log::logSomething("Analyser process terminated");
    return (Error::ErrorType::NOPE);
}

void FrameAnalyser::logicForEachFrame(bool &end)
{
    findBlobs();
    findEntities();
    if (_debugMode & DebugManager::HOT_SPOT)
        matchSavedBlobsToSavedEntities();
    _imageService.displayImg(_frame.getImages().front(), _savedBlobs, _frame.getBlobs(),
                             _savedEntities, _frame.getEntities(), colorToAnalyse);
    _frame.clearAllBlobs();
    if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
        end = true;
}

void FrameAnalyser::findBlobs()
{
    _imageService.substractInfosPossibleBlobs(_frame, colorToAnalyse);
    findAllBlobsWithInfos();
    if (_firstFrameBlob)
        initSavedBlobs();
    else
        matchFrameBlobsToSavedBlobs();
}

void FrameAnalyser::findEntities()
{
    std::vector<std::vector<cv::Point>> allContours;

    findContoursAllBlobs(allContours);
    if (!allContours.empty())
    {
        _imageService.substractInfosPossibleEntities(_frame, allContours);
        findAllEntitiesWithInfos();
        if (_firstFrameEntity)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();
    }
}

void FrameAnalyser::findAllBlobsWithInfos()
{
    std::vector<Blob> blobsFiltered;

    for (auto &colorRange : colorToAnalyse)
        _blobFilter.filtratePossibleBlobs(colorRange, _frame.getFormBlobs(colorRange), blobsFiltered);
    _frame.setBlobs(blobsFiltered);
}

void FrameAnalyser::findAllEntitiesWithInfos()
{
    std::vector<Entity> entitiesFiltered;

    _entityFilter.filtratePossibleEntities(_frame.getFormEntities(), entitiesFiltered);
    _frame.setEntities(entitiesFiltered);
}


void FrameAnalyser::findContoursAllBlobs(std::vector<std::vector<cv::Point>> &allContours)
{
    for (auto &blob : _frame.getBlobs())
        allContours.push_back(blob.getContour());
}

void FrameAnalyser::findClosestSavedBlob(const Blob &blob, FrameAnalyser::t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexSavedBlob = INDEX_SAVED_BLOB_NOT_FOUND;
    distance->leastDistance = 100000.0;

    for (auto &savedBlob : _savedBlobs)
    {
        if (savedBlob.getColorRange()._nameRange == blob.getColorRange()._nameRange)
        {
            dist = distanceBetweenPoints(blob.getCenterPositions().back(), savedBlob.getCenterPositions().back());
            if (dist < distance->leastDistance)
            {
                distance->leastDistance = dist;
                distance->indexSavedBlob = i;
            }
        }
        i++;
    }
}

void FrameAnalyser::findClosestSavedEntity(const Blob &blob, FrameAnalyser::t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexSavedBlob = INDEX_SAVED_BLOB_NOT_FOUND;
    distance->leastDistance = 100000.0;

    for (auto &savedEntity : _savedEntities)
    {
        dist = distanceBetweenPoints(blob.getCenterPositions().back(), savedEntity.getCenterPositions().back());
        if (dist < distance->leastDistance)
        {
            distance->leastDistance = dist;
            distance->indexSavedBlob = i;
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

void FrameAnalyser::initSavedBlobs()
{
    int index = 0;

    for (auto &frameBlob : _frame.getBlobs())
    {
        Blob savedBlob(frameBlob.getContour());

        savedBlob.clone(frameBlob);
        savedBlob.setId(index);
        _savedBlobs.push_back(savedBlob);
        _firstFrameBlob = false;
        index++;
    }
}

void FrameAnalyser::initSavedEntities()
{
    int index = 0;

    for (auto &frameEntity : _frame.getEntities())
    {
        Entity savedEntity(frameEntity.getContour());

        savedEntity.clone(frameEntity);
        savedEntity.setId(IdManager::newId());
        _savedEntities.push_back(savedEntity);
        _firstFrameEntity = false;
        index++;
    }
}

void FrameAnalyser::matchFrameBlobsToSavedBlobs()
{
    FrameAnalyser::t_distance distance;

    //predictNextPositionSavedBlobs();
    for (auto &frameBlob : _frame.getBlobs())
    {
        findClosestSavedBlob(frameBlob, &distance);
        if ((distance.leastDistance < (frameBlob.getDiagonalSize() * 1.15)) &&
             distance.indexSavedBlob != INDEX_SAVED_BLOB_NOT_FOUND)
            mergeSavedBlobAndFrameBlob(frameBlob, distance.indexSavedBlob);
        else
            addNewSavedBlob(frameBlob);
    }
    checkConsecutiveFrameWithoutMatchSavedBlobs();
}

void FrameAnalyser::matchFrameEntitiesToSavedEntities()
{
    FrameAnalyser::t_distance distance;

    //predictNextPositionSavedEntities();
    for (auto &frameEntity : _frame.getEntities())
    {
        findClosestSavedEntity(frameEntity, &distance);
        if ((distance.leastDistance < (frameEntity.getDiagonalSize() * 1.15)) &&
             distance.indexSavedBlob != INDEX_SAVED_BLOB_NOT_FOUND)
            mergeSavedEntityAndFrameEntity(frameEntity, distance.indexSavedBlob);
        else
            addNewSavedEntity(frameEntity);
    }
    checkConsecutiveFrameWithoutMatchSavedEntities();
}

void FrameAnalyser::matchSavedBlobsToSavedEntities()
{
    FrameAnalyser::t_distance distance;

    for (auto &blob : _savedBlobs)
    {
        findClosestSavedEntity(blob, &distance);
        if (distance.indexSavedBlob != INDEX_SAVED_BLOB_NOT_FOUND)
            _savedEntities[distance.indexSavedBlob].addBlob(blob);
    }
}

void FrameAnalyser::mergeSavedBlobAndFrameBlob(const Blob &frameBlob, size_t index)
{
    _savedBlobs[index].clone(frameBlob);
    //_savedBlobs[index].clone(mergeBlobs(_savedBlobs[index], frameBlob));
    //
    // il faut trouver une solution pour merger les deux blobs ensemble
    // dilatation ? créer des lignes pour les relier puis trouver les contours ??
    // car en clonant seulement une des deux entités disparait (aspiré par l'autre) si elles ne sont pas exactement les memes
    //
    _savedBlobs[index].setMatchFoundOrNewBlob(true);
}

void FrameAnalyser::mergeSavedEntityAndFrameEntity(const Entity &frameEntity, size_t index)
{
    int id = _savedEntities[index].getId();

    _savedBlobs[index].clone(frameEntity);
    //_savedEntities[index].clone(mergeBlobs(_savedEntities[index], frameEntity));
    _savedEntities[index].setMatchFoundOrNewBlob(true);
    _savedEntities[index].setId(id);
}

Blob FrameAnalyser::mergeBlobs(const Blob &savedBlob, const Blob &frameBlob)
{
    return (Blob(_imageService.mergeContour(
            _frame.getImages().front().size(), savedBlob.getContour(), frameBlob.getContour())));
}

void FrameAnalyser::addNewSavedBlob(const Blob &frameBlob)
{
    Blob savedBlob(frameBlob.getContour());

    savedBlob.clone(frameBlob);
    savedBlob.setMatchFoundOrNewBlob(true);
    _savedBlobs.push_back(savedBlob);
}

void FrameAnalyser::addNewSavedEntity(const Entity &frameEntity)
{
    Entity savedEntity(frameEntity.getContour());

    savedEntity.clone(frameEntity);
    savedEntity.setMatchFoundOrNewBlob(true);
    savedEntity.setId(IdManager::newId());
    _savedEntities.push_back(savedEntity);
}

void FrameAnalyser::checkConsecutiveFrameWithoutMatchSavedBlobs()
{
    for (auto &savedBlob : _savedBlobs)
    {
        if (!savedBlob.getMatchFoundOrNewBlob())
            savedBlob.setNumOfConsecutiveFramesWithoutAMatch(savedBlob.getNumOfConsecutiveFramesWithoutMatch() + 1);
        if (savedBlob.getNumOfConsecutiveFramesWithoutMatch() >= MAX_FRAME_WITHOUT_MATCH_BLOB)
            savedBlob.setStillBeingTracked(false);
        savedBlob.setMatchFoundOrNewBlob(false);
    }
    _savedBlobs.erase(std::remove_if(_savedBlobs.begin(), _savedBlobs.end(),
                    [](const Blob &blob) { return (!blob.isStillBeingTracked()); }),
                            _savedBlobs.end());
}

void FrameAnalyser::checkConsecutiveFrameWithoutMatchSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
    {
        if (!savedEntity.getMatchFoundOrNewBlob())
            savedEntity.setNumOfConsecutiveFramesWithoutAMatch(savedEntity.getNumOfConsecutiveFramesWithoutMatch() + 1);
        if (savedEntity.getNumOfConsecutiveFramesWithoutMatch() >= MAX_FRAME_WITHOUT_MATCH_ENTITY)
            savedEntity.setStillBeingTracked(false);
        savedEntity.setMatchFoundOrNewBlob(false);
    }
    _savedEntities.erase(std::remove_if(_savedEntities.begin(), _savedEntities.end(),
                                     [](const Entity &entity) { return (!entity.isStillBeingTracked()); }),
                                             _savedEntities.end());
}


/*void FrameAnalyser::predictNextPositionSavedBlobs()
{
    for (auto &savedBlob : _savedBlobs)
        savedBlob.predictNextPosition();
}

void FrameAnalyser::debugPredictedPosition(const Blob &frameBlob)
{
    if (_debugMode & DebugManager::debugMode::OUTPUT_PREDICTION)
    {
        Log::logSomething("predicted X :\t" + std::to_string(frameBlob.getPredictedNextPosition().x));
        Log::logSomething("predicted Y :\t" + std::to_string(frameBlob.getPredictedNextPosition().y));
        Log::logSomething("real X :\t" + std::to_string(frameBlob.getCenterPositions().back().x));
        Log::logSomething("real Y :\t" + std::to_string(frameBlob.getCenterPositions().back().y));
        std::cout << std::endl;
    }
}

void FrameAnalyser::findBlobsInMovementWithInfos()
{
   size_t index = 0;
   t_distance distance;

   for (auto &blob : _frame.getBlobs())
   {
       findClosestSavedBlob(blob, &distance);
       if (distance.leastDistance < blob.getCurrentDiagonalSize() * 1.15)
           _frame.setMovementTypeBlob(index, Blob::blobMovement::MOVE);
       else
           _frame.setMovementTypeBlob(index, Blob::blobMovement::STATIC);
       index++;
   }
}*/

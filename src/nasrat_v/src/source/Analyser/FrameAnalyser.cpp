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
        findBlobs();
        if (_firstFrame)
            initSavedBlobs();
        else
            matchFrameBlobsToSavedBlobs();
        _imageService.displayImg(_frame.getImages().front(), _savedBlobs, _frame.getBlobs());
        _frame.clearAllBlobs();
        if (_imageService.getNextImg(_frame) == ImageProvider::statusVideo::END)
            end = true;
        cv::waitKey(1);
    }
    return (Error::ErrorType::NO_ERROR);
}

void FrameAnalyser::findBlobs()
{
    _imageService.substractInfosPossibleBlobs(_frame, colorToAnalyse);
    findAllBlobsWithInfos();
}

void FrameAnalyser::findAllBlobsWithInfos()
{
    for (auto &colorRange : colorToAnalyse)
    {
        for (auto &formBlob : _frame.getFormBlobs(colorRange))
        {
            Blob possibleBlob(formBlob._contour);

            if (isPossibleBlob(possibleBlob))
            {
                possibleBlob.setColorRange(colorRange);
                _frame.addBlob(possibleBlob);
            }
        }
    }
}

void FrameAnalyser::findClosestSavedBlob(const Blob &blob, t_distance *distance)
{
    size_t i = 0;
    double dist = 0;
    distance->indexSavedBlob = 0;
    distance->leastDistance = 100000.0;

    for (auto &savedBlob : _savedBlobs)
    {
        dist = distanceBetweenPoints(blob.getCenterPositions().back(), savedBlob.getCenterPositions().back());
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

bool FrameAnalyser::isPossibleBlob(const Blob &possibleBlob)
{
    return (possibleBlob.getBoundingRect().area() > 150 && possibleBlob.getAspectRatio() >= 0.2 &&
            possibleBlob.getAspectRatio() <= 1.25 && possibleBlob.getBoundingRect().width > 30 &&
            possibleBlob.getBoundingRect().height > 30 && possibleBlob.getDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleBlob.getContour()) / (double)possibleBlob.getBoundingRect().area()) > 0.40);
}

void FrameAnalyser::initSavedBlobs()
{
    int index = 0;

    for (auto &frameBlob : _frame.getBlobs())
    {
        Blob savedBlob(frameBlob.getContour());

        savedBlob.clone(frameBlob);
        savedBlob.setNbBlob(index);
        _savedBlobs.push_back(savedBlob);
        _firstFrame = false;
        index++;
    }
}

void FrameAnalyser::matchFrameBlobsToSavedBlobs()
{
    t_distance  distance;

    //predictNextPositionSavedBlobs();
    for (auto &frameBlob : _frame.getBlobs())
    {
        findClosestSavedBlob(frameBlob, &distance);
        if (distance.leastDistance < (frameBlob.getDiagonalSize() * 1.15))
            setNewValueSavedBlob(frameBlob, distance.indexSavedBlob);
        else
            addNewSavedBlob(frameBlob);
    }
    checkConsecutiveFrameWithoutMatchSavedBlobs();
}

void FrameAnalyser::setNewValueSavedBlob(const Blob &frameBlob, size_t index)
{
    _savedBlobs[index].clone(frameBlob);
    _savedBlobs[index].setMatchFoundOrNewBlob(true);
}

void FrameAnalyser::addNewSavedBlob(const Blob &frameBlob)
{
    Blob savedBlob(frameBlob.getContour());

    savedBlob.clone(frameBlob);
    savedBlob.setMatchFoundOrNewBlob(true);
    _savedBlobs.push_back(savedBlob);
}

void FrameAnalyser::checkConsecutiveFrameWithoutMatchSavedBlobs()
{
    for (auto &savedBlob : _savedBlobs)
    {
        if (!savedBlob.getMatchFoundOrNewBlob())
            savedBlob.setNumOfConsecutiveFramesWithoutAMatch(savedBlob.getNumOfConsecutiveFramesWithoutMatch() + 1);
        if (savedBlob.getNumOfConsecutiveFramesWithoutMatch() >= MAX_FRAME_WITHOUT_MATCH)
            savedBlob.setStillBeingTracked(false);
        savedBlob.setMatchFoundOrNewBlob(false);
    }
    _savedBlobs.erase(std::remove_if(_savedBlobs.begin(), _savedBlobs.end(),
                    [](const Blob &blob) { return (!blob.isStillBeingTracked()); }), _savedBlobs.end());
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
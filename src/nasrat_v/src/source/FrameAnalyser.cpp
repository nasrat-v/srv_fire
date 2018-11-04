//
// Created by nasrat_v on 11/3/18.
//

#include "../header/FrameAnalyser.h"

FrameAnalyser::FrameAnalyser()
{
    _frameCnt = 2;
    _firstFrame = false;
}

FrameAnalyser::~FrameAnalyser()
{
}

void FrameAnalyser::initAnalyser(const std::string &videoPath, Log::debugMode mode)
{
    _debugMode = mode;
    openVideo(videoPath);
    readFrame();
}

void FrameAnalyser::initSavedEntities()
{
    for (auto &frameEntity : _frame.getEntities())
        _savedEntities.push_back(frameEntity);
    _firstFrame = false;
}

void FrameAnalyser::openVideo(const std::string &videoPath)
{
    _capVideo.open(videoPath);
    if (!_capVideo.isOpened())
        Error::logErrorAbort(Error::ErrorType::OPEN_VID, videoPath);
    else if (_capVideo.get(CV_CAP_PROP_FRAME_COUNT) < MIN_FRAME_VID)
        Error::logErrorAbort(Error::ErrorType::TRUNCATED_VID, videoPath);
}


void FrameAnalyser::readFrame()
{
    cv::Mat first_img;
    cv::Mat second_img;

    _capVideo.read(first_img);
    _capVideo.read(second_img);
    _frame.setFirstImg(first_img);
    _frame.setSecondImg(second_img);
    Log::logSomething("Start of video");
}

int FrameAnalyser::analyseFrame()
{
    cv::Mat second_img;

    while (_capVideo.isOpened())
    {
        _frameProcesser.substractInfos(_frame, _debugMode);
        _frame.findEntitiesWithInfos();
        if (_firstFrame)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();
        second_img = _frame.getSecondImg().clone();
        displayImg(second_img);
        _frame.clearEntities();
        _frame.setFirstImg(_frame.getSecondImg());
        if ((_capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < _capVideo.get(CV_CAP_PROP_FRAME_COUNT))
        {
            _capVideo.read(second_img);
            _frame.setSecondImg(second_img);
        }
        else
        {
            Log::logSomething("End of video");
            return (0);
        }
        _frameCnt++;
        cv::waitKey(1);
    }
    return (1);
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
            setSavedEntityToFrameEntity(frameEntity, distance.indexEntity);
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
        if (savedEntity.getStillBeingTracked())
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

void FrameAnalyser::setSavedEntityToFrameEntity(const Entity &frameEntity, size_t index)
{
    _savedEntities[index].setContour(frameEntity.getContour());
    _savedEntities[index].setCurrentBoundingRect(frameEntity.getCurrentBoundingRect());
    _savedEntities[index].addCenterPosition(frameEntity.getCenterPositions().back());
    _savedEntities[index].setCurrentDiagonalSize(frameEntity.getCurrentDiagonalSize());
    _savedEntities[index].setCurrentAspectRatio(frameEntity.getCurrentAspectRatio());
    _savedEntities[index].setCurrentMatchFoundOrNewEntity(true);
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

void FrameAnalyser::displayImg(cv::Mat img)
{
    if (_debugMode & Log::debugMode::ENTITIES)
        _frameAdditionner.drawAndShowContours(_frameProcesser.getImgThresh().size(), _savedEntities, "imgEntities");
    if (_debugMode & Log::debugMode::TRACK)
        _frameAdditionner.drawTrackEntitiesOnImage(_savedEntities, img);
    if (_debugMode & Log::debugMode::NUMBER)
        _frameAdditionner.drawNumberEntitiesOnImage(_savedEntities, img);
    if (!(_debugMode & Log::debugMode::NO_ORIGINAL_VIDEO))
        cv::imshow("imgFrame", img);
    if (_debugMode & Log::debugMode::WAIT_KEY)
        cv::waitKey(0);
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
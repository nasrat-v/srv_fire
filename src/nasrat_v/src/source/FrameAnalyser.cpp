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


void FrameAnalyser::initAnalyser(const std::string &videoPath)
{
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

void FrameAnalyser::analyseFrame(cv::VideoCapture &capVideo)
{
    cv::Mat second_img;

    while (_capVideo.isOpened())
    {
        _frameSubstracter.substractInfos(_frame);
        _frame.findEntitiesWithInfos();
        if (_firstFrame)
            initSavedEntities();
        else
            matchFrameEntitiesToSavedEntities();
        // drawAndShowContours(imgThresh.size(), blobs, "imgBlobs");
        //drawBlobInfoOnImage(blobs, imgFrame2Copy);
        //cv::imshow("imgFrame2Copy", imgFrame2Copy);
        //cv::waitKey(0);
        _frame.clearEntities();
        _frame.setFirstImg(_frame.getSecondImg());
        if ((capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < capVideo.get(CV_CAP_PROP_FRAME_COUNT))
        {
            capVideo.read(second_img);
            _frame.setSecondImg(second_img);
        }
        else
            Log::logSomething("End of video");
        _frameCnt++;
    }
}

void FrameAnalyser::matchFrameEntitiesToSavedEntities()
{
    for (auto &savedEntity : _savedEntities)
    {
        savedEntity.setCurrentMatchFoundOrNewEntity(false);
        savedEntity.predictNextPosition();
    }
    for (auto &frameEntity : _frame.getEntities())
    {
        int intIndexOfLeastDistance = 0;
        double dblLeastDistance = 100000.0;

        for (unsigned int i = 0; i < _savedEntities.size(); i++)
        {
            if (_savedEntities[i].getStillBeingTracked())
            {
                double dblDistance = distanceBetweenPoints(frameEntity.getCenterPositions().back(), _savedEntities[i].getPredictedNextPosition());

                if (dblDistance < dblLeastDistance)
                {
                    dblLeastDistance = dblDistance;
                    intIndexOfLeastDistance = i;
                }
            }
        }
        if (dblLeastDistance < frameEntity.getCurrentDiagonalSize() * 1.15)
            setSavedEntityToFrameEntity(frameEntity, intIndexOfLeastDistance);
        else
            addNewSavedEntity(frameEntity);

    }

    /*for (auto &savedEntity : _frame.getEntities())
    {
        if (!savedEntity.getCurrentMatchFoundOrNewEntity())
            savedEntity.intNumOfConsecutiveFramesWithoutAMatch++;
        if (savedEntity.getNumOfConsecutiveFramesWithoutMatch() >= 5)
            savedEntity.setStillBeingTracked(false);
    }*/
}

void FrameAnalyser::setSavedEntityToFrameEntity(const Entity &frameEntity, int &intIndex)
{
    _savedEntities[intIndex].setContour(frameEntity.getContour());
    _savedEntities[intIndex].setCurrentBoundingRect(frameEntity.getCurrentBoundingRect());
    _savedEntities[intIndex].addCenterPosition(frameEntity.getCenterPositions().back());
    _savedEntities[intIndex].setCurrentDiagonalSize(frameEntity.getCurrentDiagonalSize());
    _savedEntities[intIndex].setCurrentAspectRatio(frameEntity.getCurrentAspectRatio());
    _savedEntities[intIndex].setStillBeingTracked(true);
    _savedEntities[intIndex].setCurrentMatchFoundOrNewEntity(true);
}

void FrameAnalyser::addNewSavedEntity(Entity &frameEntity)
{
    frameEntity.setCurrentMatchFoundOrNewEntity(true);
    _savedEntities.push_back(frameEntity);
}

double FrameAnalyser::distanceBetweenPoints(cv::Point firstPoint, cv::Point secondPoint)
{
    int intX = abs(firstPoint.x - secondPoint.x);
    int intY = abs(firstPoint.y - secondPoint.y);
    return (sqrt(pow(intX, 2) + pow(intY, 2)));
}
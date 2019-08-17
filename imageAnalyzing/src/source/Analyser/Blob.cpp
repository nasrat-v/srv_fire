//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/Blob.hh"

Blob::Blob(const std::vector<cv::Point> &contour)
{
    _form._contour = contour;
    _form._convexHull = contour;
    initCurrentAttributes();
    initCenterPosition();
    _predictedNextPosition = { 0 };
    _id = DEFAULT_ID_BLOB;
    _matchFoundOrNewBlob = true;
    _numOfConsecutiveFramesWithoutMatch = 0;
    _stillBeingTracked = true;
    _colorRange = DEFAULT_COLOR_RANGE_BLOB;
}

Blob::~Blob() = default;

void Blob::initCurrentAttributes()
{
    _boundingRect = cv::boundingRect(_form._contour);
    _diagonalSize = sqrt(pow(_boundingRect.width, 2) + pow(_boundingRect.height, 2));
    _aspectRatio = ((float)_boundingRect.width / (float)_boundingRect.height);
}

void Blob::initCenterPosition()
{
    cv::Point currentCenter;

    currentCenter.x = ((_boundingRect.x + _boundingRect.x + _boundingRect.width) / 2);
    currentCenter.y = ((_boundingRect.y + _boundingRect.y + _boundingRect.height) / 2);
    _centerPositions.push_back(currentCenter);
}

void Blob::clone(const Blob &blob)
{
    _aspectRatio = blob._aspectRatio;
    _diagonalSize = blob._diagonalSize;
    _boundingRect = blob._boundingRect;
    _predictedNextPosition = blob._predictedNextPosition;
    _centerPositions = std::vector<cv::Point>(blob._centerPositions);
    _form._contour = std::vector<cv::Point>(blob._form._contour);
    _form._convexHull = std::vector<cv::Point>(blob._form._convexHull);
    _id = blob._id;
    _matchFoundOrNewBlob = blob._matchFoundOrNewBlob;
    _numOfConsecutiveFramesWithoutMatch = blob._numOfConsecutiveFramesWithoutMatch;
    _stillBeingTracked = blob._stillBeingTracked;
    _colorRange = blob._colorRange;
}

bool Blob::isSame(const Blob &blob) const
{
    return (_aspectRatio == blob._aspectRatio &&
            _diagonalSize == blob._diagonalSize &&
            _boundingRect == blob._boundingRect &&
            _predictedNextPosition == blob._predictedNextPosition &&
            _centerPositions.back() == blob._centerPositions.back() &&
            _form._contour.back() == blob._form._contour.back() &&
            _form._convexHull.back() == blob._form._convexHull.back() &&
            _colorRange._nameRange == blob._colorRange._nameRange);
}

double Blob::getAspectRatio() const
{
    return (_aspectRatio);
}

double Blob::getDiagonalSize() const
{
    return (_diagonalSize);
}

const cv::Rect &Blob::getBoundingRect() const
{
    return (_boundingRect);
}

const std::vector<cv::Point> &Blob::getContour() const
{
    return (_form._contour);
}

const std::vector<cv::Point> &Blob::getConvexHull() const
{
    return (_form._convexHull);
}

const std::vector<cv::Point> &Blob::getCenterPositions() const
{
    return (_centerPositions);
}

size_t Blob::getId() const
{
    return (_id);
}

bool Blob::getMatchFoundOrNewBlob() const
{
    return (_matchFoundOrNewBlob);
}

int Blob::getNumOfConsecutiveFramesWithoutMatch() const
{
    return (_numOfConsecutiveFramesWithoutMatch);
}

const ScalarColor::t_colorRange &Blob::getColorRange() const
{
    return (_colorRange);
}

bool Blob::isStillBeingTracked() const
{
    return (_stillBeingTracked);
}

void Blob::setAspectRatio(double val)
{
    _aspectRatio = val;
}

void Blob::setDiagonalSize(double val)
{
    _diagonalSize = val;
}

void Blob::setBoundingRect(const cv::Rect &rect)
{
    _boundingRect = rect;
}

void Blob::setContour(const std::vector<cv::Point> &contour)
{
    _form._contour = contour;
}

void Blob::setConvexHull(const std::vector<cv::Point> &convexHull)
{
    _form._convexHull = convexHull;
}

void Blob::setId(size_t id)
{
    _id = id;
}

void Blob::setMatchFoundOrNewBlob(bool match)
{
    _matchFoundOrNewBlob = match;
}

void Blob::setNumOfConsecutiveFramesWithoutAMatch(int val)
{
    _numOfConsecutiveFramesWithoutMatch = val;
}

void Blob::setStillBeingTracked(bool tracked)
{
    _stillBeingTracked = tracked;
}

void Blob::setColorRange(const ScalarColor::t_colorRange &colorRange)
{
    _colorRange = colorRange;
}

void Blob::predictNextPosition()
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

void Blob::calculateSumOfChanges(t_sumOfChanges &sumOfChanges)
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
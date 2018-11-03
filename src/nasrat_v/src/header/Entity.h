//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_ENTITY_H
#define OPENCV_SRV_ENTITY_H

#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class Entity
{
public:
    Entity(const std::vector<cv::Point> &contour);
    ~Entity();

    void                            predictNextPosition();
    const double                    &getCurrentAspectRatio();
    const double                    &getCurrentDiagonalSize();
    const cv::Rect                  &getCurrentBoundingRect();
    const std::vector<cv::Point>    &getContour();
    const bool                      getStillBeingTracked();

private:
    /* Methods */
    void    initCenterPosition();
    void    initCurrentAttributes();
    void    calculateSumOfChanges(int *sumOfChanges, int *i, int *n);

    /* Attributes */
    int                     _numOfConsecutiveFramesWithoutMatch;
    bool                    _stillBeingTracked;
    bool                    _currentMatchFoundOrNewBlob;
    double                  _currentAspectRatio;
    double                  _currentDiagonalSize;
    cv::Rect                _currentBoundingRect;
    cv::Point               _predictedNextPosition;
    std::vector<cv::Point>  _centerPositions;
    std::vector<cv::Point>  _contour;
};


#endif //OPENCV_SRV_ENTITY_H

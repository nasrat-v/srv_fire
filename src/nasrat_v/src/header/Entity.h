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
    double                          getCurrentAspectRatio() const;
    double                          getCurrentDiagonalSize() const;
    const cv::Rect                  &getCurrentBoundingRect() const;
    const cv::Point                 &getPredictedNextPosition() const;
    const std::vector<cv::Point>    &getContour() const;
    const std::vector<cv::Point>    &getCenterPositions() const;
    bool                            getStillBeingTracked() const;
    bool                            getCurrentMatchFoundOrNewEntity() const;
    int                             getNumOfConsecutiveFramesWithoutMatch() const;
    void                            setCurrentAspectRatio(double val);
    void                            setCurrentDiagonalSize(double val);
    void                            setCurrentBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            addCenterPosition(const cv::Point &centerPosition);
    void                            setCurrentMatchFoundOrNewEntity(bool val);
    void                            setStillBeingTracked(bool val);

private:
    /* Methods */
    void                            initCenterPosition();
    void                            initCurrentAttributes();
    void                            calculateSumOfChanges(int *sumOfChanges, int *i, int *n);

    /* Attributes */
    int                             _numOfConsecutiveFramesWithoutMatch;
    bool                            _stillBeingTracked;
    bool                            _currentMatchFoundOrNewEntity;
    double                          _currentAspectRatio;
    double                          _currentDiagonalSize;
    cv::Rect                        _currentBoundingRect;
    cv::Point                       _predictedNextPosition;
    std::vector<cv::Point>          _centerPositions;
    std::vector<cv::Point>          _contour;
};


#endif //OPENCV_SRV_ENTITY_H

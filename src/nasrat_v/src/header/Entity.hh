//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_ENTITY_H
# define OPENCV_SRV_ENTITY_H

# define NB_FRAME_MOVE_PREDICTION    5

#include "Log/Log.hh"

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class Entity
{
public:
    explicit Entity(const std::vector<cv::Point> &contour);
    ~Entity();

    enum class entityMovement
    {
        MOVE,
        STATIC
    };

    enum class entityTemperature
    {
        WARM,
        HOT,
        VERY_HOT
    };

    void                            predictNextPosition();
    double                          getCurrentAspectRatio() const;
    double                          getCurrentDiagonalSize() const;
    const cv::Rect                  &getCurrentBoundingRect() const;
    const std::vector<cv::Point>    &getContour() const;
    const std::vector<cv::Point>    &getCenterPositions() const;
    const entityMovement            &getMovementType() const;
    const entityTemperature         &getTemperatureType() const;
    void                            setCurrentMatchFoundOrNewEntity(bool val);
    void                            setMovementType(const entityMovement &type);
    void                            setTemperatureType(const entityTemperature &type);

    /*const cv::Point                 &getPredictedNextPosition() const;
    bool                            getStillBeingTracked() const;
    bool                            getCurrentMatchFoundOrNewEntity() const;
    int                             getNumOfConsecutiveFramesWithoutMatch() const;
    void                            setCurrentAspectRatio(double val);
    void                            setCurrentDiagonalSize(double val);
    void                            setCurrentBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            addCenterPosition(const cv::Point &centerPosition);
    void                            setStillBeingTracked(bool val);
    void                            setNumOfConsecutiveFramesWithoutAMatch(int val);*/

private:
    /* Attributes */
    double                          _currentAspectRatio;
    double                          _currentDiagonalSize;
    cv::Rect                        _currentBoundingRect;
    cv::Point                       _predictedNextPosition;
    std::vector<cv::Point>          _centerPositions;
    std::vector<cv::Point>          _contour;
    entityMovement                  _movementType;
    entityTemperature               _temperatureType;
    bool                            _currentMatchFoundOrNewEntity;

    /*int                             _numOfConsecutiveFramesWithoutMatch;
    bool                            _stillBeingTracked;*/

    typedef struct                  s_sumOfChanges
    {
        short                       posX;
        short                       posY;
        short                       changesLeft;
        short                       nbChanges;
    }                               t_sumOfChanges;

    /* Methods */
    void                            initCenterPosition();
    void                            initCurrentAttributes();
    void                            calculateSumOfChanges(t_sumOfChanges &sumOfChanges);
};


#endif //OPENCV_SRV_ENTITY_H

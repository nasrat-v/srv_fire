//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_ENTITY_H
# define OPENCV_SRV_ENTITY_H

# define NB_FRAME_MOVE_PREDICTION    5

#include "output_static_object/Log.hh"

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class Entity
{
public:
    explicit Entity(const std::vector<cv::Point> &contour);
    ~Entity();

    enum class  entityType
    {
        MOVE,
        STATIC
    };

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
    const entityType                &getType() const;
    void                            setCurrentAspectRatio(double val);
    void                            setCurrentDiagonalSize(double val);
    void                            setCurrentBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            addCenterPosition(const cv::Point &centerPosition);
    void                            setCurrentMatchFoundOrNewEntity(bool val);
    void                            setStillBeingTracked(bool val);
    void                            setNumOfConsecutiveFramesWithoutAMatch(int val);
    void                            setType(const entityType &type);

private:
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
    entityType                      _type;

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

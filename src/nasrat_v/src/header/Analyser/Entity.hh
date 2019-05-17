//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_ENTITY_H
# define OPENCV_SRV_ENTITY_H

# define NB_FRAME_MOVE_PREDICTION    5
# define DEFAULT_NB_ENTITY          -1

#include "../Log/Log.hh"

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
        NO_TEMP,
        WARM,
        HOT,
        VERY_HOT
    };

    void                            clone(const Entity &entity);
    bool                            isSame(const Entity &entity) const;
    void                            predictNextPosition();
    double                          getAspectRatio() const;
    double                          getDiagonalSize() const;
    const cv::Rect                  &getBoundingRect() const;
    const std::vector<cv::Point>    &getContour() const;
    const std::vector<cv::Point>    &getCenterPositions() const;
    const entityMovement            &getMovementType() const;
    const entityTemperature         &getTemperatureType() const;
    int                             getNbEntity() const;
    bool                            getMatchFoundOrNewEntity() const;
    int                             getNumOfConsecutiveFramesWithoutMatch() const;
    bool                            isStillBeingTracked() const;
    void                            setAspectRatio(double val);
    void                            setDiagonalSize(double val);
    void                            setBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            setMovementType(const entityMovement &type);
    void                            setTemperatureType(const entityTemperature &type);
    void                            setNbEntity(int nb);
    void                            setMatchFoundOrNewEntity(bool match);
    void                            setNumOfConsecutiveFramesWithoutAMatch(int val);
    void                            setStillBeingTracked(bool tracked);

    /*const cv::Point                 &getPredictedNextPosition() const;
    void                            addCenterPosition(const cv::Point &centerPosition);*/

private:
    /* Attributes */
    double                          _aspectRatio { };
    double                          _diagonalSize { };
    cv::Rect                        _boundingRect;
    cv::Point                       _predictedNextPosition;
    std::vector<cv::Point>          _centerPositions;
    std::vector<cv::Point>          _contour;
    entityMovement                  _movementType;
    entityTemperature               _temperatureType;
    int                             _nbEntity;
    bool                            _matchFoundOrNewEntity;
    int                             _numOfConsecutiveFramesWithoutMatch;
    bool                            _stillBeingTracked;

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

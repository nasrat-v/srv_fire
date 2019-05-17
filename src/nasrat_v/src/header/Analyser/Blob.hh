//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_BLOB_HH
# define OPENCV_SRV_BLOB_HH

# define NB_FRAME_MOVE_PREDICTION    5
# define DEFAULT_NB_BLOB            -1

#include "../Log/Log.hh"

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class Blob
{
public:
    explicit Blob(const std::vector<cv::Point> &contour);
    virtual ~Blob();

    enum class blobMovement
    {
        MOVE,
        STATIC
    };

    enum class blobTemperature
    {
        NO_TEMP,
        WARM,
        HOT,
        VERY_HOT
    };

    typedef struct                  s_blobForm
    {
        std::vector<cv::Point>      _contour;
        std::vector<cv::Point>      _convexHull;
    }                               t_blobForm;

    void                            clone(const Blob &blob);
    bool                            isSame(const Blob &blob) const;
    void                            predictNextPosition();
    double                          getAspectRatio() const;
    double                          getDiagonalSize() const;
    const cv::Rect                  &getBoundingRect() const;
    const std::vector<cv::Point>    &getContour() const;
    const std::vector<cv::Point>    &getConvexHull() const;
    const std::vector<cv::Point>    &getCenterPositions() const;
    const blobMovement              &getMovementType() const;
    const blobTemperature           &getTemperatureType() const;
    int                             getNbBlob() const;
    bool                            getMatchFoundOrNewBlob() const;
    int                             getNumOfConsecutiveFramesWithoutMatch() const;
    bool                            isStillBeingTracked() const;
    void                            setAspectRatio(double val);
    void                            setDiagonalSize(double val);
    void                            setBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            setConvexHull(const std::vector<cv::Point> &convexHulls);
    void                            setMovementType(const blobMovement &type);
    void                            setTemperatureType(const blobTemperature &type);
    void                            setNbBlob(int nb);
    void                            setMatchFoundOrNewBlob(bool match);
    void                            setNumOfConsecutiveFramesWithoutAMatch(int val);
    void                            setStillBeingTracked(bool tracked);

    /*const cv::Point                 &getPredictedNextPosition() const;
    void                            addCenterPosition(const cv::Point &centerPosition);*/

protected:
    /* Attributes */
    double                          _aspectRatio { };
    double                          _diagonalSize { };
    cv::Rect                        _boundingRect;
    cv::Point                       _predictedNextPosition;
    std::vector<cv::Point>          _centerPositions;
    blobMovement                    _movementType;
    blobTemperature                 _temperatureType;
    int                             _nbBlob;
    bool                            _matchFoundOrNewBlob;
    int                             _numOfConsecutiveFramesWithoutMatch;
    bool                            _stillBeingTracked;
    t_blobForm                      _form;

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


#endif //OPENCV_SRV_BLOB_HH

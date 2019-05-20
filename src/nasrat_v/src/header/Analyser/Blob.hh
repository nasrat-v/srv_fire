//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_BLOB_HH
# define OPENCV_SRV_BLOB_HH

# define NB_FRAME_MOVE_PREDICTION    5
# define DEFAULT_ID_BLOB            -1
# define DEFAULT_COLOR_RANGE_BLOB   WHITE_RANGE

#include "../Log/Log.hh"
#include "ScalarColor.hpp"

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types.hpp>

class Blob
{
public:
    explicit Blob(const std::vector<cv::Point> &contour);
    virtual ~Blob();

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
    size_t                          getId() const;
    bool                            getMatchFoundOrNewBlob() const;
    int                             getNumOfConsecutiveFramesWithoutMatch() const;
    const ScalarColor::t_colorRange &getColorRange() const;
    bool                            isStillBeingTracked() const;
    void                            setAspectRatio(double val);
    void                            setDiagonalSize(double val);
    void                            setBoundingRect(const cv::Rect &rect);
    void                            setContour(const std::vector<cv::Point> &contour);
    void                            setConvexHull(const std::vector<cv::Point> &convexHulls);
    void                            setId(size_t id);
    void                            setMatchFoundOrNewBlob(bool match);
    void                            setNumOfConsecutiveFramesWithoutAMatch(int val);
    void                            setStillBeingTracked(bool tracked);
    void                            setColorRange(const ScalarColor::t_colorRange &colorRange);

    /*const cv::Point                 &getPredictedNextPosition() const;
    void                            addCenterPosition(const cv::Point &centerPosition);*/

protected:
    /* Attributes */
    double                          _aspectRatio { };
    double                          _diagonalSize { };
    cv::Rect                        _boundingRect;
    cv::Point                       _predictedNextPosition;
    std::vector<cv::Point>          _centerPositions;
    size_t                          _id;
    bool                            _matchFoundOrNewBlob;
    int                             _numOfConsecutiveFramesWithoutMatch;
    bool                            _stillBeingTracked;
    t_blobForm                      _form;
    ScalarColor::t_colorRange       _colorRange;

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

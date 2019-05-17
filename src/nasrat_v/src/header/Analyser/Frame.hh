//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAME_H
# define OPENCV_SRV_FRAME_H

#include <map>
#include <opencv2/core/mat.hpp>

#include "Blob.hh"
#include "ImageProcesser.hh"
#include "../Log/Error.hh"

class Frame
{
public:
    Frame();
    ~Frame();

    void                                        addImage(const cv::Mat &img);
    void                                        addPossibleBlob(const ImageProcesser::t_colorRange &colorRange,
                                                                const Blob::t_blobForm &possibleBlob);
    void                                        setImage(const cv::Mat &img, size_t index);
    void                                        setMovementTypeBlob(size_t index, const Blob::blobMovement &type);
    void                                        setTemperatureTypeBlob(size_t index, const Blob::blobTemperature &type);
    const std::vector<cv::Mat>                  &getImages() const;
    const std::vector<Blob>                     &getBlobs() const;
    const std::vector<Blob::t_blobForm>         &getPossibleBlobs(const ImageProcesser::t_colorRange &colorRange) const;
    void                                        clearBlobs();
    void                                        clearPossibleBlobs();
    void                                        predictNextPositionBlobs();
    void                                        addBlob(const Blob &blob);

private:
    /* Attributes */
    std::vector<cv::Mat>                        _images;
    std::vector<Blob>                           _blobs;
    std::map<ImageProcesser::t_colorRange, std::vector<Blob::t_blobForm>>   _possibleBlobs
};


#endif //OPENCV_SRV_FRAME_H

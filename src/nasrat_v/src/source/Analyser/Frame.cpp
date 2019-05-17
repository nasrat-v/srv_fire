//
// Created by nasrat_v on 11/3/18.
//

#include "../../header/Analyser/Frame.hh"

Frame::Frame() = default;

Frame::~Frame() = default;

void Frame::addImage(const cv::Mat &img)
{
    _images.push_back(img);
}

void Frame::addBlob(const Blob &blob)
{
    _blobs.push_back(blob);
}

void Frame::addPossibleBlob(const ImageProcesser::t_colorRange &colorRange,
                            const Blob::t_blobForm &possibleBlob)
{
    _possibleBlobs[colorRange].push_back(possibleBlob);
}

void Frame::setImage(const cv::Mat &img, size_t index)
{
    _images.at(index) = img;
}

void Frame::setMovementTypeBlob(size_t index, const Blob::blobMovement &type)
{
    _blobs.at(index).setMovementType(type);
}

void Frame::setTemperatureTypeBlob(size_t index, const Blob::blobTemperature &type)
{
    _blobs.at(index).setTemperatureType(type);
}

const std::vector<cv::Mat> &Frame::getImages() const
{
    return (_images);
}

const std::vector<Blob> &Frame::getBlobs() const
{
    return (_blobs);
}

const std::vector<Blob::t_blobForm> &Frame::getPossibleBlobs(const ImageProcesser::t_colorRange &colorRange) const
{
    return (_possibleBlobs.at(colorRange));
}

void Frame::clearBlobs()
{
    _blobs.clear();
}

void Frame::clearPossibleBlobs()
{
    _possibleBlobs.clear();
}

void Frame::predictNextPositionBlobs()
{
    for (auto &blob : _blobs)
        blob.predictNextPosition();
}
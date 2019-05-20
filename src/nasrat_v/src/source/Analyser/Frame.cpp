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

void Frame::addEntity(const Entity &entity)
{
    _entities.push_back(entity);
}

void Frame::addFormBlob(const ScalarColor::t_colorRange &colorRange, const Blob::t_blobForm &possibleBlob)
{
    _formBlobs[colorRange].push_back(possibleBlob);
}

void Frame::addFormEntity(const Entity::t_blobForm &possibleEntity)
{
    _formEntities.push_back(possibleEntity);
}

void Frame::setImage(const cv::Mat &img, size_t index)
{
    _images.at(index) = img;
}

void Frame::setBlobs(const std::vector<Blob> &blobs)
{
    _blobs = std::vector<Blob>(blobs);
}

void Frame::setEntities(const std::vector<Entity> &entities)
{
    _entities = std::vector<Entity>(entities);
}

const std::vector<cv::Mat> &Frame::getImages() const
{
    return (_images);
}

const std::vector<Blob> &Frame::getBlobs() const
{
    return (_blobs);
}

const std::vector<Entity> &Frame::getEntities() const
{
    return (_entities);
}

const std::vector<Blob::t_blobForm> &Frame::getFormBlobs(const ScalarColor::t_colorRange &colorRange)
{
    return (_formBlobs[colorRange]);
}

const std::vector<Entity::t_blobForm> &Frame::getFormEntities() const
{
    return (_formEntities);
}

void Frame::clearAllBlobs()
{
    _blobs.clear();
    _entities.clear();
    _formBlobs.clear();
    _formEntities.clear();
}
//
// Created by nasrat_v on 5/17/19.
//

#include "../../header/Analyser/Entity.hh"

Entity::Entity(const std::vector<cv::Point> &contour) : Blob(contour)
{
    _id = DEFAULT_ID_ENTITY;
    _colorRange = DEFAULT_COLOR_RANGE_ENTITY;
}

Entity::~Entity() = default;


void Entity::addBlob(const Blob &blob)
{
    _blobs.push_back(blob);
}

const std::vector<Blob> &Entity::getBlobs() const
{
    return (_blobs);
}


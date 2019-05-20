//
// Created by nasrat_v on 5/19/19.
//

#include "../../header/Analyser/EntityFilter.hh"

EntityFilter::EntityFilter() = default;

EntityFilter::~EntityFilter() = default;

bool EntityFilter::isPossibleEntity(const Entity &possibleEntity)
{
    return (possibleEntity.getBoundingRect().area() > 150 && possibleEntity.getAspectRatio() >= 0.2 &&
            possibleEntity.getAspectRatio() <= 1.25 && possibleEntity.getBoundingRect().width > 30 &&
            possibleEntity.getBoundingRect().height > 30 && possibleEntity.getDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleEntity.getContour()) / (double)possibleEntity.getBoundingRect().area()) > 0.40);
}

void EntityFilter::filtratePossibleEntities(const std::vector<Entity::t_blobForm> &possibleEntities,
                                            std::vector<Entity> &entitiesFiltred)
{
    int index = 0;

    for (auto &formEntity : possibleEntities)
    {
        Entity pEntity(formEntity._contour);

        if (isPossibleEntity(pEntity))
            entitiesFiltred.push_back(pEntity);
    }
}
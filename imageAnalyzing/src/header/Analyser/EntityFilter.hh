//
// Created by nasrat_v on 5/19/19.
//

#ifndef OPENCV_SRV_ENTITYFILTER_HH
#define OPENCV_SRV_ENTITYFILTER_HH

#include "Entity.hh"

class EntityFilter
{
public:
    EntityFilter();
    ~EntityFilter();

    void        filtratePossibleEntities(const std::vector<Entity::t_blobForm> &possibleEntities,
                                         std::vector<Entity> &entitiesFiltred);

private:
    /* Methods */
    bool        isPossibleEntity(const Entity &possibleEntity);
};

#endif //OPENCV_SRV_ENTITYFILTER_HH

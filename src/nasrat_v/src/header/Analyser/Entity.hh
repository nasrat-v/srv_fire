//
// Created by nasrat_v on 5/17/19.
//

#ifndef OPENCV_SRV_ENTITY_HH
#define OPENCV_SRV_ENTITY_HH

#include "Blob.hh"

class Entity : public Blob
{
public:
    Entity(const std::vector<cv::Point> &contour);
    ~Entity();

    void                    addBlob(const Blob &blob);
    const std::vector<Blob> &getBlobs() const;

private:
    std::vector<Blob>       _blobs;
};

#endif //OPENCV_SRV_ENTITY_HH

//
// Created by nasrat_v on 11/3/18.
//

#ifndef OPENCV_SRV_FRAME_H
# define OPENCV_SRV_FRAME_H

#include <map>
#include <opencv2/core/mat.hpp>

#include "Entity.hh"
#include "ImageProcesser.hh"

class Frame
{
public:
    Frame();
    ~Frame();

    void                                        addImage(const cv::Mat &img);
    void                                        addBlob(const Blob &blob);
    void                                        addEntity(const Entity &entity);
    void                                        addFormBlob(const ScalarColor::t_colorRange &colorRange,
                                                                const Blob::t_blobForm &possibleBlob);
    void                                        addFormEntity(const Entity::t_blobForm &possibleEntity);
    void                                        setImage(const cv::Mat &img, size_t index);
    void                                        setBlobs(const std::vector<Blob> &blobs);
    void                                        setEntities(const std::vector<Entity> &entities);
    const std::vector<cv::Mat>                  &getImages() const;
    const std::vector<Blob>                     &getBlobs() const;
    const std::vector<Entity>                   &getEntities() const;
    const std::vector<Blob::t_blobForm>         &getFormBlobs(const ScalarColor::t_colorRange &colorRange);
    const std::vector<Entity::t_blobForm>       &getFormEntities() const;
    void                                        clearAllBlobs();


private:
    /* Attributes */
    std::vector<cv::Mat>                        _images;
    std::vector<Blob>                           _blobs;
    std::vector<Entity>                         _entities;
    std::map<ScalarColor::t_colorRange, std::vector<Blob::t_blobForm>>  _formBlobs;
    std::vector<Entity::t_blobForm>                                     _formEntities;
};


#endif //OPENCV_SRV_FRAME_H

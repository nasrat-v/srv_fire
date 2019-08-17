//
// Created by nasrat_v on 5/19/19.
//

#ifndef OPENCV_SRV_BLOBFILTER_HH
#define OPENCV_SRV_BLOBFILTER_HH

#include "Blob.hh"

class BlobFilter
{
public:
    BlobFilter();
    virtual ~BlobFilter();

    virtual void        filtratePossibleBlobs(const ScalarColor::t_colorRange &colorRange,
                                              const std::vector<Blob::t_blobForm> &possibleBlobs,
                                              std::vector<Blob> &blobsFiltred);

private:
    /* Methods */
    virtual bool        isPossibleBlob(const Blob &possibleBlob);
};

#endif //OPENCV_SRV_BLOBFILTER_HH

//
// Created by nasrat_v on 5/19/19.
//

#include "../../header/Analyser/BlobFilter.hh"

BlobFilter::BlobFilter() = default;

BlobFilter::~BlobFilter() = default;

bool BlobFilter::isPossibleBlob(const Blob &possibleBlob)
{
    return (possibleBlob.getBoundingRect().area() > 150 && possibleBlob.getAspectRatio() >= 0.2 &&
            possibleBlob.getAspectRatio() <= 1.25 && possibleBlob.getBoundingRect().width > 30 &&
            possibleBlob.getBoundingRect().height > 30 && possibleBlob.getDiagonalSize() > 30.0 &&
            (cv::contourArea(possibleBlob.getContour()) / (double)possibleBlob.getBoundingRect().area()) > 0.40);
}

void BlobFilter::filtratePossibleBlobs(const ScalarColor::t_colorRange &colorRange,
                                        const std::vector<Blob::t_blobForm> &possibleBlobs,
                                        std::vector<Blob> &blobsFiltred)
{
    for (auto &formBlob : possibleBlobs)
    {
        Blob pBlob(formBlob._contour);

        if (isPossibleBlob(pBlob))
        {
            pBlob.setColorRange(colorRange);
            blobsFiltred.push_back(pBlob);
        }
    }
}
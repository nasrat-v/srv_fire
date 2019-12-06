//
// Created by nasrat_v on 11/6/18.
//

#include "../../header/Analyser/ImageService.hh"

ImageService::ImageService(const char *defaukltVideoPath, 
                            const DebugManager::debugMode &mode) :  _debugMode(mode), 
                                                                    _imageProvider(defaukltVideoPath, mode)
{
    _firstTime = true;
}

ImageService::~ImageService() = default;

/////////////////////// Image Processing //////////////////////////

void ImageService::substractInfosPossibleBlobs(Frame &frame,
                                                const std::vector<ScalarColor::t_colorRange> &colorRanges)
{
    cv::Mat imgProcessed;

    for (auto &colorR : colorRanges)
    {
        imgProcessed = frame.getImages().front().clone();
        substractColor(imgProcessed, colorR);
        threshImg(imgProcessed);
        addFormBlob(frame, imgProcessed, colorR);
    }
}

void ImageService::substractInfosPossibleEntities(Frame &frame,
                                                    const std::vector<std::vector<cv::Point>> &allContours)
{
    cv::Mat imgMerge(frame.getImages().front().size(), CV_8UC3, SCALAR_BLACK);

    mergeAllContours(imgMerge, allContours);
    addFormEntity(frame, imgMerge);
}


void ImageService::substractInfosBlobsInMovement(Frame &frame)
{
    cv::Mat imgProcessed;

    differenceImg(frame.getImages().front().clone(), frame.getImages().back().clone(), imgProcessed);
    threshImg(imgProcessed);
}

void ImageService::substractColor(cv::Mat &imgProcessed, const ScalarColor::t_colorRange &range)
{
    _imageProcesser.imgToHSV(imgProcessed, range);
    if (_debugMode & DebugManager::debugMode::SUBSTRACT_COLOR)
        cv::imshow(("SubstractColor " + range._nameRange), imgProcessed);
}

void ImageService::differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed)
{
    imgProcessed = _imageProcesser.differenceImgGray(std::move(firstImg), std::move(secondImg));
    if (_debugMode & DebugManager::debugMode::DIFFERENCE)
        cv::imshow("Difference", imgProcessed);
}

void ImageService::threshImg(cv::Mat &imgProcessed)
{
    _imageProcesser.threshImg(imgProcessed);
    if (_debugMode & DebugManager::debugMode::THRESH)
        cv::imshow("Thresh", imgProcessed);
}

void ImageService::addFormBlob(Frame &frame, const cv::Mat &imgProcessed,
                                const ScalarColor::t_colorRange &colorRange)
{
    int                                 index = 0;
    Blob::t_blobForm                    blobForm;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<std::vector<cv::Point>> convexHulls;

    findContoursFrame(imgProcessed, colorRange, contours);
    findConvexHullsFrame(imgProcessed.size(), colorRange, contours, convexHulls);
    for (auto ctr : contours)
    {
        blobForm._contour = ctr;
        blobForm._convexHull = convexHulls[index];
        frame.addFormBlob(colorRange, blobForm);
        index++;
    }
}

void ImageService::addFormEntity(Frame &frame, const cv::Mat &imgMerge)
{
    int                                 index = 0;
    Blob::t_blobForm                    blobForm;
    std::vector<std::vector<cv::Point>> contoursMerged;
    std::vector<std::vector<cv::Point>> convexHullsMerged;

    findContoursMergedFrame(imgMerge, contoursMerged);
    findConvexHullsMergedFrame(imgMerge.size(), contoursMerged, convexHullsMerged);
    for (auto &ctrM : contoursMerged)
    {
        blobForm._contour = ctrM;
        blobForm._convexHull = convexHullsMerged[index];
        frame.addFormEntity(blobForm);
        index++;
    }
}

void ImageService::findContoursFrame(const cv::Mat &imgProcessed,
                                     const ScalarColor::t_colorRange &colorRange,
                                     std::vector<std::vector<cv::Point>> &contours)
{
    contours = _imageProcesser.findContoursFromImg(imgProcessed);
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), contours,
                                              ("Blob Form Contours " + colorRange._nameRange), colorRange);
}

void ImageService::findConvexHullsFrame(const cv::Size &imageSize,
                                        const ScalarColor::t_colorRange &colorRange,
                                        const std::vector<std::vector<cv::Point>> &contours,
                                        std::vector<std::vector<cv::Point>> &convexHulls)
{
    convexHulls = _imageProcesser.findConvexHullsFromContours(contours);
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imageSize, convexHulls,
                                              ("Blob Form ConvexHulls " + colorRange._nameRange), colorRange);
}

std::vector<cv::Point> ImageService::mergeContour(const cv::Size &imgSize,
                                                  const std::vector<cv::Point> &contourFirst,
                                                  const std::vector<cv::Point> &contourSecond)
{
    cv::Mat image(std::move(imgSize), CV_8UC3, SCALAR_BLACK);
    std::vector<std::vector<cv::Point>> tmpContours;

    tmpContours.push_back(contourFirst);
    tmpContours.push_back(contourSecond);
    _imageAdditionner.drawContours(image, tmpContours, WHITE_RANGE);
    _imageProcesser.imgToGray(image);
    _imageProcesser.threshImg(image);
    imshow("toto", image);
    return (_imageProcesser.findContoursFromImg(image).front());
}

void ImageService::mergeAllContours(cv::Mat &img, const std::vector<std::vector<cv::Point>> &allContours)
{
    _imageAdditionner.drawContours(img, allContours, WHITE_RANGE);
    _imageProcesser.imgToGray(img);
    _imageProcesser.threshImg(img);
}

void ImageService::findContoursMergedFrame(const cv::Mat &imgMerge,
                                            std::vector<std::vector<cv::Point>> &contoursMerged)
{
    contoursMerged = _imageProcesser.findContoursFromImg(imgMerge);
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgMerge.size(), contoursMerged,
                                              "Blob Form Contours Merged", WHITE_RANGE);
}

void ImageService::findConvexHullsMergedFrame(const cv::Size &imageSize,
                                              const std::vector<std::vector<cv::Point>> &contoursMerged,
                                              std::vector<std::vector<cv::Point>> &convexHullsMerged)
{
    convexHullsMerged = _imageProcesser.findConvexHullsFromContours(contoursMerged);
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imageSize, convexHullsMerged,
                                              "Blob Form ConvexHulls Merged", WHITE_RANGE);
}

/////////////////////// Image Providing //////////////////////////

ImageProvider::statusVideo ImageService::openVideo()
{
    return (_imageProvider.openVideo());
}

ImageProvider::statusVideo ImageService::getNextImg(Frame &frame)
{
    if (_firstTime)
    {
        _firstTime = false;
        return (initImg(frame));
    }
    return (incrementImg(frame));
}

ImageProvider::statusVideo ImageService::initImg(Frame &frame)
{
    std::vector<cv::Mat> imgs;
    ImageProvider::statusVideo status;

    status = _imageProvider.initImg(imgs, NB_IMG_INCR);
    for (const cv::Mat &img : imgs)
        frame.addImage(img);
    return (status);
}

ImageProvider::statusVideo ImageService::incrementImg(Frame &frame)
{
    size_t i = 0;
    cv::Mat nextImage;
    ImageProvider::statusVideo status;

    status = _imageProvider.incrementImg(nextImage, NB_IMG_INCR);
    while (i < (frame.getImages().size() - 1))
    {
        frame.setImage(frame.getImages()[i + 1], i);
        i++;
    }
    frame.setImage(nextImage, (frame.getImages().size() - 1));
    return (status);
}

ImageProvider::statusVideo ImageService::createSampleImgFromVideo()
{
    ImageProvider::statusVideo status;

    if ((status =_imageProvider.openVideo()) != ImageProvider::statusVideo::OPEN)
    {
        Error::logError(Error::ErrorType::OPEN_VID, "Cannot create sample IMG");
        return (status);
    }
    _imageProvider.createSampleImgFromVideo();
}

/////////////////////// Image Addition //////////////////////////

void ImageService::displayBlobs(const cv::Size &imgSize, const std::vector<Blob> &blobs,
                                const std::string &strImageName,
                                const std::vector<ScalarColor::t_colorRange> &colorToAnalyse)
{
    _imageAdditionner.drawAndShowContours(imgSize, blobs, strImageName, colorToAnalyse);
}

void ImageService::displayImg(cv::Mat img, const std::vector<Blob> &savedBlobs,
                                            const std::vector<Blob> &frameBlobs,
                                            const std::vector<Entity> &savedEntities,
                                            const std::vector<Entity> &frameEntities,
                                            const std::vector<ScalarColor::t_colorRange> &colorToAnalyse)
{
    cv::Mat trackImg = img.clone();

    if (_debugMode & DebugManager::debugMode::SAVED_BLOBS)
        displayBlobs(img.size(), savedBlobs, "Saved Blobs", colorToAnalyse);
    if (_debugMode & DebugManager::debugMode::FRAME_FILTRATE_BLOBS)
        displayBlobs(img.size(), frameBlobs, "Frame Filtrate Blobs", colorToAnalyse);
    if (_debugMode & DebugManager::debugMode::TRACK)
        _imageAdditionner.drawTrackEntitiesOnImage(trackImg, savedEntities, frameEntities);
    if (_debugMode & DebugManager::debugMode::HOT_SPOT)
        _imageAdditionner.drawTrackBlobsOnImage(trackImg, savedBlobs, frameBlobs);
    if (_debugMode & DebugManager::debugMode::NUMBER)
        _imageAdditionner.drawNumberEntitiesOnImage(trackImg, savedEntities, frameEntities);
    if (!(_debugMode & DebugManager::debugMode::NO_ORIGINAL_VIDEO))
        cv::imshow("Frame", trackImg);
    if (_debugMode & DebugManager::debugMode::WAIT_KEY)
        cv::waitKey(0);
}

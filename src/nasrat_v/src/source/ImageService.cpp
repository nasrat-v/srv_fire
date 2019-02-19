//
// Created by nasrat_v on 11/6/18.
//

#include "../header/ImageService.h"

ImageService::ImageService(const DebugManager::debugMode &mode, const std::string &videoPath) :  _debugMode(mode),
                                                                                                 _imageProvider(videoPath)
{
    _firstTime = true;
}

ImageService::~ImageService() = default;

/////////////////////// Image Processing //////////////////////////

void ImageService::substractInfosAllEntities(Frame &frame)
{
    cv::Mat imgProcessed = frame.getImages().front().clone();

    substractColor(imgProcessed, YELLOW_RANGE);
    threshImg(imgProcessed);
    setContoursWarmFrame(frame, imgProcessed);
    setConvexHullsWarmFrame(frame, imgProcessed);

    imgProcessed = frame.getImages().front().clone();

    substractColor(imgProcessed, ORANGE_RANGE);
    threshImg(imgProcessed);
    setContoursHotFrame(frame, imgProcessed);
    setConvexHullsHotFrame(frame, imgProcessed);

    imgProcessed = frame.getImages().front().clone();

    substractColor(imgProcessed, RED_RANGE);
    threshImg(imgProcessed);
    setContoursVeryHotFrame(frame, imgProcessed);
    setConvexHullsVeryHotFrame(frame, imgProcessed);
}

void ImageService::substractInfosEntitiesInMovement(Frame &frame)
{
    cv::Mat imgProcessed;

    differenceImg(frame.getImages().front().clone(), frame.getImages().back().clone(), imgProcessed);
    threshImg(imgProcessed);
    //setContoursMovementFrame(frame, imgProcessed);
    //setConvexHullsMovementFrame(frame, imgProcessed);
}

void ImageService::substractColor(cv::Mat &imgProcessed, const ImageProcesser::t_colorRange &range)
{
    _imageProcesser.imgToHSV(imgProcessed, range);
    if (_debugMode & DebugManager::debugMode::SUBSTRACT_COLOR)
        cv::imshow("imgSubstractColor", imgProcessed);
}

void ImageService::differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed)
{
    imgProcessed = _imageProcesser.differenceImgGray(std::move(firstImg), std::move(secondImg));
    if (_debugMode & DebugManager::debugMode::DIFFERENCE)
        cv::imshow("imgDifference", imgProcessed);
}

void ImageService::threshImg(cv::Mat &imgProcessed)
{
    _imageProcesser.threshImg(imgProcessed);
    if (_debugMode & DebugManager::debugMode::THRESH)
        cv::imshow("imgThresh", imgProcessed);
}

void ImageService::setContoursWarmFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setContoursWarm(_imageProcesser.findContoursFromImg(imgProcessed));
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getContoursWarm(), "imgContoursWarm");
}

void ImageService::setConvexHullsWarmFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setConvexHullsWarm(_imageProcesser.findConvexHullsFromContours(frame.getContoursWarm()));
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getConvexHullsWarm(), "imgConvexHullsWarm");
}

void ImageService::setContoursHotFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setContoursHot(_imageProcesser.findContoursFromImg(imgProcessed));
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getContoursHot(), "imgAContoursHot");
}

void ImageService::setConvexHullsHotFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setConvexHullsHot(_imageProcesser.findConvexHullsFromContours(frame.getContoursHot()));
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getConvexHullsHot(), "imgConvexHullsHot");
}

void ImageService::setContoursVeryHotFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setContoursVeryHot(_imageProcesser.findContoursFromImg(imgProcessed));
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getContoursVeryHot(), "imgAContoursVeryHot");
}

void ImageService::setConvexHullsVeryHotFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setConvexHullsVeryHot(_imageProcesser.findConvexHullsFromContours(frame.getContoursVeryHot()));
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getConvexHullsVeryHot(), "imgConvexHullsVeryHot");
}

/*void ImageService::setContoursMovementFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setContoursMovement(_imageProcesser.findContoursFromImg(imgProcessed));
    if (_debugMode & DebugManager::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getAllContours(), "imgContoursMovement");
}

void ImageService::setConvexHullsMovementFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setConvexHullsMovement(_imageProcesser.findConvexHullsFromContours(frame.getAllContours()));
    if (_debugMode & DebugManager::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getAllConvexHulls(), "imgConvexHullsMovement");
}*/

/////////////////////// Image Providing //////////////////////////

ImageProvider::statusVideo ImageService::openVideo()
{
    return (_imageProvider.openVideo());
}

ImageProvider::statusVideo ImageService::getNextImg(Frame &frame)
{
    if (_imageProvider.videoContinues() == ImageProvider::statusVideo::CONTINUE)
    {
        if (_firstTime)
        {
            _firstTime = false;
            return (initImg(frame));
        }
        return (incrementImg(frame));
    }
    return (ImageProvider::statusVideo::END);
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

    status = _imageProvider.incrementImg(nextImage);
    while (i < (frame.getImages().size() - 1))
    {
        frame.setImage(frame.getImages()[i + 1], i);
        i++;
    }
    frame.setImage(nextImage, (frame.getImages().size() - 1));
    return (status);
}

/////////////////////// Image Addition //////////////////////////

void ImageService::displayImg(cv::Mat img, /*const std::vector<Entity> &savedEntities,*/ const std::vector<Entity> &frameEntities)
{
    cv::Mat trackImg = img.clone();

    //if (_debugMode & Log::debugMode::SAVED_ENTITIES)
    //    _imageAdditionner.drawAndShowContours(img.size(), savedEntities, "imgEntities");
    if (_debugMode & DebugManager::debugMode::FRAME_ENTITIES)
        _imageAdditionner.drawAndShowContours(img.size(), frameEntities, "imgFrameEntities");
    if (_debugMode & DebugManager::debugMode::TRACK)
        //_imageAdditionner.drawTrackEntitiesOnImage(savedEntities, trackImg);
        _imageAdditionner.drawTrackEntitiesOnImage(frameEntities, trackImg);
    if (_debugMode & DebugManager::debugMode::NUMBER)
        //_imageAdditionner.drawNumberEntitiesOnImage(savedEntities, trackImg);
        _imageAdditionner.drawNumberEntitiesOnImage(frameEntities, trackImg);
    if (!(_debugMode & DebugManager::debugMode::NO_ORIGINAL_VIDEO))
        cv::imshow("imgFrame", trackImg);
    if (_debugMode & DebugManager::debugMode::WAIT_KEY)
        cv::waitKey(0);
}

//
// Created by nasrat_v on 11/6/18.
//

#include "../header/ImageService.h"

ImageService::ImageService(const Log::debugMode &mode, const std::string &videoPath) :  _debugMode(mode),
                                                                                        _imageProvider(videoPath)
{
    _firstTime = true;
}

ImageService::~ImageService() = default;

void ImageService::substractInfos(Frame &frame, const Entity::entityType &type)
{
    cv::Mat imgProcessed;

    differenceImg(frame.getImages().front().clone(), frame.getImages().back().clone(), imgProcessed, type);
    threshImg(imgProcessed, type);
    setContoursFrame(frame, imgProcessed);
    setConvexHullsFrame(frame, imgProcessed);
}

void ImageService::differenceImg(cv::Mat firstImg, cv::Mat secondImg, cv::Mat &imgProcessed, const Entity::entityType &type)
{
    imgProcessed = _imageProcesser.differenceImg(std::move(firstImg), std::move(secondImg), type);
    if (_debugMode & Log::debugMode::DIFFERENCE)
        cv::imshow("imgDifference", imgProcessed);
}

void ImageService::threshImg(cv::Mat &imgProcessed, const Entity::entityType &type)
{
    imgProcessed = _imageProcesser.threshImg(imgProcessed);
    if (_debugMode & Log::debugMode::THRESH)
    {
        if (type == Entity::entityType::FIRE)
            cv::imshow("imgThresFire", imgProcessed);
        else
            cv::imshow("imgThreshHuman", imgProcessed);
    }
}

void ImageService::setContoursFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setAllContours(_imageProcesser.findContoursFromImg(imgProcessed));
    if (_debugMode & Log::debugMode::CONTOUR)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getAllContours(), "imgContours");
}

void ImageService::setConvexHullsFrame(Frame &frame, const cv::Mat &imgProcessed)
{
    frame.setAllConvexHulls(_imageProcesser.findConvexHullsFromContours(frame.getAllContours()));
    if (_debugMode & Log::debugMode::CONVEXHULLS)
        _imageAdditionner.drawAndShowContours(imgProcessed.size(), frame.getAllConvexHulls(), "imgConvexHulls");
}

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

void ImageService::displayImg(cv::Mat img, /*const std::vector<Entity> &savedEntities,*/ const std::vector<Entity> &frameEntities)
{
    cv::Mat trackImg = img.clone();

    //if (_debugMode & Log::debugMode::SAVED_ENTITIES)
    //    _imageAdditionner.drawAndShowContours(img.size(), savedEntities, "imgEntities");
    if (_debugMode & Log::debugMode::FRAME_ENTITIES)
        _imageAdditionner.drawAndShowContours(img.size(), frameEntities, "imgFrameEntities");
    if (_debugMode & Log::debugMode::TRACK)
        //_imageAdditionner.drawTrackEntitiesOnImage(savedEntities, trackImg);
        _imageAdditionner.drawTrackEntitiesOnImage(frameEntities, trackImg);
    if (_debugMode & Log::debugMode::NUMBER)
        //_imageAdditionner.drawNumberEntitiesOnImage(savedEntities, trackImg);
        _imageAdditionner.drawNumberEntitiesOnImage(frameEntities, trackImg);
    if (!(_debugMode & Log::debugMode::NO_ORIGINAL_VIDEO))
        cv::imshow("imgFrame", trackImg);
    if (_debugMode & Log::debugMode::WAIT_KEY)
        cv::waitKey(0);
}

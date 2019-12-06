#include <utility>

//
// Created by nasrat_v on 11/6/18.
//

#include "../../header/Analyser/ImageProvider.hh"

ImageProvider::ImageProvider(const char *defaultVideoPath,
                            const DebugManager::debugMode &debugMode,
                            const ParamManager::paramMode &paramMode) : _debugMode(debugMode),
                                                                        _paramMode(paramMode)
{
    resetImageNetworkPath();
}

ImageProvider::~ImageProvider() = default;

ImageProvider::statusVideo ImageProvider::openVideo()
{
    bool error = false;

    if (_debugMode & DebugManager::debugMode::WEBCAM)
        _capVideo.open(0);
    else
        _capVideo.open(_videoPath);
    if (!_capVideo.isOpened())
    {
        Error::logError(Error::ErrorType::OPEN_VID, _videoPath);
        error = true;
    }
    else if (!(_debugMode & DebugManager::debugMode::WEBCAM) && 
            (_capVideo.get(CV_CAP_PROP_FRAME_COUNT) < MIN_FRAME_VID))
    {
        Error::logError(Error::ErrorType::TRUNCATED_VID, _videoPath);
        error = true;
    }
    if (error)
        return (statusVideo::ERROR);
    Log::logSomething("Video opened", _videoPath);
    return (statusVideo::OPEN);
}

ImageProvider::statusVideo ImageProvider::initImg(std::vector<cv::Mat> &imgs, size_t nbImgIncr)
{
    if (_paramMode & ParamManager::paramMode::NETWORK_MODE)
        return (initImgNetwork(imgs, nbImgIncr));
    if (_debugMode & DebugManager::debugMode::SRC_AS_IMG)
        return (initImgPng(imgs, nbImgIncr));
    return (initImgVideo(imgs, nbImgIncr));
}

ImageProvider::statusVideo ImageProvider::incrementImg(cv::Mat &nextImage, size_t nbImgIncr)
{
    statusVideo status;

    if (_paramMode & ParamManager::paramMode::NETWORK_MODE)
    {
        while ((status = incrementImgNetwork(nextImage)) == statusVideo::IGNORE_WAIT);
        return (status);
    }
    if (_debugMode & DebugManager::debugMode::SRC_AS_IMG)
        return (incrementImgPng(nextImage, nbImgIncr));
    return (incrementImgVideo(nextImage));
}

ImageProvider::statusVideo ImageProvider::videoContinues()
{
    return ((_capVideo.isOpened()) ? (statusVideo::CONTINUE) : (statusVideo::END));
}

ImageProvider::statusVideo ImageProvider::initImgVideo(std::vector<cv::Mat> &imgs, size_t nbImgIncr)
{
    size_t i = 0;
    cv::Mat imgRead;

    while (i < nbImgIncr)
    {
        _capVideo.read(imgRead);
        imgs.push_back(imgRead);
        i++;
    }
    Log::logSomething("Video started", _videoPath);
    return (statusVideo::START);
}

ImageProvider::statusVideo ImageProvider::incrementImgVideo(cv::Mat &nextImage)
{
    if ((_debugMode & DebugManager::debugMode::WEBCAM) ||
        (_capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < _capVideo.get(CV_CAP_PROP_FRAME_COUNT))
    {
        _capVideo.read(nextImage);
        return (statusVideo::CONTINUE);
    }
    Log::logSomething("Video ended", _videoPath);
    return (statusVideo::END);
}

ImageProvider::statusVideo ImageProvider::initImgPng(std::vector<cv::Mat> &imgs, size_t nbImgIncr)
{
    size_t i = 0;
    cv::Mat imgRead;

    while (i < nbImgIncr)
    {
        if (openImg((IMG_PATH +  std::to_string(i) + IMG_FORMAT), imgRead) == statusVideo::ERROR)
            return (statusVideo::ERROR);
        imgs.push_back(imgRead);
        i++;
    }
    Log::logSomething("Video started", _videoPath);
    return (statusVideo::START);
}

ImageProvider::statusVideo ImageProvider::incrementImgPng(cv::Mat &nextImage, size_t nbImgIncr)
{
    static size_t idPath = nbImgIncr;

    Log::logSomething(("Read source as IMG number: " + std::to_string(idPath)));
    return (openImg((IMG_PATH +  std::to_string(idPath++) + IMG_FORMAT), nextImage));
}

ImageProvider::statusVideo ImageProvider::openImg(const std::string &path, cv::Mat &imgRead)
{
    imgRead = imread(path, cv::IMREAD_COLOR);
    if ((!imgRead.data) || (imgRead.size == 0))
    {
        Error::logError(Error::ErrorType::OPEN_IMG, ("- Cannot read source as IMG: " + path));
        return (statusVideo::ERROR);
    }
    return (statusVideo::OPEN);
}

void ImageProvider::createSampleImgFromVideo()
{
    size_t idPath = 0;
    cv::Mat imgRead;

    while ((_capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < _capVideo.get(CV_CAP_PROP_FRAME_COUNT))
    {
        _capVideo.read(imgRead);
        cv::imwrite((IMG_PATH +  std::to_string(idPath) + IMG_FORMAT), imgRead);
        idPath++;
    }
}

ImageProvider::statusVideo ImageProvider::initImgNetwork(std::vector<cv::Mat> &imgs, size_t nbImgIncr)
{
    size_t i = 0;
    cv::Mat imgRead;
    statusVideo status;

    while (i < nbImgIncr)
    {
        while ((status = incrementImgNetwork(imgRead)) == statusVideo::IGNORE_WAIT);
        if (status == statusVideo::ERROR)
            return (statusVideo::ERROR);
        imgs.push_back(imgRead);
        i++;
    }
    Log::logSomething("Video started", _videoPath);
    return (statusVideo::START);
}

ImageProvider::statusVideo ImageProvider::incrementImgNetwork(cv::Mat &nextImage)
{
    Log::logSomething("Wait for image from network");
    while (!_canReadImage)
        std::this_thread::yield(); // WAIT FOR PATH FROM NETWORK
    Log::logSomething(("Read source from network: " + _imageNetworkPath));
    if (openImg(_imageNetworkPath, nextImage) == statusVideo::ERROR)
    {
        Error::logError(Error::ErrorType::TRUNCATED_IMG_NETWORK, "- Ignore image");
        resetImageNetworkPath();
        return (statusVideo::IGNORE_WAIT);
    }
    resetImageNetworkPath();
    return (statusVideo::OPEN);
}

void ImageProvider::resetImageNetworkPath()
{
    _imageNetworkPath = "";
    _canReadImage = false;
}

void ImageProvider::setImageNetworkPath(const std::string &path)
{
    _imageNetworkPath = path;
}

void ImageProvider::setCanReadImage(bool status)
{
    _canReadImage = status;
}

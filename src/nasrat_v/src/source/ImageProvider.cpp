//
// Created by nasrat_v on 11/6/18.
//

#include "../header/ImageProvider.h"

ImageProvider::ImageProvider(const std::string &videoPath) :  _videoPath(videoPath)
{
}

ImageProvider::~ImageProvider() = default;

ImageProvider::statusVideo ImageProvider::openVideo()
{
    bool error = false;

    _capVideo.open(_videoPath);
    if (!_capVideo.isOpened())
    {
        Error::logError(Error::ErrorType::OPEN_VID, _videoPath);
        error = true;
    }
    else if (_capVideo.get(CV_CAP_PROP_FRAME_COUNT) < MIN_FRAME_VID)
    {
        Error::logError(Error::ErrorType::TRUNCATED_VID, _videoPath);
        error = true;
    }
    if (error)
        return (statusVideo::ERROR);
    Log::logSomething("Video opened", _videoPath);
    return (statusVideo::OPEN);
}

ImageProvider::statusVideo ImageProvider::initImg(cv::Mat &firstImg, cv::Mat &secondImg)
{
    _capVideo.read(firstImg);
    _capVideo.read(secondImg);
    Log::logSomething("Video started", _videoPath);
    return (statusVideo::START);
}

ImageProvider::statusVideo ImageProvider::incrementImg(cv::Mat &nextImage)
{
    if ((_capVideo.get(CV_CAP_PROP_POS_FRAMES) + 1) < _capVideo.get(CV_CAP_PROP_FRAME_COUNT))
    {
        _capVideo.read(nextImage);
        return (statusVideo::CONTINUE);
    }
    Log::logSomething("Video ended", _videoPath);
    return (statusVideo::END);
}

ImageProvider::statusVideo ImageProvider::videoContinues()
{
    if (_capVideo.isOpened())
        return (statusVideo::CONTINUE);
    return (statusVideo::END);
}



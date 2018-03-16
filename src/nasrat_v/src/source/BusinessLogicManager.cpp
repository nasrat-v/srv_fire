//
// Created by nasrat_v on 15/03/18.
//

#include "../header/BusinessLogicManager.hh"

BusinessLogicManager::BusinessLogicManager()
{
}

BusinessLogicManager::~BusinessLogicManager()
{
}

void        BusinessLogicManager::run()
{
    Image   image;
    cv::Mat img;

    img = cv::imread(FILE_PATH);
    if (img.empty())
        Error::logError(Error::ErrorType::OPEN_IMG, FILE_PATH);
    else
    {
        image.setOpencvImage(img);
        _imageAnalyser.setImage(image);
        _imageAnalyser.Analyse();
    }
}
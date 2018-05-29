//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/business_logic_layer/BusinessLogicManager.hh"

BusinessLogicManager::BusinessLogicManager()
{
}

BusinessLogicManager::~BusinessLogicManager()
{
}

/**
 * Entry point of the program.
 * We load an image and then we analyse it
 */
void        BusinessLogicManager::run()
{
    Image   image;
    cv::Mat img;

    img = cv::imread(FILE_PATH, CV_LOAD_IMAGE_GRAYSCALE);
    if (img.empty())
        Error::logError(Error::ErrorType::OPEN_IMG, FILE_PATH);
    else
    {
        image.setOpencvImage(img);
        _imageAnalyser.setImage(image);
        _imageAnalyser.Analyse();
    }
}
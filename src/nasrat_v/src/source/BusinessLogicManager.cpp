//
// Created by nasrat_v on 15/03/18.
//

#include "../header/BusinessLogicManager.hh"

// Transform an image into an array of bytes. This function replaces the creation of the image by the network
uint8_t     **convertImageToByteArray()
{
    cv::Mat                 img;
    std::vector<uint8_t*>   pixel;

    img = cv::imread(FILE_PATH);
    if (img.empty())
    {
        Error::logError(Error::ErrorType::OPEN_IMG, FILE_PATH);
        return (nullptr);
    }
    for (int i = 0; i < img.rows; i++)
        pixel.push_back(img.ptr<uint8_t>(i));
    return (&pixel[0]);
}

BusinessLogicManager::BusinessLogicManager()
{
}

BusinessLogicManager::~BusinessLogicManager()
{
}

void        BusinessLogicManager::run()
{
    Image   image;

    image.createOpencvImage(1680, 1050, convertImageToByteArray());
    _imageAnalyser.setImage(image);
    //_imageAnalyser.Analyse();
}
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
 * We loop on all image in DIR_PATH directory.
 * Then we analyse them
 */
void        BusinessLogicManager::analyseAllFiles()
{
    DIR             *dir;
    struct dirent   *entry;
    std::string     path;

    if (!(dir = opendir(DIR_PATH)))
        Error::logError(Error::ErrorType::OPEN_DIR, DIR_PATH);
    else
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            path = DIR_PATH;
            if (strncmp(entry->d_name, ".", 1) && strncmp(entry->d_name, "..", 2))
            {
                analyse(path + entry->d_name, ImageAnalyser::typeAnalysis::SIMPLE);
                //analyse(path + entry->d_name, ImageAnalyser::typeAnalysis::TRIPLE);
            }
        }
        closedir(dir);
    }
}

/**
 * We load an image and then we analyse it
 * @param file_path Path of the image to analyse
 * @param type_analysis Analysis type to do. SIMPLE for quick analysis, TRIPLE for deep analysis
 */
void        BusinessLogicManager::analyse(const std::string &file_path, const ImageAnalyser::typeAnalysis &type_analysis)
{
    Image           image;
    cv::Mat         img;
    ImageAnalyser   imageAnalyser;

    if (type_analysis == ImageAnalyser::typeAnalysis::SIMPLE)
        img = cv::imread(file_path, CV_LOAD_IMAGE_GRAYSCALE);
    else if (type_analysis == ImageAnalyser::typeAnalysis::TRIPLE)
        img = cv::imread(file_path, CV_LOAD_IMAGE_COLOR);
    if (img.empty())
        Error::logError(Error::ErrorType::OPEN_IMG, file_path);
    else
    {
        image.setImagePath(file_path);
        image.setOpencvImage(img);
        imageAnalyser.setImage(image);
        imageAnalyser.Analyse(type_analysis);
    }
}

/**
 * Entry point of the program.
 */
void        BusinessLogicManager::run()
{
    analyseAllFiles();
}
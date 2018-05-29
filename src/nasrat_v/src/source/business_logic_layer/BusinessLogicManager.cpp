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
                analyse(path + entry->d_name);
        }
        closedir(dir);
    }
}

/**
 * We load an image and then we analyse it
 * @param file_path Path of the image to analyse
 */
void        BusinessLogicManager::analyse(const std::string &file_path)
{
    Image           image;
    cv::Mat         img;
    ImageAnalyser   imageAnalyser;

    img = cv::imread(file_path, CV_LOAD_IMAGE_GRAYSCALE);
    if (img.empty())
        Error::logError(Error::ErrorType::OPEN_IMG, file_path);
    else
    {
        image.setImagePath(file_path);
        image.setOpencvImage(img);
        imageAnalyser.setImage(image);
        imageAnalyser.Analyse();
    }
}

/**
 * Entry point of the program.
 */
void        BusinessLogicManager::run()
{
    analyseAllFiles();
}
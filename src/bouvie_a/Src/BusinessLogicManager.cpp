//
// Created by nasrat_v on 15/03/18.
//

#include "../Include/BusinessLogicManager.hh"

BusinessLogicManager::BusinessLogicManager(int Socket): _network(Socket), _thread(&BusinessLogicManager::run, this)
{
}

BusinessLogicManager::~BusinessLogicManager()
{
    std::cout << "Thread Killed" << std::endl;
    _thread.detach();
}

void        BusinessLogicManager::run()
{
    std::string buff = "";
    
    _network.sendPacket(*new std::string("Well Connected"));
    while ((buff = _network.getPacket()) != "QUIT")
    {
        if ( buff != "")
        {
            /*   Image   image;
             cv::Mat img;
             
             img = cv::imread(FILE_PATH);
             if (img.empty())
             Error::logError(Error::ErrorType::OPEN_IMG, FILE_PATH);
             else
             {
             image.setOpencvImage(img);
             _imageAnalyser.setImage(image);
             _imageAnalyser.Analyse();
             } */
            buff = "";
        }
    }
        std::cout << buff << std::endl;
    delete(this);
}

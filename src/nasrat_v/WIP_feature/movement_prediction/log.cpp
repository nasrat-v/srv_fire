
 #include "movement_prediction.hh"

void printLog(const cv::Point &mousePosition, const cv::Point &predictedMousePosition)
{
    if ((mousePosition.x != predictedMousePosition.x) || (mousePosition.y != predictedMousePosition.y))
    {
        std::cout << "current position        = " << mousePosition.x << ", " << mousePosition.y << std::endl;
        std::cout << "next predicted position = " << predictedMousePosition.x << ", " << predictedMousePosition.y << std::endl;
        std::cout << "--------------------------------------------------" << std::endl;
    }
}
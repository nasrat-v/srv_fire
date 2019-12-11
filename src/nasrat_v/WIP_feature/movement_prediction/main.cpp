
#include "movement_prediction.hh"

int main()
{
    cv::Mat img(HEIGHT_WINDOW, WIDTH_WINDOW, CV_8UC3, cv::Scalar::all(0));
    
    if (drawBackground(img) == ERROR)
        return (ERROR);
    return (mousePredictPosition(img));
}
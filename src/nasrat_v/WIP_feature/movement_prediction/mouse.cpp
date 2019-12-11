
#include "movement_prediction.hh"

cv::Point currentMousePosition(0, 0);

void mouseMoveCallback(int event, int x, int y, __attribute__((unused))int flags, __attribute__((unused))void* userData)
{
    if (event == cv::EVENT_MOUSEMOVE) 
    {
        currentMousePosition.x = x;
        currentMousePosition.y = y;
    }
}

void initTmpPositions(std::vector<cv::Point> &tmpPositions, std::vector<cv::Point> mousePositions)
{
    tmpPositions.clear();
    tmpPositions.swap(mousePositions);
}

int mousePredictPosition(cv::Mat &img)
{
    int nb;
    std::vector<cv::Point> mousePositions;
    std::vector<cv::Point> tmpPositions;
    cv::Point predictedMousePosition;

    cv::setMouseCallback(NAME_WINDOW, mouseMoveCallback);
    while (42) 
    {
        nb = 0;
        mousePositions.push_back(currentMousePosition);
        initTmpPositions(tmpPositions, mousePositions);
        while (nb < NB_PREDICTION)
        {
            predictedMousePosition = predictNextPosition(tmpPositions);
            tmpPositions.push_back(predictedMousePosition);
            printLog(currentMousePosition, predictedMousePosition);
            drawPrediction(img, predictedMousePosition, nb);
            nb++;
        }
        drawMouseCursor(img, currentMousePosition, SCALAR_WHITE);
        cv::imshow(NAME_WINDOW, img);
        cv::waitKey(UTIME_WAIT_KEY);
        if (resetImg(img) == ERROR)
            return (ERROR);
    }
    return (ERROR);
}

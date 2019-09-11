
#include "movement_prediction.hh"

void drawCross(cv::Mat &img, const cv::Point &center, const cv::Scalar &color, int thickness)
{
    cv::line(img, cv::Point(center.x - 5, center.y - 5), cv::Point(center.x + 5, center.y + 5), color, thickness);
    cv::line(img, cv::Point(center.x + 5, center.y - 5), cv::Point(center.x - 5, center.y + 5), color, thickness);
}

void drawMouseCursor(cv::Mat &img, const cv::Point &center, const cv::Scalar &color)
{
    drawCross(img, center, color, THICKNESS_MOUSE_CURSOR);
}

void drawPrediction(cv::Mat &img, const cv::Point &center, int nbPrediction)
{
    cv::Scalar color = cv::Scalar((255.0 - (nbPrediction * (NB_PREDICTION * 5))), 
                                    (0.0 + (nbPrediction * (NB_PREDICTION * 10))), 
                                    (0.0 + (nbPrediction * (NB_PREDICTION * 5))));
    drawCross(img, center, color, THICKNESS_PREDICTION);
}

void resetImg(cv::Mat &img)
{
    img = cv::Scalar::all(0);
}

#include <iostream>
#include <math.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>

# define NAME_WINDOW                "movement_prediction"
# define PATHFILE_BACKGROUND        "input/test_prediction.png"
# define HEIGHT_WINDOW              1000
# define WIDTH_WINDOW               1800
# define NB_OLD_MOVEMENT_USED       12 /* nombre de mouvement dans le passé pris en compte pour calculer la prédiction */
# define NB_PREDICTION              8 /* nombre de prediction dans le futur */
# define UTIME_WAIT_KEY             50
# define THICKNESS_PREDICTION       3
# define THICKNESS_MOUSE_CURSOR     2
# define ERROR                      (~0)
# define SUCCESS                    0

const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar(0.0, 0.0, 255.0);

typedef struct  s_sumOfChanges
{
    short       posX;
    short       posY;
    short       changesLeft;
    short       nbChanges;
}               t_sumOfChanges;

void            mouseMoveCallback(int event, int x, int y, int flags, void* userData);
int             mousePredictPosition(cv::Mat &img);
const cv::Point predictNextPosition(const std::vector<cv::Point> &positions);
void            calculateSumOfChanges(const std::vector<cv::Point> &positions, t_sumOfChanges &sumOfChanges);
void            drawCross(cv::Mat &img, const cv::Point &center, const cv::Scalar &color, int thickness);
void            drawMouseCursor(cv::Mat &img, const cv::Point &center, const cv::Scalar &color);
void            drawPrediction(cv::Mat &img, const cv::Point &center, int nbPrediction);
int             drawBackground(cv::Mat &img);
int             resetImg(cv::Mat &img);
void            printLog(const cv::Point &mousePosition, const cv::Point &predictedMousePosition);

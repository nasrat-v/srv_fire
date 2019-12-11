
#include "movement_prediction.hh"

void calculateSumOfChanges(const std::vector<cv::Point> &positions, t_sumOfChanges &sumOfChanges)
{
    sumOfChanges.posX += ((positions[sumOfChanges.changesLeft - 1].x - positions[sumOfChanges.changesLeft - 2].x) * sumOfChanges.nbChanges);
    sumOfChanges.posY += ((positions[sumOfChanges.changesLeft - 1].y - positions[sumOfChanges.changesLeft - 2].y) * sumOfChanges.nbChanges);
    sumOfChanges.changesLeft--;
    sumOfChanges.nbChanges++;
}

const cv::Point predictNextPosition(const std::vector<cv::Point> &positions)
{
    short deltaX;
    short deltaY;
    t_sumOfChanges sumOfChanges;
    cv::Point predictedNextPosition;
    auto numPositions = (short)positions.size();
    sumOfChanges.posX = 0;
    sumOfChanges.changesLeft = numPositions;
    sumOfChanges.posY = 0;
    sumOfChanges.nbChanges = 0;

    if (numPositions == 1)
    {
        predictedNextPosition.x = positions.back().x;
        predictedNextPosition.y = positions.back().y;
    }
    else if (numPositions > 1 && numPositions < NB_OLD_MOVEMENT_USED)
    {
        while ((sumOfChanges.changesLeft - 2) >= 0)
            calculateSumOfChanges(positions, sumOfChanges);
    }
    else
    {
        while (sumOfChanges.changesLeft > (numPositions - (NB_OLD_MOVEMENT_USED - 1)))
            calculateSumOfChanges(positions, sumOfChanges);
    }
    deltaX = (short)std::round((float)sumOfChanges.posX / ((sumOfChanges.nbChanges * 2) - 1));
    deltaY = (short)std::round((float)sumOfChanges.posY / ((sumOfChanges.nbChanges * 2) - 1));
    predictedNextPosition.x = (positions.back().x + deltaX);
    predictedNextPosition.y = (positions.back().y + deltaY);
    return (predictedNextPosition);
}







/*
const cv::Point predictNextPosition(const std::vector<cv::Point> &positions) 
{
    cv::Point predictedPosition;
    int numPositions;

    numPositions = positions.size();
    if (numPositions == 0)
        std::cout << "error, predictNextPosition was called with zero points\n";
    else if (numPositions == 1) 
        return(positions[0]);
    else if (numPositions == 2) 
    {
        int deltaX = positions[1].x - positions[0].x;
        int deltaY = positions[1].y - positions[0].y;

        predictedPosition.x = positions.back().x + deltaX;
        predictedPosition.y = positions.back().y + deltaY;
    } 
    else if (numPositions == 3) 
    {
        int sumOfXChanges = ((positions[2].x - positions[1].x) * 2) +
            ((positions[1].x - positions[0].x) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 3.0);

        int sumOfYChanges = ((positions[2].y - positions[1].y) * 2) +
            ((positions[1].y - positions[0].y) * 1);

        int deltaY = (int)std::round((float)sumOfYChanges / 3.0);

        predictedPosition.x = positions.back().x + deltaX;
        predictedPosition.y = positions.back().y + deltaY;
    } 
    else if (numPositions == 4) 
    {
        int sumOfXChanges = ((positions[3].x - positions[2].x) * 3) +
            ((positions[2].x - positions[1].x) * 2) +
            ((positions[1].x - positions[0].x) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 6.0);

        int sumOfYChanges = ((positions[3].y - positions[2].y) * 3) +
            ((positions[2].y - positions[1].y) * 2) +
            ((positions[1].y - positions[0].y) * 1);

        int deltaY = (int)std::round((float)sumOfYChanges / 6.0);

        predictedPosition.x = positions.back().x + deltaX;
        predictedPosition.y = positions.back().y + deltaY;
    } 
    else if (numPositions >= 5) 
    {
        int sumOfXChanges = ((positions[numPositions - 1].x - positions[numPositions - 2].x) * 4) +
            ((positions[numPositions - 2].x - positions[numPositions - 3].x) * 3) +
            ((positions[numPositions - 3].x - positions[numPositions - 4].x) * 2) +
            ((positions[numPositions - 4].x - positions[numPositions - 5].x) * 1);

        int deltaX = (int)std::round((float)sumOfXChanges / 10.0);

        int sumOfYChanges = ((positions[numPositions - 1].y - positions[numPositions - 2].y) * 4) +
            ((positions[numPositions - 2].y - positions[numPositions - 3].y) * 3) +
            ((positions[numPositions - 3].y - positions[numPositions - 4].y) * 2) +
            ((positions[numPositions - 4].y - positions[numPositions - 5].y) * 1);

        int deltaY = (int)std::round((float)sumOfYChanges / 10.0);

        predictedPosition.x = positions.back().x + deltaX;
        predictedPosition.y = positions.back().y + deltaY;
    } 
    else 
    {
        // should never get here
    }
    return (predictedPosition);
}*/

// Blob.cpp

#include "Blob.h"

#include <iostream>

///////////////////////////////////////////////////////////////////////////////////////////////////
Blob::Blob(std::vector<cv::Point> _contour) {

    currentContour = _contour;

    currentBoundingRect = cv::boundingRect(currentContour);

    cv::Point currentCenter;

    currentCenter.x = (currentBoundingRect.x + currentBoundingRect.x + currentBoundingRect.width) / 2;
    currentCenter.y = (currentBoundingRect.y + currentBoundingRect.y + currentBoundingRect.height) / 2;

    centerPositions.push_back(currentCenter);

    dblCurrentDiagonalSize = sqrt(pow(currentBoundingRect.width, 2) + pow(currentBoundingRect.height, 2));

    dblCurrentAspectRatio = (float)currentBoundingRect.width / (float)currentBoundingRect.height;

    blnStillBeingTracked = true;
    blnCurrentMatchFoundOrNewBlob = true;

    intNumOfConsecutiveFramesWithoutAMatch = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Blob::predictNextPosition(void)
{
    int deltaX;
    int deltaY;
    int n = 0;
    int sumOfXChanges = 0;
    int sumOfYChanges = 0;
    int numPositions = (int)centerPositions.size();
    int i = numPositions;

    if (numPositions == 1)
    {
        predictedNextPosition.x = centerPositions.back().x;
        predictedNextPosition.y = centerPositions.back().y;
    }
    else if (numPositions > 1 && numPositions < 5)
    {
	while ((i - 2) >= 0)
	{
	    sumOfXChanges += ((centerPositions[i - 2].x - centerPositions[i - 1].x) * n);
	    sumOfYChanges += ((centerPositions[i - 2].y - centerPositions[i - 1].y) * n);
	    i -= 1;
	    n += 1;
	}
    }
    else
    {
	while (i > (numPositions - (5 - 1)))
	{
	    sumOfXChanges += ((centerPositions[i - 2].x - centerPositions[i - 1].x) * n);
	    sumOfYChanges += ((centerPositions[i - 2].y - centerPositions[i - 1].y) * n);
	    i -= 1;
	    n += 1;
	}
    }
    deltaX = (int)std::round((float)sumOfXChanges / ((n * 2) - 1));
    deltaY = (int)std::round((float)sumOfYChanges / ((n * 2) - 1));
    predictedNextPosition.x = centerPositions.back().x + deltaX;
    predictedNextPosition.y = centerPositions.back().y + deltaY;
    std::cout << "predicted X =\n" << predictedNextPosition.x << std::endl;
    std::cout << "predicted Y =\n" << predictedNextPosition.y << std::endl;
}

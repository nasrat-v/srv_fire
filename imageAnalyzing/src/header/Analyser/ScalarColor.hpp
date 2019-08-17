//
// Created by nasrat_v on 5/17/19.
//

#ifndef OPENCV_SRV_SCALARCOLOR_HPP
#define OPENCV_SRV_SCALARCOLOR_HPP

# define SCALAR_BLACK   cv::Scalar(0.0, 0.0, 0.0)
# define SCALAR_WHITE   cv::Scalar(255.0, 255.0, 255.0)
# define SCALAR_YELLOW  cv::Scalar(0.0, 255.0, 255.0)
# define SCALAR_GREEN   cv::Scalar(0.0, 200.0, 0.0)
# define SCALAR_RED     cv::Scalar(0.0, 0.0, 255.0)
# define SCALAR_BLUE    cv::Scalar(255.0, 0.0, 0.0)
# define SCALAR_ORANGE  cv::Scalar(0.0 ,165.0 , 255.0)

# define WHITE_RANGE     ScalarColor::t_colorRange { "White Range", cv::Scalar(250, 250, 250), cv::Scalar(255, 255, 255), SCALAR_WHITE }
# define RED_RANGE       ScalarColor::t_colorRange { "Red Range", cv::Scalar(0, 150, 100), cv::Scalar(10, 255, 255), SCALAR_RED }
# define ORANGE_RANGE    ScalarColor::t_colorRange { "Orange Range", cv::Scalar(11, 150, 100), cv::Scalar(20, 255, 255), SCALAR_ORANGE }
# define YELLOW_RANGE    ScalarColor::t_colorRange { "Yellow Range", cv::Scalar(21, 150, 100), cv::Scalar(30, 255, 255), SCALAR_YELLOW }

#include <string>
#include <iostream>
#include <opencv2/core/types.hpp>

class ScalarColor
{
public:

    typedef struct  s_colorRange
    {
        std::string _nameRange;
        cv::Scalar  _firstRange;
        cv::Scalar  _secondRange;
        cv::Scalar  _displayColor;

        bool operator<(const s_colorRange &colorRange) const
        {
            return (_nameRange < colorRange._nameRange);
        }
    }               t_colorRange;
};


#endif //OPENCV_SRV_SCALARCOLOR_HPP

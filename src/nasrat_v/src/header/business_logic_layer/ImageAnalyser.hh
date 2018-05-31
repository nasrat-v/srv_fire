//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_IMAGEANALYSER_HH__
# define __OPENCV_TEST_IMAGEANALYSER_HH__

# define FLAME_RED          255 // WHITE
# define FLAME_GREEN        255
# define FLAME_BLUE         255
# define VERY_HOT_MIN_RED   150 // YELLOW
# define VERY_HOT_MIN_GREEN 150
# define VERY_HOT_MIN_BLUE  0
# define VERY_HOT_MAX_RED   255
# define VERY_HOT_MAX_GREEN 255
# define VERY_HOT_MAX_BLUE  50
# define HOT_MIN_RED        150 // RED
# define HOT_MIN_GREEN      0
# define HOT_MIN_BLUE       0
# define HOT_MAX_RED        255
# define HOT_MAX_GREEN      50
# define HOT_MAX_BLUE       50
# define SENSIBILITY_COLOR  200
# define TRANSFORM_TO_COLOR 255
# define BINARY_FILE_PATH   "../output/image/binary.png"

#include <ctime>
#include <string>
#include "../data_transfert_object/Image.hh"
#include "ZoneAnalyser.hh"

class ImageAnalyser
{
public:
    ImageAnalyser();
    ~ImageAnalyser();

    enum class          typeAnalysis
    {
        SIMPLE,
        TRIPLE
    };

    const Image         &getImage() const;
    void                setImage(const Image &image);
    void                Analyse(const typeAnalysis &type_analysis);

private:
    /* Methods */
    void                transformToBinary(cv::Mat &img);
    double              defineZone(cv::Mat neg_img);
    bool                isPattern(Pixel &pixel);
    void                printPixel(const Pixel &pixel);
    const char          *getTypeAnalysisString(const typeAnalysis &type) const;

    /* Attributes */
    Image               _image;
    ZoneAnalyser        _zoneAnalyser;
};

#endif /* !__OPENCV_TEST_IMAGEANALYSER_HH__ */

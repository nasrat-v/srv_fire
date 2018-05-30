//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_IMAGEANALYSER_HH__
# define __OPENCV_TEST_IMAGEANALYSER_HH__

# define MAX_RED            0
# define MAX_BLUE           0
# define MAX_GREEN          0
# define NEGATIVE_FILE_PATH "../output/image/negative.png"

#include "../data_transfert_object/Image.hh"
#include "ZoneAnalyser.hh"

class ImageAnalyser
{
public:
    ImageAnalyser();
    ~ImageAnalyser();

    const Image     &getImage() const;
    void            setImage(const Image &image);
    void            Analyse();

private:
    /* Methods */
    cv::Mat         transformToNegative(cv::Mat img);
    void            defineZone(cv::Mat neg_img);
    bool            isPattern(const Pixel &pixel);
    void            printPixel(const Pixel &pixel);

    /* Attributes */
    Image           _image;
    ZoneAnalyser    _zoneAnalyser;
};

#endif /* !__OPENCV_TEST_IMAGEANALYSER_HH__ */

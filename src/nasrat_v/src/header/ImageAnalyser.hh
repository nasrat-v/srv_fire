//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_IMAGEANALYSER_HH__
# define __OPENCV_TEST_IMAGEANALYSER_HH__

# define MAX_RED    255
# define MIN_RED    100
# define MAX_BLUE   200
# define MIN_BLUE   0
# define MAX_GREEN  200
# define MIN_GREEN  0
# define TEMP_FIRE  60

#include "Image.hh"
#include "ZoneAnalyser.hh"

class ImageAnalyser
{
public:
    ImageAnalyser();
    ~ImageAnalyser();

    const Image     &getImage() const;
    void            setImage(const Image &image);
    void            Analyse(int y, int x, float *palette);

private:
    /* Methods */
    void            defineZone();
    bool            isPattern(const Pixel &pixel);
    void            printPixel(const Pixel &pixel);

    /* Attributes */
    Image           _image;
    ZoneAnalyser    _zoneAnalyser;
};

#endif /* !__OPENCV_TEST_IMAGEANALYSER_HH__ */

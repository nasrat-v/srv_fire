//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_IMAGE_HH__
# define __OPENCV_TEST_IMAGE_HH__

#include <iostream>
#include <list>
#include <map>
#include <opencv2/opencv.hpp>
#include "Packet.hh"
#include "Pixel.hh"

class Image : public Packet
{
public:
    Image();
    virtual ~Image();
    typedef float                       TEMP;

    const std::list<Pixel>              &getPixelsList() const;
    const std::map<Pixel::t_rgb, TEMP>  &getColorsPalette() const;
    const cv::Mat                       &getOpencvImage() const;
    void                                addPixel(const Pixel &pixel);
    void                                addColorToPalette(const Pixel::t_rgb &color, const TEMP &temp);
    void                                createOpencvImage(int height, int width, uint8_t **data);

private:
    cv::Mat                             _opencvImage;
    std::list<Pixel>                    _pixelsList;
    std::map<Pixel::t_rgb, TEMP>        _colorsPalette;
};

#endif /* !__OPENCV_TEST_IMAGE_HH__ */

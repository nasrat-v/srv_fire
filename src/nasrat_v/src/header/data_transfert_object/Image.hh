//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_IMAGE_HH__
# define __OPENCV_TEST_IMAGE_HH__

#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include "Packet.hh"
#include "Pixel.hh"

class Pixel;

class Image : public Packet
{
public:
    Image();
    virtual ~Image();
    typedef float                       TEMP;

    const std::map<Pixel::t_pos, Pixel> &getPixelsPosMap() const;
    const std::map<Pixel::t_rgb, TEMP>  &getColorsPalette() const;
    const cv::Mat                       &getOpencvImage() const;
    const std::string                   &getImagePath() const;
    void                                addPixel(const Pixel &pixel);
    void                                addColorToPalette(const Pixel::t_rgb &color, const TEMP &temp);
    void                                setOpencvImage(const cv::Mat &image);
    void                                setImagePath(const std::string &path);

private:
    cv::Mat                             _opencvImage;
    std::string                         _imagePath;
    std::map<Pixel::s_pos, Pixel>       _pixelsPosMap;
    std::map<Pixel::t_rgb, TEMP>        _colorsPalette;
};

#endif /* !__OPENCV_TEST_IMAGE_HH__ */

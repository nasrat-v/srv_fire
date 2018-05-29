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

    const std::map<Pixel::t_pos, Pixel> &getPixelsPosMap() const;
    const cv::Mat                       &getOpencvImage() const;
    void                                addPixel(const Pixel &pixel);
    void                                setOpencvImage(const cv::Mat &image);

private:
    cv::Mat                             _opencvImage;
    std::map<Pixel::s_pos, Pixel>       _pixelsPosMap;
};

#endif /* !__OPENCV_TEST_IMAGE_HH__ */

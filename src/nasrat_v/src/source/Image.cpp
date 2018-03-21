//
// Created by nasrat_v on 15/03/18.
//

#include "../header/Image.hh"

Image::Image() : Packet()
{
}

Image::~Image()
{
}

const std::map<Pixel::t_pos, Pixel>     &Image::getPixelsPosMap() const
{
    return (_pixelsPosMap);
}

const cv::Mat   &Image::getOpencvImage() const
{
    return (_opencvImage);
}

void        Image::addPixel(const Pixel &pixel)
{
    _pixelsPosMap.insert(std::make_pair(pixel.getPos(), pixel));
}

void        Image::setOpencvImage(const cv::Mat &image)
{
    _opencvImage = image;
}

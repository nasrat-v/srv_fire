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

const std::list<Pixel>  &Image::getPixelsList() const
{
    return (_pixelsList);
}

const std::map<Pixel::t_rgb, Image::TEMP>   &Image::getColorsPalette() const
{
    return (_colorsPalette);
}

const cv::Mat   &Image::getOpencvImage() const
{
    return (_opencvImage);
}

void        Image::addPixel(const Pixel &pixel)
{
    _pixelsList.push_back(pixel);
}

void        Image::addColorToPalette(const Pixel::t_rgb &color, const Image::TEMP &temp)
{
    _colorsPalette.insert(std::make_pair(color, temp));
}

void        Image::setOpencvImage(const cv::Mat &image)
{
    _opencvImage = image;
}

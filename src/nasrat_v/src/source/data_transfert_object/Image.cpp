//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/data_transfert_object/Image.hh"

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

const std::map<Pixel::t_rgb, Image::TEMP>   &Image::getColorsPalette() const
{
    return (_colorsPalette);
}

const cv::Mat   &Image::getOpencvImage() const
{
    return (_opencvImage);
}

const std::string   &Image::getImagePath() const
{
    return (_imagePath);
}

void        Image::addPixel(const Pixel &pixel)
{
    _pixelsPosMap.insert(std::make_pair(pixel.getPos(), pixel));
}

void        Image::addColorToPalette(const Pixel::t_rgb &color, const Image::TEMP &temp)
{
    _colorsPalette.insert(std::make_pair(color, temp));
}

void        Image::setOpencvImage(const cv::Mat &image)
{
    _opencvImage = image;
}

void        Image::setImagePath(const std::string &path)
{
    _imagePath = path;
}

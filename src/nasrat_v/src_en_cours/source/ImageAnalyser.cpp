//
// Created by nasrat_v on 15/03/18.
//

#include "../header/ImageAnalyser.hh"

ImageAnalyser::ImageAnalyser()
{
}

ImageAnalyser::~ImageAnalyser()
{
}

const Image     &ImageAnalyser::getImage() const
{
    return (_image);
}

void            ImageAnalyser::setImage(const Image &image)
{
    _image = image;
}

bool            ImageAnalyser::isPattern(const Pixel &pixel)
{
    Pixel::t_rgb    rgb = pixel.getColors();

    return (rgb._red >= MIN_RED && rgb._red <= MAX_RED &&
            rgb._green >= MIN_GREEN && rgb._green <= MAX_GREEN &&
            rgb._blue >= MIN_BLUE && rgb._blue <= MAX_BLUE);
}

void            ImageAnalyser::printPixel(const Pixel &pixel)
{
    Pixel::t_rgb    rgb = pixel.getColors();

    std::cout << "red: " << (int)rgb._red << std::endl;
    std::cout << "green: " << (int)rgb._green << std::endl;
    std::cout << "blue: " << (int)rgb._blue << std::endl << std::endl;
}

void            ImageAnalyser::defineZone()
{
    Pixel       pixel;
    int         id_zone;
    uint8_t     *pixels;
    cv::Mat     img = _image.getOpencvImage();

    for (int y = 0; y < img.rows; ++y)
    {
        pixels = img.ptr<uint8_t>(y);
        for (int x = 0; x < img.cols; ++x)
        {
            pixel.setColors(*pixels++, *pixels++, *pixels++);
            pixel.setPosition(y, x);
            if (isPattern(pixel))
            {
                if ((id_zone = _zoneAnalyser.findExistingZone(pixel)) == ZONE_NOT_FIND)
                    _zoneAnalyser.createNewZone(pixel);
                else
                    _zoneAnalyser.addPixelToZone(pixel, id_zone);
            }
        }
    }
    std::cout << _zoneAnalyser.getNbZone() << std::endl;
    _zoneAnalyser.printBorderOnZone(img);
}

void            ImageAnalyser::Analyse()
{
    defineZone();
    /*Pixel       pixel;
    uint8_t     *pixels;
    cv::Mat     img = _image.getOpencvImage();

    for (int i = 0; i < img.rows; ++i)
    {
        pixels = img.ptr<uint8_t>(i);
        for (int j = 0; j < img.cols; ++j)
        {
            pixel.setColors(*pixels++, *pixels++, *pixels++);
            /* printPixel(pixel); */
            /*if (isPattern(pixel))
            {
                std::cout << "[OK] Fire detected" << std::endl;
                return;
            }
        }
    }
    std::cout << "[KO] No fire detected" << std::endl;*/
}

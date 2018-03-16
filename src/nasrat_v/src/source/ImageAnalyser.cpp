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

void            ImageAnalyser::Analyse()
{
    uint8_t     red;
    uint8_t     green;
    uint8_t     blue;
    uint8_t     *pixel;
    cv::Mat     img = _image.getOpencvImage();

    for (int i = 0; i < img.rows; ++i)
    {
        pixel = img.ptr<uint8_t>(i);
        for (int j = 0; j < img.cols; ++j)
        {
            blue = *pixel++;
            green = *pixel++;
            red = *pixel++;
            std::cout << "red: " << (int)red << std::endl << "green: " << (int)green << std::endl << "blue: " << (int)blue << std::endl << std::endl;
            if (red >= MIN_RED && red <= MAX_RED && green >= MIN_GREEN && green <= MAX_GREEN && blue >= MIN_BLUE && blue <= MAX_BLUE)
            {
                std::cout << "[OK] Fire detected" << std::endl;
                return;
            }
        }
    }
    std::cout << "[KO] No fire detected" << std::endl;
}

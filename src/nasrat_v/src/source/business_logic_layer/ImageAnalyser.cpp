//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/business_logic_layer/ImageAnalyser.hh"

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

/**
 * Debug function. Print RGB color of a pixel
 * @param pixel Pixel to print
 */
void            ImageAnalyser::printPixel(const Pixel &pixel)
{
    Pixel::t_rgb    rgb = pixel.getColors();

    std::cout << "red: " << (int)rgb._red << std::endl;
    std::cout << "green: " << (int)rgb._green << std::endl;
    std::cout << "blue: " << (int)rgb._blue << std::endl << std::endl;
}

/**
 * Check if a pixel correspond to the fire pattern
 * @param pixel The pixel to check
 * @return True if pixel is fire, False if not
 */
bool            ImageAnalyser::isPattern(Pixel &pixel)
{
    Pixel::t_rgb    rgb = pixel.getColors();

    if ((rgb._red == FLAME_RED) && (rgb._green == FLAME_GREEN) && (rgb._blue == FLAME_BLUE))
    {
        pixel.setTypePixel(Pixel::typeTemp::FLAME);
        return (true);
    }
    else if ((rgb._red >= VERY_HOT_MIN_RED && rgb._red <= VERY_HOT_MAX_RED) &&
             (rgb._green >= VERY_HOT_MIN_GREEN && rgb._green <= VERY_HOT_MAX_GREEN) &&
             (rgb._blue >= VERY_HOT_MIN_BLUE && rgb._blue <= VERY_HOT_MAX_BLUE))
    {
        pixel.setTypePixel(Pixel::typeTemp::VERY_HOT);
        return (true);
    }
    else if ((rgb._red >= HOT_MIN_RED && rgb._red <= HOT_MAX_RED) &&
             (rgb._green >= HOT_MIN_GREEN && rgb._green <= HOT_MAX_GREEN) &&
             (rgb._blue >= HOT_MIN_BLUE && rgb._blue <= HOT_MAX_BLUE))
    {
        pixel.setTypePixel(Pixel::typeTemp::HOT);
        return (true);
    }
    pixel.setTypePixel(Pixel::typeTemp::NO_TYPE);
    return (false);
}

/**
 *  Define all fire zone present on the image.
 *  If a pixel correspond to the fire pattern color,
 *  we check all pixel around it with a sonar algorithm and then we add it to a fire zone
 * @param neg_img Image to analyse in negative
 */
void            ImageAnalyser::defineZone(cv::Mat neg_img)
{
    Pixel       pixel;
    int         id_zone;
    uint8_t     *pixels;

    for (int y = 0; y < neg_img.rows; ++y)
    {
        pixels = neg_img.ptr<uint8_t>(y);
        for (int x = 0; x < neg_img.cols; ++x)
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
    Log::logSomething("Number of fire's zone detected: " + std::to_string(_zoneAnalyser.getNbZone()));
    _zoneAnalyser.printBorderOnZone(_image.getImagePath());
}

/**
 * Transform an (A)RGB image into it's binary form
 * @param img The image source
 */
void            ImageAnalyser::transformToBinary(cv::Mat &img)
{
    cv::threshold(img, img, SENSIBILITY_COLOR, TRANSFORM_TO_COLOR, cv::THRESH_BINARY);
    cv::imwrite(BINARY_FILE_PATH, img);
    img = cv::imread(BINARY_FILE_PATH, CV_LOAD_IMAGE_COLOR);
}

/**
 * Entry point of the class. Launch the analysis
 */
void            ImageAnalyser::Analyse()
{
    cv::Mat     img = _image.getOpencvImage();

    transformToBinary(img);
    defineZone(img);
}

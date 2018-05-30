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
bool            ImageAnalyser::isPattern(const Pixel &pixel)
{
    Pixel::t_rgb    rgb = pixel.getColors();

    return ((rgb._red == MAX_RED) &&
            (rgb._green == MAX_GREEN) &&
            (rgb._blue == MAX_BLUE));
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
    _zoneAnalyser.printBorderOnZone(_image.getOpencvImage(), _image.getImagePath());
}

/**
 * Transform an (A)RGB image into it's negative form
 * @param img The image source
 * @return The negative image
 */
cv::Mat         ImageAnalyser::transformToNegative(cv::Mat img)
{
    cv::threshold(img, img, 200, 255, cv::THRESH_BINARY);
    for (int i = 0; i < img.rows; i++)
    {
        for (int j = 0; j < img.cols; j++)
            img.at<uchar>(i, j) = ((uchar)255 - img.at<uchar>(i, j));
    }
    cv::imwrite(NEGATIVE_FILE_PATH, img);
    img = cv::imread(NEGATIVE_FILE_PATH, CV_LOAD_IMAGE_COLOR);
    return (img);
}

/**
 * Entry point of the class. Launch the analysis
 */
void            ImageAnalyser::Analyse()
{
    cv::Mat     img = _image.getOpencvImage();

    img = transformToNegative(img);
    defineZone(img);
}

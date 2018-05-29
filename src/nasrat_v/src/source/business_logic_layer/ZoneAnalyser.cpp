//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/business_logic_layer/ZoneAnalyser.hh"

ZoneAnalyser::ZoneAnalyser()
{
}

ZoneAnalyser::~ZoneAnalyser()
{
}

const std::vector<Zone> &ZoneAnalyser::getZones() const
{
    return (_zones);
}

size_t         ZoneAnalyser::getNbZone() const
{
    return (_zones.size());
}

void            ZoneAnalyser::addZone(const Zone &zone)
{
    _zones.push_back(zone);
}

void            ZoneAnalyser::createNewZone(const Pixel &pixel)
{
    Zone        zone;

    zone.addPixel(pixel);
    addZone(zone);
}

void            ZoneAnalyser::addPixelToZone(Pixel &pixel, int id_zone)
{
    _zones[id_zone].addPixel(pixel);
}

void            ZoneAnalyser::findBorderOfRectangle(cv::Point &point_top_left, cv::Point &point_bottom_right,
                                                    const Pixel::t_pos &leftTop, const Pixel::t_pos &rightBottom)
{
    point_top_left.x = leftTop._x;
    point_bottom_right.x = rightBottom._x;
    point_top_left.y = leftTop._y;
    point_bottom_right.y = rightBottom._y;
}

/**
 * Debug function.
 * Thanks to the border of each fire zone, we recreate an image with the border in color.
 * The color of the border is defined by the macro COLOR_SCALAR_BORDER.
 * We recreate a color image and a black/white image
 * @param source_image The color image we analysed
 */
void            ZoneAnalyser::printBorderOnZone(const cv::Mat &opencv_image_loaded, const std::string &base_image_path)
{
    int                                 id_zone = 0;
    cv::Mat                             neg_dest_image = opencv_image_loaded;
    cv::Mat                             dest_image = cv::imread(base_image_path);
    std::vector<Zone>::iterator         zone_it = _zones.begin();
    cv::Point                           point_top_left;
    cv::Point                           point_bottom_right;

    while (zone_it < _zones.end())
    {
        findBorderOfRectangle(point_top_left, point_bottom_right, zone_it->getLeftTopPos(), zone_it->getRightBottomPos());
        cv::rectangle(dest_image, point_top_left, point_bottom_right, COLOR_SCALAR_BORDER, 2);
        cv::rectangle(neg_dest_image, point_top_left, point_bottom_right, COLOR_SCALAR_BORDER, 2);
        //std::cout << "id_zone: " << id_zone << "\tx: " << zone_it->getLeftTopPos()._x << "\ty: " << zone_it->getLeftTopPos()._y;
        //std::cout << "\t to -> \tx: " << zone_it->getRightBottomPos()._x << "\ty: " << zone_it->getRightBottomPos()._y << std::endl << std::endl;
        ++zone_it;
        id_zone++;
    }
    cv::imshow("negative_test", neg_dest_image);
    cv::imshow("test", dest_image);
    cv::waitKey(0);
}

/**
 * Define the border of a fire zone to have rectangle
 * @param id_zone Id of the fire zone to define
 * @param y Y position of the fire zone to define
 * @param x X position of the fire zone to define
 */
void            ZoneAnalyser::findBorderOfPixel(int id_zone, int y, int x)
{
    if (x < _zones[id_zone].getLeftTopPos()._x)
        _zones[id_zone].setLowerX(x);
    if (x > _zones[id_zone].getRightBottomPos()._x)
        _zones[id_zone].setBiggerX(x);
    if (y < _zones[id_zone].getLeftTopPos()._y)
        _zones[id_zone].setLowerY(y);
    if (y > _zones[id_zone].getRightBottomPos()._y)
        _zones[id_zone].setBiggerY(y);
}

/**
 * Find the fire zone to which the pixel belongs with it's position
 * @param y Y position of the pixel to check
 * @param x X position of the pixel to check
 * @return If the pixel belongs to a fire zone we return the zone's ID. If not we return the macro ZONE_NOT_FIND
 * @todo Possibility to improve the speed by keeping a pointer of its zone on each pixel. We recover the pixel on the map with its position to have its area.
 */
int             ZoneAnalyser::findZoneByPixelPos(int y, int x)
{
    int                                 id_zone = 0;
    Pixel::t_pos                        pos { y, x };
    std::map<Pixel::t_pos, Pixel>       pixels;
    std::vector<Zone>::iterator         zone_it = _zones.begin();

    while (zone_it < _zones.end())
    {
        pixels = zone_it->getPixelsPosMap();
        if (pixels.find(pos) != pixels.end())
            return (id_zone);
        ++zone_it;
        id_zone++;
    }
    return (ZONE_NOT_FIND);
}

/**
 * Check with a sonar algorithm if a pixel belongs to a fire zone.
 * To verify this, we define a deepness to check with the macro DEEPNESS_SONAR
 * We gonna verify all pixels around our pixel at DEEPNESS_SONAR deepness
 * @param pixel The pixel to check
 * @return If the pixel belongs to a fire zone we return the zone's ID. If not we return the macro ZONE_NOT_FIND
 */
int             ZoneAnalyser::findExistingZone(const Pixel &pixel)
{
    int             n;
    int             id_zone;
    Pixel::t_pos    pos = pixel.getPos();
    int             i = (pos._y - DEEPNESS_SONAR);

    while (i <= (pos._y + DEEPNESS_SONAR))
    {
        n = (pos._x - DEEPNESS_SONAR);
        while (n <= (pos._x + DEEPNESS_SONAR))
        {
            if ((i >= 0 && n >= 0) &&
                    (id_zone = findZoneByPixelPos(i, n)) != ZONE_NOT_FIND)
            {
                findBorderOfPixel(id_zone, pos._y, pos._x);
                return (id_zone);
            }
            n++;
        }
        i++;
    }
    return (ZONE_NOT_FIND);
}

void            ZoneAnalyser::Analyse()
{
}

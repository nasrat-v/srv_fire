//
// Created by nasrat_v on 15/03/18.
//

#include "../header/ZoneAnalyser.hh"

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
    //if (id_zone == 3)
    //    std::cout << "id_zone: " << id_zone << "\tx: " << pixel.getPos()._x << "\ty: " << pixel.getPos()._y << std::endl << std::endl;
}


void            ZoneAnalyser::findBorderOfRectangle(cv::Point &point_top_left, cv::Point &point_bottom_right,
                                                    const Pixel::t_pos &leftTop, const Pixel::t_pos &rightBottom)
{
    /*if ((leftTop._x - 3) >= 0)
        point_top_left.x = (leftTop._x - 3);
    else*/
        point_top_left.x = leftTop._x;
    /*if ((rightBottom._x + 3) <= 1080)
        point_bottom_right.x = (rightBottom._x + 3);
    else*/
        point_bottom_right.x = rightBottom._x;
    /*if ((leftTop._y - 3) >= 0)
        point_top_left.y = (leftTop._y - 3);
    else*/
        point_top_left.y = leftTop._y;
    /*if ((rightBottom._y + 3) <= 1920)
        point_bottom_right.y = (rightBottom._y + 3);
    else*/
        point_bottom_right.y = rightBottom._y;
}

void            ZoneAnalyser::printBorderOnZone(const cv::Mat &source_image)
{
    int                                 id_zone = 0;
    cv::Mat                             dest_image = source_image;
    std::vector<Zone>::iterator         zone_it = _zones.begin();
    cv::Point                           point_top_left;
    cv::Point                           point_bottom_right;

    cv::namedWindow("test_pattern", cv::WINDOW_AUTOSIZE);
    while (zone_it < _zones.end())
    {
        findBorderOfRectangle(point_top_left, point_bottom_right, zone_it->getLeftTopPos(), zone_it->getRightBottomPos());
        cv::rectangle(dest_image, point_top_left, point_bottom_right, cv::Scalar(0, 200, 0), 2);
        //std::cout << "id_zone: " << id_zone << "\tx: " << zone_it->getLeftTopPos()._x << "\ty: " << zone_it->getLeftTopPos()._y;
        //std::cout << "\t to -> \tx: " << zone_it->getRightBottomPos()._x << "\ty: " << zone_it->getRightBottomPos()._y << std::endl << std::endl;
        ++zone_it;
        id_zone++;
    }
    cv::imshow("test_pattern", dest_image);
    cv::waitKey(0);
}

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

// Possibility to improve the speed by keeping a pointer of its zone on each pixel.
// We recover the pixel on the map with its position to have its area.
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

int             ZoneAnalyser::findExistingZone(const Pixel &pixel)
{
    int             n;
    int             id_zone;
    Pixel::t_pos    pos = pixel.getPos();
    int             i = (pos._y - OFFSET_PIXEL);

    while (i <= (pos._y + OFFSET_PIXEL))
    {
        n = (pos._x - OFFSET_PIXEL);
        while (n <= (pos._x + OFFSET_PIXEL))
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

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
                return (id_zone);
            n++;
        }
        i++;
    }
    return (ZONE_NOT_FIND);
}

void            ZoneAnalyser::Analyse()
{
}

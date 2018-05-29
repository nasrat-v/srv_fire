//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/data_transfert_object/Pixel.hh"

Pixel::Pixel()
{
    _colors._red = 0;
    _colors._green = 0;
    _colors._blue = 0;
    _pos._y = 0;
    _pos._x = 0;
}

Pixel::~Pixel()
{
}

const Pixel::t_rgb  &Pixel::getColors() const
{
    return (_colors);
}

const Pixel::t_pos  &Pixel::getPos() const
{
    return (_pos);
}

void        Pixel::setColors(const Pixel::t_rgb &colors)
{
    _colors._red = colors._red;
    _colors._green = colors._green;
    _colors._blue = colors._blue;
}

void        Pixel::setColors(uint8_t red, uint8_t green, uint8_t blue)
{
    _colors._red = red;
    _colors._green = green;
    _colors._blue = blue;
}

void        Pixel::setPosition(int y, int x)
{
    _pos._y = y;
    _pos._x = x;
}

void        Pixel::setPosition(const Pixel::t_pos &pos)
{
    _pos._y = pos._y;
    _pos._x = pos._x;
}

// operator < overload to allow the class to be used as Key in a Map
bool        Pixel::t_rgb::operator<(const Pixel::t_rgb &color) const
{
    return ((_red + _green + _blue) < (color._red + color._green + color._blue));
}

// operator < overload to allow the class to be used as Key in a Map
bool        Pixel::s_pos::operator<(const Pixel::t_pos &pos) const
{
    return ((_y + _x) < (pos._y + pos._x));
}

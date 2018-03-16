//
// Created by nasrat_v on 15/03/18.
//

#include "../header/Pixel.hh"

Pixel::Pixel()
{
    _colors._red = 0;
    _colors._green = 0;
    _colors._blue = 0;
}

Pixel::~Pixel()
{
}

const Pixel::t_rgb  &Pixel::getColors() const
{
    return (_colors);
}

void        Pixel::setColors(const Pixel::t_rgb &colors)
{
    _colors._red = colors._red;
    _colors._green = colors._green;
    _colors._blue = colors._blue;
}

// operator < overload to allow the class to be used as Key in a Map
bool        Pixel::t_rgb::operator<(const Pixel::t_rgb &color) const
{
    return ((_red + _green + _blue) < (color._red + color._green + color._blue));
}

//
// Created by nasrat_v on 15/03/18.
//

#include "../../header/data_transfert_object/Zone.hh"

Zone::Zone(): Image()
{
    _leftTopPos._y = 1080;
    _leftTopPos._x = 1920;
    _rightBottomPos._y = 0;
    _rightBottomPos._x = 0;
}

Zone::~Zone()
{
}

void        Zone::setLeftTopPos(const Pixel::t_pos &pos)
{
    _leftTopPos._y = pos._y;
    _leftTopPos._x = pos._x;
}

void        Zone::setRightBottomPos(const Pixel::t_pos &pos)
{
    _rightBottomPos._y = pos._y;
    _rightBottomPos._x = pos._x;
}

void        Zone::setLowerY(int y)
{
    _leftTopPos._y = y;
}

void        Zone::setLowerX(int x)
{
    _leftTopPos._x = x;
}

void        Zone::setBiggerY(int y)
{
    _rightBottomPos._y = y;
}

void        Zone::setBiggerX(int x)
{
    _rightBottomPos._x = x;
}

void        Zone::setTypeZone(const Pixel::typeTemp &type)
{
    _typeZone = type;
}

const Pixel::t_pos  &Zone::getLeftTopPos() const
{
    return (_leftTopPos);
}

const Pixel::t_pos  &Zone::getRightBottomPos() const
{
    return (_rightBottomPos);
}

const Pixel::typeTemp    &Zone::getTypeZone() const
{
    return (_typeZone);
}

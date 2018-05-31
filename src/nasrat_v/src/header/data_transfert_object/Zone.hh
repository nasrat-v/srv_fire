//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ZONE_HH__
# define __OPENCV_TEST_ZONE_HH__

#include "Image.hh"

class Zone : public Image
{
public:
    Zone();
    ~Zone();

    void                setLeftTopPos(const Pixel::t_pos &pos);
    void                setRightBottomPos(const Pixel::t_pos &pos);
    void                setLowerY(int y);
    void                setLowerX(int x);
    void                setBiggerY(int y);
    void                setBiggerX(int x);
    void                setTypeZone(const Pixel::typeTemp &type);
    const Pixel::t_pos  &getLeftTopPos() const;
    const Pixel::t_pos  &getRightBottomPos() const;
    const Pixel::typeTemp  &getTypeZone() const;

private:
    Pixel::t_pos        _leftTopPos;
    Pixel::t_pos        _rightBottomPos;
    Pixel::typeTemp     _typeZone;

};

#endif /* !__OPENCV_TEST_ZONE_HH__ */

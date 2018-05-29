//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_PIXEL_HH__
# define __OPENCV_TEST_PIXEL_HH__

#include <cstdint>

class Pixel
{
public:
    Pixel();
    ~Pixel();
    typedef struct  s_rgb
    {
        bool        operator<(const s_rgb &color) const; // operator < overload to allow the class to be used as Key in a Map
        uint8_t     _red;
        uint8_t     _green;
        uint8_t     _blue;
    }               t_rgb;
    typedef struct  s_pos
    {
        bool        operator<(const s_pos &pos) const; // operator < overload to allow the class to be used as Key in a Map
        int         _y;
        int         _x;
    }               t_pos;
    typedef float   TEMP;

    const t_rgb     &getColors() const;
    const t_pos     &getPos() const;
    const TEMP      &getTemp() const;
    void            setColors(const t_rgb &colors);
    void            setColors(uint8_t red, uint8_t green, uint8_t blue);
    void            setPosition(int y, int x);
    void            setPosition(const t_pos &pos);
    void            setTemp(const TEMP &temp);

private:
    t_rgb           _colors;
    t_pos           _pos;
    TEMP            _temp;
};

#endif /* !__OPENCV_TEST_PIXEL_HH__ */

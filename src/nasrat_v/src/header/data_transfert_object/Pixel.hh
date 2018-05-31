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

    enum class      typeTemp
    {
        NO_TYPE,
        HOT,
        VERY_HOT,
        FLAME
    };

    const t_rgb             &getColors() const;
    const t_pos             &getPos() const;
    const Pixel::typeTemp   &getTypePixel() const;
    void                    setColors(const t_rgb &colors);
    void                    setColors(uint8_t red, uint8_t green, uint8_t blue);
    void                    setPosition(int y, int x);
    void                    setPosition(const t_pos &pos);
    void                    setTypePixel(const Pixel::typeTemp &type);

private:
    t_rgb           _colors;
    t_pos           _pos;
    typeTemp       _typePixel;
};

#endif /* !__OPENCV_TEST_PIXEL_HH__ */

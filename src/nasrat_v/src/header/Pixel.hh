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
    class  t_rgb
    {
    public:
        bool        operator<(const t_rgb &color) const; // operator < overload to allow the class to be used as Key in a Map
        uint8_t     _red;
        uint8_t     _green;
        uint8_t     _blue;
    };

    const t_rgb     &getColors() const;
    void            setColors(const t_rgb &colors);
    void            setColors(uint8_t red, uint8_t green, uint8_t blue);

private:
    t_rgb           _colors;
};

#endif /* !__OPENCV_TEST_PIXEL_HH__ */

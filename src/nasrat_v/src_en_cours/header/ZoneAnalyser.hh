//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ZONEANALYSER_HH__
# define __OPENCV_TEST_ZONEANALYSER_HH__

# define ZONE_NOT_FIND  (-1)
# define OFFSET_PIXEL   10       // Precision for zone finder, bigger is more precise but slower

#include "Zone.hh"

class ZoneAnalyser
{
public:
    ZoneAnalyser();
    ~ZoneAnalyser();

    const std::vector<Zone> &getZones() const;
    void                    addZone(const Zone &zone);
    void                    createNewZone(const Pixel &pixel);
    void                    addPixelToZone(Pixel &pixel, int id_zone);
    int                     findExistingZone(const Pixel &pixel);
    size_t                  getNbZone() const;
    void                    printBorderOnZone(const cv::Mat &source_image);
    void                    Analyse();

private:
    /* Methods */
    int                     findZoneByPixelPos(int y, int x);
    void                    findBorderOfPixel(int id_zone, int y, int x);
    void                    findBorderOfRectangle(cv::Point &point_top_left, cv::Point &point_bottom_right,
                                                  const Pixel::t_pos &leftTop, const Pixel::t_pos &rightBottom);

    /* Attributes */
    std::vector<Zone>         _zones;
};

#endif /* !__OPENCV_TEST_ZONEANALYSER_HH__ */

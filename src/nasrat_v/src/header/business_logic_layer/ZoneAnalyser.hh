//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ZONEANALYSER_HH__
# define __OPENCV_TEST_ZONEANALYSER_HH__

# define ZONE_NOT_FIND                  (-1)
# define DEEPNESS_SONAR                 20       // Deepness for sonar algorithm, bigger is slower. Depends on the image resolution
# define FLAME_COLOR_SCALAR_BORDER      cv::Scalar(255, 255, 0)
# define VERY_HOT_COLOR_SCALAR_BORDER   cv::Scalar(0, 255, 255)
# define HOT_COLOR_SCALAR_BORDER        cv::Scalar(0, 0, 255)

#include "../data_transfert_object/Zone.hh"
#include "../output_static_object/Error.hh"

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
    void                    printBorderOnZone(const std::string &base_image_path);
    void                    Analyse();

private:
    /* Methods */
    int                     findZoneByPixelPos(int y, int x, const Pixel::typeTemp &type);
    void                    findBorderOfPixel(int id_zone, int y, int x);
    void                    findBorderOfRectangle(cv::Point &point_top_left, cv::Point &point_bottom_right,
                                                  const Pixel::t_pos &leftTop, const Pixel::t_pos &rightBottom);

    /* Attributes */
    std::vector<Zone>         _zones;
};

#endif /* !__OPENCV_TEST_ZONEANALYSER_HH__ */

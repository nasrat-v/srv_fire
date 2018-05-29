//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ZONEANALYSER_HH__
# define __OPENCV_TEST_ZONEANALYSER_HH__

# define ZONE_NOT_FIND          (-1)
# define DEEPNESS_SONAR         15       // Deepness for sonar algorithm, bigger is more precise but slower
# define COLOR_SCALAR_BORDER    cv::Scalar(0, 255, 0)
# define FILE_PATH              "../input/image/test02.jpg"

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

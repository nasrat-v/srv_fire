//
// Created by nasrat_v on 15/03/18.
//

#ifndef __OPENCV_TEST_ZONEANALYSER_HH__
# define __OPENCV_TEST_ZONEANALYSER_HH__

#include "Zone.hh"

class ZoneAnalyser
{
public:
    ZoneAnalyser();
    ~ZoneAnalyser();

    const std::list<Zone>   &getZones() const;
    void                    setZone(const Zone &zone);
    void                    Analyse();

private:
    std::list<Zone>         _zones;
};

#endif /* !__OPENCV_TEST_ZONEANALYSER_HH__ */

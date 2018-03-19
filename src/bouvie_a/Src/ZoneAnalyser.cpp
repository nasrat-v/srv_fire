//
// Created by nasrat_v on 15/03/18.
//

#include "../Include/ZoneAnalyser.hh"

ZoneAnalyser::ZoneAnalyser()
{
}

ZoneAnalyser::~ZoneAnalyser()
{
}

const std::list<Zone>   &ZoneAnalyser::getZones() const
{
    return (_zones);
}

void            ZoneAnalyser::setZone(const Zone &zone)
{
    _zones.push_back(zone);
}

void            ZoneAnalyser::Analyse()
{
}

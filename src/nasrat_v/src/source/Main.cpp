//
// Created by nasrat_v on 22/12/17.
//

#include "../header/FrameAnalyser.h"
#include "../header/DebugManager.h"
#include "../../lib/tinyxml2/header/tinyxml2.h"

/*void        xmlTest()
{
    tinyxml2::XMLDocument doc;

    doc.LoadFile("../input/config/xml_test.xml");
    tinyxml2::XMLElement *element = doc.FirstChildElement("test");

    std::cout << element->LastChildElement()->GetText();
    while (element != element->LastChildElement())
    {
        element->GetText();
        element = element->NextSiblingElement();
    }
}*/

Error::ErrorType analyse(const Log::debugMode &mode)
{
    Error::ErrorType error;
    FrameAnalyser core(mode,VIDEO_PATH);

    if ((error = core.initAnalyser()) != Error::ErrorType::NO_ERROR)
        return (error);
    return (core.analyseFrame());
}

int         main(int ac, const char **av)
{

    DebugManager debugManager;
    Log::debugMode mode = Log::debugMode::NO_DEBUG;

    if (ac > 1)
    {
        if (strncmp("--debug", av[1], strlen("--debug")) == 0)
            mode = debugManager.findDebugMode(av);
    }
    if (analyse(mode) != Error::ErrorType::NO_ERROR)
        return (1);
    return (0);
}
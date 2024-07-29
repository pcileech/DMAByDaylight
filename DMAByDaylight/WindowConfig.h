#pragma once
#include "pch.h"
class WindowConfig
{
    std::string ConfigName;

public:
    WindowConfig(const std::string& name)
    {
        ConfigName = name;
    }

    //WindowConfig ESP ÅäÖÃ

    bool WindowESPEnabled = false;
    bool WindowESPDistance = true;
    int WindowESPMaxDistance = 1000;
    int WindowESPFontSize = 11;

    D2D1::ColorF TextColour = Colour(255, 255, 255);
    int FontSize = 11;
    void ToJsonColour(json* j, const std::string& name, D2D1::ColorF* colour)
    {
        (*j)[ConfigName][name][LIT("r")] = colour->r;
        (*j)[ConfigName][name][LIT("g")] = colour->g;
        (*j)[ConfigName][name][LIT("b")] = colour->b;
        (*j)[ConfigName][name][LIT("a")] = colour->a;

    }
    void FromJsonColour(json j, const std::string& name, D2D1::ColorF* colour)
    {
        if (j[ConfigName].contains(name))
        {
            colour->r = j[ConfigName][name][LIT("r")];
            colour->g = j[ConfigName][name][LIT("g")];
            colour->b = j[ConfigName][name][LIT("b")];
            colour->a = j[ConfigName][name][LIT("a")];
        }
    }

    json ToJson()
    {

        json j;
        j[ConfigName][LIT("WindowESPEnabled")] = WindowESPEnabled;
        j[ConfigName][LIT("WindowESPDistance")] = WindowESPDistance;
        j[ConfigName][LIT("WindowESPMaxDistance")] = WindowESPMaxDistance;
        ToJsonColour(&j, LIT("TextColour"), &TextColour);

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("WindowESPEnabled")))
            WindowESPEnabled = j[ConfigName][LIT("WindowESPEnabled")];
        if (j[ConfigName].contains(LIT("WindowESPDistance")))
            WindowESPDistance = j[ConfigName][LIT("WindowESPDistance")];
        if (j[ConfigName].contains(LIT("WindowESPFontSize")))
            WindowESPFontSize = j[ConfigName][LIT("WindowESPFontSize")];
        if (j[ConfigName].contains(LIT("WindowESPMaxDistance")))
            WindowESPMaxDistance = j[ConfigName][LIT("WindowESPMaxDistance")];
        FromJsonColour(j, LIT("TextColour"), &TextColour);
    }
};

#pragma once
#include "pch.h"
class MiscConfig
{
    std::string ConfigName;

public:
    MiscConfig(const std::string& name)
    {
        ConfigName = name;
    }

    // ÐÂÔöµÄ Gen ESP ÅäÖÃ
    bool GenESPEnabled = false;
    bool GenESPDistance = false;
    int GenESPMaxDistance = 1000;
    int GenESPFontSize = 11;
    
    D2D1::ColorF TextColour = Colour(0, 255, 0);
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
        j[ConfigName][LIT("GenESPEnabled")] = GenESPEnabled;
        j[ConfigName][LIT("GenESPDistance")] = GenESPDistance;
        j[ConfigName][LIT("GenESPMaxDistance")] = GenESPMaxDistance;
        j[ConfigName][LIT("GenESPFontSize")] = GenESPFontSize;
        ToJsonColour(&j, LIT("TextColour"), &TextColour);

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("GenESPEnabled")))
            GenESPEnabled = j[ConfigName][LIT("GenESPEnabled")];
        if (j[ConfigName].contains(LIT("GenESPDistance")))
            GenESPDistance = j[ConfigName][LIT("GenESPDistance")];
        if (j[ConfigName].contains(LIT("GenESPFontSize")))
            GenESPFontSize = j[ConfigName][LIT("GenESPFontSize")];
        if (j[ConfigName].contains(LIT("GenESPMaxDistance")))
            GenESPMaxDistance = j[ConfigName][LIT("GenESPMaxDistance")];
        FromJsonColour(j, LIT("TextColour"), &TextColour);
    }
};


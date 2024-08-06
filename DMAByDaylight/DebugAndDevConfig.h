#pragma once
#include "pch.h"
class DebugAndDevConfig
{
    std::string ConfigName;

public:
    DebugAndDevConfig(const std::string& name)
    {
        ConfigName = name;
    }

    // ÐÂÔöµÄ Gen ESP ÅäÖÃ
    bool DebugESPEnabled = false;
    bool DebugESPDistance = false;
    int DebugESPMaxDistance = 1000;
    int DebugESPFontSize = 11;

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
        j[ConfigName][LIT("GenESPEnabled")] = DebugESPEnabled;
        j[ConfigName][LIT("GenESPDistance")] = DebugESPDistance;
        j[ConfigName][LIT("GenESPMaxDistance")] = DebugESPMaxDistance;
        j[ConfigName][LIT("GenESPFontSize")] = DebugESPFontSize;
        ToJsonColour(&j, LIT("TextColour"), &TextColour);

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("DebugESPEnabled")))
            DebugESPEnabled = j[ConfigName][LIT("DebugESPEnabled")];
        if (j[ConfigName].contains(LIT("DebugESPDistance")))
            DebugESPDistance = j[ConfigName][LIT("DebugESPDistance")];
        if (j[ConfigName].contains(LIT("DebugESPFontSize")))
            DebugESPFontSize = j[ConfigName][LIT("DebugESPFontSize")];
        if (j[ConfigName].contains(LIT("DebugESPMaxDistance")))
            DebugESPMaxDistance = j[ConfigName][LIT("DebugESPMaxDistance")];
        FromJsonColour(j, LIT("TextColour"), &TextColour);
    }
};


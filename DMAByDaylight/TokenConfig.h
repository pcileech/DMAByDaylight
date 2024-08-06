#pragma once
#include "pch.h"
class TokenConfig
{
    std::string ConfigName;

public:
    TokenConfig(const std::string& name)
    {
        ConfigName = name;
    }

    //Token ESP ÅäÖÃ

    bool TokenESPEnabled = true;
    bool TokenOnlyShowActived = false;
    bool TokenESPDistance = true;
    int TokenESPMaxDistance = 1000;
    int TokenESPFontSize = 11;

    D2D1::ColorF TextColour = Colour(0, 0, 255);
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
        j[ConfigName][LIT("TokenESPEnabled")] = TokenESPEnabled;
        j[ConfigName][LIT("TokenESPDistance")] = TokenESPDistance;
        j[ConfigName][LIT("TokenOnlyShowActived")] = TokenOnlyShowActived;
        j[ConfigName][LIT("TokenESPMaxDistance")] = TokenESPMaxDistance;
        ToJsonColour(&j, LIT("TextColour"), &TextColour);

        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("TokenESPEnabled")))
            TokenESPEnabled = j[ConfigName][LIT("TokenESPEnabled")];
        if (j[ConfigName].contains(LIT("TokenESPDistance")))
            TokenESPDistance = j[ConfigName][LIT("TokenESPDistance")];
        if (j[ConfigName].contains(LIT("TokenOnlyShowActived")))
            TokenOnlyShowActived = j[ConfigName][LIT("TokenOnlyShowActived")];
        if (j[ConfigName].contains(LIT("TokenESPFontSize")))
            TokenESPFontSize = j[ConfigName][LIT("TokenESPFontSize")];
        if (j[ConfigName].contains(LIT("TokenESPMaxDistance")))
            TokenESPMaxDistance = j[ConfigName][LIT("TokenESPMaxDistance")];
        FromJsonColour(j, LIT("TextColour"), &TextColour);
    }
};

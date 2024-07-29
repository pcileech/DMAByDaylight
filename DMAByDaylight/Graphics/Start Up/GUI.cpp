#include "pch.h"
#include "GUI.h"
#include "entity.h"
#include "Form.h"
#include "Button.h"
#include "ColourPicker.h"
#include "Label.h"
#include "tab.h"
#include "TabController.h"
#include "Toggle.h"
#include "Slider.h"
#include "DropDown.h"
#include "ComboBox.h"
#include "KeyBind.h"
#include "TabListBox.h"
#include "TabListBoxController.h"
#include "TextBox.h"
#include "ConfigUtilities.h"

int SelectedTab = 1;
int SelectedSubTab = 0;
int TabCount = 0;
int KeyBindClipBoard = 0;
EntityVector MenuEntity;
bool MenuOpen = true;
D2D1::ColorF ColourPickerClipBoard = Colour(255, 255, 255);
D2D1::ColorF ColourPick = Colour(0, 150, 255, 255);
std::wstring ScreenWidth = std::to_wstring(Configs.Overlay.Width);
std::wstring ScreenHeight = std::to_wstring(Configs.Overlay.Height);

void CreateGUI()
{
    MenuEntity = std::make_shared<Container>();
    auto form = std::make_shared<Form>(100, 100.0f, 300, 400, 2, 30, LIT(L"小透"), false);
    {
        auto tabcontroller = std::make_shared<TabController>();
        form->Push(tabcontroller);

        auto playeresptab = std::make_shared<Tab>(LIT(L"人类透视"), 5, 5, &SelectedTab, 0, 20);
        {
            auto name = std::make_shared<Toggle>(100, 5, LIT(L"姓名"), &Configs.Survivor.Name);
            playeresptab->Push(name);
            auto textcolour = std::make_shared<ColourPicker>(160, 6, &Configs.Survivor.TextColour);
            playeresptab->Push(textcolour);
            auto distance = std::make_shared<Toggle>(100, 25, LIT(L"距离"), &Configs.Survivor.Distance);
            playeresptab->Push(distance);
            auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"最大显示距离"), LIT(L"米"), 0, 1000, &Configs.Survivor.MaxDistance);
            playeresptab->Push(maxdistance);
            auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"字体大小"), LIT(L"px"), 4, 16, &Configs.Survivor.FontSize);
            playeresptab->Push(textsize);
        }
        tabcontroller->Push(playeresptab);



        auto killeresptab = std::make_shared<Tab>(LIT(L"屠夫透视"), 5, 30, &SelectedTab, 0, 20);
        {
            auto name = std::make_shared<Toggle>(100, 5, LIT(L"姓名"), &Configs.Killer.Name);
            killeresptab->Push(name);
            auto textcolour = std::make_shared<ColourPicker>(160, 6, &Configs.Killer.TextColour);
            killeresptab->Push(textcolour);
            auto distance = std::make_shared<Toggle>(100, 25, LIT(L"距离"), &Configs.Killer.Distance);
            killeresptab->Push(distance);
            auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"最大显示距离"), LIT(L"米"), 0, 1000, &Configs.Killer.MaxDistance);
            killeresptab->Push(maxdistance);
            auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"字体大小"), LIT(L"px"), 4, 16, &Configs.Killer.FontSize);
            killeresptab->Push(textsize);
        }
        tabcontroller->Push(killeresptab);

        auto overlaytab = std::make_shared<Tab>(LIT(L"分辨率"), 5, 55, &SelectedTab, 0, 20);
        {
            auto overrideresolution = std::make_shared<Toggle>(100, 5, LIT(L"Override W2S Resolution"), &Configs.Overlay.OverrideResolution);
            overlaytab->Push(overrideresolution);
            auto screenwidth = std::make_shared<TextBox>(100, 35, LIT(L"分辨率:宽"), &ScreenWidth);
            screenwidth->SetValueChangedEvent([]()
                {
                    try
                    {
                        Configs.Overlay.Width = std::stoi(ScreenWidth);
                    }
                    catch (std::exception ex)
                    {
                    }
                });
            overlaytab->Push(screenwidth);
            auto screenheight = std::make_shared<TextBox>(100, 70, LIT(L"分辨率:高"), &ScreenHeight);
            screenheight->SetValueChangedEvent([]()
                {
                    try
                    {
                        Configs.Overlay.Height = std::stoi(ScreenHeight);
                    }
                    catch (std::exception ex)
                    {
                    }
                });
            overlaytab->Push(screenheight);
        }
        tabcontroller->Push(overlaytab);

        auto configtab = std::make_shared<Tab>(LIT(L"参数设置"), 5, 80, &SelectedTab, 0, 20);
        {
            auto saveconfig = std::make_shared<Button>(100, 5, LIT(L"保存"), []()
                {
                    SaveConfig(L"Default.json");
                    CreateGUI(); // reinit/ reload
                    SelectedTab = 1;
                });
            configtab->Push(saveconfig);

            auto loadconfig = std::make_shared<Button>(165, 5, LIT(L"加载"), []()
                {
                    LoadConfig(L"Default.json");
                    CreateGUI(); // reinit/ reload
                    SelectedTab = 1;
                });
            configtab->Push(loadconfig);
        }
        tabcontroller->Push(configtab);

        // 新增的 Gen ESP 选项
        auto genesptab = std::make_shared<Tab>(LIT(L"发电机透视"), 5, 105, &SelectedTab, 0, 20);
        {
            auto enable = std::make_shared<Toggle>(100, 5, LIT(L"激活"), &Configs.GenESP.GenESPEnabled);
            genesptab->Push(enable);
            auto textcolour = std::make_shared<ColourPicker>(200, 6, &Configs.GenESP.TextColour);
            genesptab->Push(textcolour);
            auto distance = std::make_shared<Toggle>(100, 25, LIT(L"距离"), &Configs.GenESP.GenESPDistance);
            genesptab->Push(distance);
            auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"最大显示距离"), LIT(L"米"), 0, 1000, &Configs.GenESP.GenESPMaxDistance);
            genesptab->Push(maxdistance);
            auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"字体大小"), LIT(L"px"), 4, 16, &Configs.GenESP.GenESPFontSize);
            genesptab->Push(textsize);
        }
        tabcontroller->Push(genesptab);

        // 新增的 Token ESP 选项
        auto tokenesptab = std::make_shared<Tab>(LIT(L"图腾透视"), 5, 130, &SelectedTab, 0, 20);
        {
            auto enable = std::make_shared<Toggle>(100, 5, LIT(L"激活"), &Configs.TokenESP.TokenESPEnabled);
            tokenesptab->Push(enable);
            auto showActived = std::make_shared<Toggle>(100, 25, LIT(L"只看火图腾"), &Configs.TokenESP.TokenOnlyShowActived);
            tokenesptab->Push(showActived);
            auto textcolour = std::make_shared<ColourPicker>(200, 6, &Configs.TokenESP.TextColour);
            tokenesptab->Push(textcolour);
            auto distance = std::make_shared<Toggle>(100, 45, LIT(L"距离"), &Configs.TokenESP.TokenESPDistance);
            tokenesptab->Push(distance);
            auto maxdistance = std::make_shared<Slider<int>>(100, 65, 150, LIT(L"最大显示距离"), LIT(L"米"), 0, 1000, &Configs.TokenESP.TokenESPMaxDistance);
            tokenesptab->Push(maxdistance);
            auto textsize = std::make_shared<Slider<int>>(100, 90, 150, LIT(L"字体大小"), LIT(L"px"), 4, 16, &Configs.TokenESP.FontSize);
            tokenesptab->Push(textsize);
        }
        tabcontroller->Push(tokenesptab);

        // 新增的 DEBUG ESP 选项
        auto debugesptab = std::make_shared<Tab>(LIT(L"DEBUG"), 5, 155, &SelectedTab, 0, 20);
        {
            auto enable = std::make_shared<Toggle>(100, 5, LIT(L"激活"), &Configs.DebugESP.DebugESPEnabled);
            debugesptab->Push(enable);
            auto textcolour = std::make_shared<ColourPicker>(200, 6, &Configs.DebugESP.TextColour);
            debugesptab->Push(textcolour);
            auto distance = std::make_shared<Toggle>(100, 25, LIT(L"距离"), &Configs.DebugESP.DebugESPDistance);
            debugesptab->Push(distance);
            auto maxdistance = std::make_shared<Slider<int>>(100, 45, 150, LIT(L"最大显示距离"), LIT(L"米"), 0, 1000, &Configs.DebugESP.DebugESPMaxDistance);
            debugesptab->Push(maxdistance);
            auto textsize = std::make_shared<Slider<int>>(100, 70, 150, LIT(L"字体大小"), LIT(L"px"), 4, 16, &Configs.DebugESP.FontSize);
            debugesptab->Push(textsize);
        }
        tabcontroller->Push(debugesptab);
    }

    auto form1 = std::make_shared<Form>(0, 0, 0, 0, 0, 0, LIT(L""), false);
    MenuEntity->Push(form);
    MenuEntity->Draw();
    MenuEntity->Update();
}

void SetFormPriority()
{
    std::sort(MenuEntity->GetContainer().begin(), MenuEntity->GetContainer().end(),
        [](child a, child b) { return b->GetLastClick() < a->GetLastClick(); }
    );
}

float LastOpen = 0;

void Render()
{
    if (IsKeyClicked(VK_INSERT) && LastOpen < clock() * 0.00001f)
    {
        LastOpen = (clock() * 0.00001f) + 0.002f;
        MenuOpen = !MenuOpen;
    }

    MenuEntity->Draw();
    MenuEntity->GetContainer()[0]->Update();
    SetFormPriority();
}

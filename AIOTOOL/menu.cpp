#include "menu.h"
#include "features.h"
#include "imguipp_v2.h"

ImFont* MainCaps;
ImFont* Main;
ImFont* FMenu;
ImFont* headerFont;
ImFont* bodyFont;
ImFont* bodyFont2;
ImVec2 screenSize = ImVec2(WND_SIZEX, WND_SIZEY);
std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" };
std::random_device rd;
std::mt19937 generator(rd());
std::string RandStr(size_t length)
{
    const size_t char_size = chars.size();
    std::uniform_int_distribution<> random_int(0, char_size - 1);
    std::string output;
    for (size_t i = 0; i < length; ++i)
        output.push_back(chars[random_int(generator)]);
    return output;
}

void AIO::MENUSHOW()
{

    ImGui::UITheme();

    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar;
    static bool open = true;
    if (!open) ExitProcess(0);
    ImGui::SetNextWindowPos(ImVec2(screenSize.x / 2.75, screenSize.y / 2.75), ImGuiCond_Once);
    ImGui::Begin("MainWindow", &open, windowFlags);

    ImGui::MainUISetup();

    ImGui::End();
}


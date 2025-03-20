#ifndef DEBUGWINDOW_H
#define DEBUGWINDOW_H

#include <iostream>
#include <memory>
#include <vector>

#include "imgui.h"
#include "MovingImage.h"
#include "Text.h"


struct DebugData {
    char textBuffer[128] = "PAUSE";
    float speedValue = 0.3f;
    float sizeValue = 2.f;
    std::vector<std::string> items = {
        "BluRay",
        "CD",
        "DVD",
    };
    float color[3];
};

class DebugWindow {
public:
    void setDebugData(const DebugData& newData);
    void Render(std::shared_ptr<MovingImage> img, std::shared_ptr<Text>  text);
private:
    DebugData data;
};

#endif // DEBUGWINDOW_H

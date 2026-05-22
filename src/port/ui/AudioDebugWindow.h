#pragma once
#include <libultraship/libultraship.h>

namespace SF64 {

class AudioDebugWindow : public Ship::GuiWindow {
public:
    using Ship::GuiWindow::GuiWindow;

    void InitElement() override {}
    void DrawElement() override;
    void UpdateElement() override {}
};

} // namespace SF64

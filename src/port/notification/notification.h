#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#ifdef __cplusplus

#include <string>
#include <cstdint>
#include <ship/window/gui/GuiWindow.h>
namespace Notification {

struct Options {
    uint32_t id = 0;
    const char* itemIcon = nullptr;
    std::string prefix = "";
    ImVec4 prefixColor = ImVec4(0.5f, 0.5f, 1.0f, 1.0f);
    std::string message = "";
    ImVec4 messageColor = ImVec4(0.7f, 0.7f, 0.7f, 1.0f);
    std::string suffix = "";
    ImVec4 suffixColor = ImVec4(1.0f, 0.5f, 0.5f, 1.0f);
    float remainingTime = 0.0f; // Seconds
    bool mute = false;
    bool isAchievement = false; // Simple flag for achievement notifications
};

class Window : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

    void InitElement() override{};
    void DrawElement() override{};
    void Draw() override;
    void UpdateElement() override;

  private:
    void DrawRegularNotification(const Options& notification, ImVec2 basePosition, int inverseIndex, int position,
                                 float padding, ImGuiViewport* vp, int index);
    void DrawEnhancedNotification(const Options& notification, ImVec2 basePosition, int position, float padding,
                                  int index);
};

void Emit(Options notification);
void EmitAchievement(const char* iconPath, const std::string& achievementName, int harbourMastery);
void EmitAchievementProgress(const char* iconPath, const char* name, int current, int target);
void EmitAchievementProgressWithEvent(const char* iconPath, const char* eventName, const char* achievementName,
                                      int current, int target);
bool IsNotificationActive();

} // namespace Notification

#endif // __cplusplus
#endif // NOTIFICATION_H
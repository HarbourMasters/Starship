#include "UIWidgets_Bridge.h"
#include "port/ui/UIWidgets.h"

#include <span>

/* =========================================================================
 * Helpers: convert flat C color/enum fields to C++ types
 * ====================================================================== */

static inline ImVec4 MakeColor(float r, float g, float b, float a) {
    return ImVec4(r, g, b, a);
}

static inline UIWidgets::LabelPosition ToLabelPosition(int v) {
    switch (v) {
        case UIWIDGETS_LABEL_FAR:
            return UIWidgets::LabelPosition::Far;
        case UIWIDGETS_LABEL_ABOVE:
            return UIWidgets::LabelPosition::Above;
        case UIWIDGETS_LABEL_NONE:
            return UIWidgets::LabelPosition::None;
        case UIWIDGETS_LABEL_WITHIN:
            return UIWidgets::LabelPosition::Within;
        default:
            return UIWidgets::LabelPosition::Near;
    }
}

static inline UIWidgets::ComponentAlignment ToAlignment(int v) {
    return (v == UIWIDGETS_ALIGN_RIGHT) ? UIWidgets::ComponentAlignment::Right : UIWidgets::ComponentAlignment::Left;
}

static inline UIWidgets::CheckboxGraphics ToCheckboxGraphics(int v) {
    switch (v) {
        case UIWIDGETS_CHECKBOX_CHECKMARK:
            return UIWidgets::CheckboxGraphics::Checkmark;
        case UIWIDGETS_CHECKBOX_NONE:
            return UIWidgets::CheckboxGraphics::None;
        default:
            return UIWidgets::CheckboxGraphics::Cross;
    }
}

/* Convert C options structs to C++ options structs */

static UIWidgets::ButtonOptions ToButtonOptions(const UIWidgets_ButtonOptions* opts) {
    if (!opts)
        return {};
    return {
        .color = MakeColor(opts->color_r, opts->color_g, opts->color_b, opts->color_a),
        .size = ImVec2(opts->size_x, opts->size_y),
        .tooltip = opts->tooltip ? opts->tooltip : "",
        .disabled = (bool) opts->disabled,
        .disabledTooltip = opts->disabledTooltip ? opts->disabledTooltip : "",
    };
}

static UIWidgets::CheckboxOptions ToCheckboxOptions(const UIWidgets_CheckboxOptions* opts) {
    if (!opts)
        return {};
    return {
        .color = MakeColor(opts->color_r, opts->color_g, opts->color_b, opts->color_a),
        .tooltip = opts->tooltip ? opts->tooltip : "",
        .disabled = (bool) opts->disabled,
        .disabledTooltip = opts->disabledTooltip ? opts->disabledTooltip : "",
        .defaultValue = (bool) opts->defaultValue,
        .alignment = ToAlignment(opts->alignment),
        .labelPosition = ToLabelPosition(opts->labelPosition),
    };
}

static UIWidgets::ComboboxOptions ToComboboxOptions(const UIWidgets_ComboboxOptions* opts) {
    if (!opts)
        return {};
    return {
        .color = MakeColor(opts->color_r, opts->color_g, opts->color_b, opts->color_a),
        .tooltip = opts->tooltip ? opts->tooltip : "",
        .disabled = (bool) opts->disabled,
        .disabledTooltip = opts->disabledTooltip ? opts->disabledTooltip : "",
        .defaultIndex = opts->defaultIndex,
        .alignment = ToAlignment(opts->alignment),
        .labelPosition = ToLabelPosition(opts->labelPosition),
        .flags = (ImGuiComboFlags) opts->flags,
    };
}

static UIWidgets::IntSliderOptions ToIntSliderOptions(const UIWidgets_IntSliderOptions* opts) {
    if (!opts)
        return {};
    return {
        .color = MakeColor(opts->color_r, opts->color_g, opts->color_b, opts->color_a),
        .tooltip = opts->tooltip ? opts->tooltip : "",
        .disabled = (bool) opts->disabled,
        .disabledTooltip = opts->disabledTooltip ? opts->disabledTooltip : "",
        .showButtons = (bool) opts->showButtons,
        .flags = (ImGuiSliderFlags) opts->flags,
        .format = opts->format ? opts->format : "%d",
        .step = opts->step,
        .alignment = ToAlignment(opts->alignment),
        .labelPosition = ToLabelPosition(opts->labelPosition),
    };
}

static UIWidgets::FloatSliderOptions ToFloatSliderOptions(const UIWidgets_FloatSliderOptions* opts) {
    if (!opts)
        return {};
    return {
        .color = MakeColor(opts->color_r, opts->color_g, opts->color_b, opts->color_a),
        .tooltip = opts->tooltip ? opts->tooltip : "",
        .disabled = (bool) opts->disabled,
        .disabledTooltip = opts->disabledTooltip ? opts->disabledTooltip : "",
        .showButtons = (bool) opts->showButtons,
        .flags = (ImGuiSliderFlags) opts->flags,
        .format = opts->format ? opts->format : "%f",
        .step = opts->step,
        .isPercentage = (bool) opts->isPercentage,
        .alignment = ToAlignment(opts->alignment),
        .labelPosition = ToLabelPosition(opts->labelPosition),
    };
}

/* =========================================================================
 * extern "C" implementations
 * ====================================================================== */

extern "C" {

/* -------------------------------------------------------------------------
 * Default option initializers
 * ---------------------------------------------------------------------- */

UIWidgets_ButtonOptions UIWidgets_DefaultButtonOptions(void) {
    UIWidgets::ButtonOptions cpp = {};
    UIWidgets_ButtonOptions c = {};
    c.color_r = cpp.color.x;
    c.color_g = cpp.color.y;
    c.color_b = cpp.color.z;
    c.color_a = cpp.color.w;
    c.size_x = cpp.size.x;
    c.size_y = cpp.size.y;
    c.tooltip = cpp.tooltip;
    c.disabled = (int) cpp.disabled;
    c.disabledTooltip = cpp.disabledTooltip;
    return c;
}

UIWidgets_CheckboxOptions UIWidgets_DefaultCheckboxOptions(void) {
    UIWidgets::CheckboxOptions cpp = {};
    UIWidgets_CheckboxOptions c = {};
    c.color_r = cpp.color.x;
    c.color_g = cpp.color.y;
    c.color_b = cpp.color.z;
    c.color_a = cpp.color.w;
    c.tooltip = cpp.tooltip;
    c.disabled = (int) cpp.disabled;
    c.disabledTooltip = cpp.disabledTooltip;
    c.defaultValue = (int) cpp.defaultValue;
    c.alignment = (int) cpp.alignment;
    c.labelPosition = (int) cpp.labelPosition;
    return c;
}

UIWidgets_ComboboxOptions UIWidgets_DefaultComboboxOptions(void) {
    UIWidgets::ComboboxOptions cpp = {};
    UIWidgets_ComboboxOptions c = {};
    c.color_r = cpp.color.x;
    c.color_g = cpp.color.y;
    c.color_b = cpp.color.z;
    c.color_a = cpp.color.w;
    c.tooltip = cpp.tooltip;
    c.disabled = (int) cpp.disabled;
    c.disabledTooltip = cpp.disabledTooltip;
    c.defaultIndex = cpp.defaultIndex;
    c.alignment = (int) cpp.alignment;
    c.labelPosition = (int) cpp.labelPosition;
    c.flags = (int) cpp.flags;
    return c;
}

UIWidgets_IntSliderOptions UIWidgets_DefaultIntSliderOptions(void) {
    UIWidgets::IntSliderOptions cpp = {};
    UIWidgets_IntSliderOptions c = {};
    c.color_r = cpp.color.x;
    c.color_g = cpp.color.y;
    c.color_b = cpp.color.z;
    c.color_a = cpp.color.w;
    c.tooltip = cpp.tooltip;
    c.disabled = (int) cpp.disabled;
    c.disabledTooltip = cpp.disabledTooltip;
    c.showButtons = (int) cpp.showButtons;
    c.flags = (int) cpp.flags;
    c.format = cpp.format;
    c.step = cpp.step;
    c.alignment = (int) cpp.alignment;
    c.labelPosition = (int) cpp.labelPosition;
    return c;
}

UIWidgets_FloatSliderOptions UIWidgets_DefaultFloatSliderOptions(void) {
    UIWidgets::FloatSliderOptions cpp = {};
    UIWidgets_FloatSliderOptions c = {};
    c.color_r = cpp.color.x;
    c.color_g = cpp.color.y;
    c.color_b = cpp.color.z;
    c.color_a = cpp.color.w;
    c.tooltip = cpp.tooltip;
    c.disabled = (int) cpp.disabled;
    c.disabledTooltip = cpp.disabledTooltip;
    c.showButtons = (int) cpp.showButtons;
    c.flags = (int) cpp.flags;
    c.format = cpp.format;
    c.step = cpp.step;
    c.isPercentage = (int) cpp.isPercentage;
    c.alignment = (int) cpp.alignment;
    c.labelPosition = (int) cpp.labelPosition;
    return c;
}

/* -------------------------------------------------------------------------
 * Layout helpers
 * ---------------------------------------------------------------------- */

char* UIWidgets_WrappedText(const char* text, unsigned int charactersPerLine) {
    return UIWidgets::WrappedText(text, charactersPerLine);
}

void UIWidgets_SetLastItemHoverText(const char* text) {
    UIWidgets::SetLastItemHoverText(text);
}

void UIWidgets_InsertHelpHoverText(const char* text) {
    UIWidgets::InsertHelpHoverText(text);
}

void UIWidgets_Tooltip(const char* text) {
    UIWidgets::Tooltip(text);
}

void UIWidgets_Spacer(float height) {
    UIWidgets::Spacer(height);
}

void UIWidgets_PaddedSeparator(int padTop, int padBottom, float extraTop, float extraBottom) {
    UIWidgets::PaddedSeparator((bool) padTop, (bool) padBottom, extraTop, extraBottom);
}

void UIWidgets_DisableComponent(float alpha) {
    UIWidgets::DisableComponent(alpha);
}

void UIWidgets_ReEnableComponent(const char* disabledTooltipText) {
    UIWidgets::ReEnableComponent(disabledTooltipText);
}

/* -------------------------------------------------------------------------
 * Menu / MenuBar
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleMenu(float r, float g, float b, float a) {
    UIWidgets::PushStyleMenu(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleMenu(void) {
    UIWidgets::PopStyleMenu();
}

int UIWidgets_BeginMenu(const char* label, float r, float g, float b, float a) {
    return (int) UIWidgets::BeginMenu(label, MakeColor(r, g, b, a));
}

void UIWidgets_PushStyleMenuItem(float r, float g, float b, float a) {
    UIWidgets::PushStyleMenuItem(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleMenuItem(void) {
    UIWidgets::PopStyleMenuItem();
}

int UIWidgets_MenuItem(const char* label, const char* shortcut, float r, float g, float b, float a) {
    return (int) UIWidgets::MenuItem(label, shortcut, MakeColor(r, g, b, a));
}

/* -------------------------------------------------------------------------
 * Button
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleButton(float r, float g, float b, float a) {
    UIWidgets::PushStyleButton(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleButton(void) {
    UIWidgets::PopStyleButton();
}

int UIWidgets_Button(const char* label, const UIWidgets_ButtonOptions* options) {
    return (int) UIWidgets::Button(label, ToButtonOptions(options));
}

/* -------------------------------------------------------------------------
 * Checkbox
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleCheckbox(float r, float g, float b, float a) {
    UIWidgets::PushStyleCheckbox(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleCheckbox(void) {
    UIWidgets::PopStyleCheckbox();
}

int UIWidgets_Checkbox(const char* label, int* value, const UIWidgets_CheckboxOptions* options) {
    bool bValue = (bool) *value;
    bool changed = UIWidgets::Checkbox(label, &bValue, ToCheckboxOptions(options));
    *value = (int) bValue;
    return (int) changed;
}

int UIWidgets_CVarCheckbox(const char* label, const char* cvarName, const UIWidgets_CheckboxOptions* options) {
    return (int) UIWidgets::CVarCheckbox(label, cvarName, ToCheckboxOptions(options));
}

/* -------------------------------------------------------------------------
 * Combobox
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleCombobox(float r, float g, float b, float a) {
    UIWidgets::PushStyleCombobox(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleCombobox(void) {
    UIWidgets::PopStyleCombobox();
}

int UIWidgets_Combobox(const char* label, uint8_t* value, const char** comboArray, int count,
                       const UIWidgets_ComboboxOptions* options) {
    std::span<const char*> span(comboArray, (size_t) count);
    return (int) UIWidgets::Combobox(label, value, span, ToComboboxOptions(options));
}

int UIWidgets_CVarCombobox(const char* label, const char* cvarName, const char** comboArray, int count,
                           const UIWidgets_ComboboxOptions* options) {
    std::span<const char*> span(comboArray, (size_t) count);
    return (int) UIWidgets::CVarCombobox(label, cvarName, span, ToComboboxOptions(options));
}

/* -------------------------------------------------------------------------
 * Integer slider
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleSlider(float r, float g, float b, float a) {
    UIWidgets::PushStyleSlider(MakeColor(r, g, b, a));
}

void UIWidgets_PopStyleSlider(void) {
    UIWidgets::PopStyleSlider();
}

int UIWidgets_SliderInt(const char* label, int32_t* value, int32_t min, int32_t max,
                        const UIWidgets_IntSliderOptions* options) {
    return (int) UIWidgets::SliderInt(label, value, min, max, ToIntSliderOptions(options));
}

int UIWidgets_CVarSliderInt(const char* label, const char* cvarName, int32_t min, int32_t max, int32_t defaultValue,
                            const UIWidgets_IntSliderOptions* options) {
    return (int) UIWidgets::CVarSliderInt(label, cvarName, min, max, defaultValue, ToIntSliderOptions(options));
}

/* -------------------------------------------------------------------------
 * Float slider
 * ---------------------------------------------------------------------- */

int UIWidgets_SliderFloat(const char* label, float* value, float min, float max,
                          const UIWidgets_FloatSliderOptions* options) {
    return (int) UIWidgets::SliderFloat(label, value, min, max, ToFloatSliderOptions(options));
}

int UIWidgets_CVarSliderFloat(const char* label, const char* cvarName, float min, float max, float defaultValue,
                              const UIWidgets_FloatSliderOptions* options) {
    return (int) UIWidgets::CVarSliderFloat(label, cvarName, min, max, defaultValue, ToFloatSliderOptions(options));
}

/* -------------------------------------------------------------------------
 * Legacy / V1 wrappers
 * ---------------------------------------------------------------------- */

int UIWidgets_EnhancementCheckbox(const char* text, const char* cvarName, int disabled, const char* disabledTooltipText,
                                  int disabledGraphic, int defaultValue) {
    return (int) UIWidgets::EnhancementCheckbox(text, cvarName, (bool) disabled,
                                                disabledTooltipText ? disabledTooltipText : "",
                                                ToCheckboxGraphics(disabledGraphic), (bool) defaultValue);
}

int UIWidgets_PaddedEnhancementCheckbox(const char* text, const char* cvarName, int padTop, int padBottom, int disabled,
                                        const char* disabledTooltipText, int disabledGraphic, int defaultValue) {
    return (int) UIWidgets::PaddedEnhancementCheckbox(text, cvarName, (bool) padTop, (bool) padBottom, (bool) disabled,
                                                      disabledTooltipText ? disabledTooltipText : "",
                                                      ToCheckboxGraphics(disabledGraphic), (bool) defaultValue);
}

int UIWidgets_EnhancementCombobox(const char* cvarName, const char** comboArray, int count, uint8_t defaultIndex,
                                  int disabled, const char* disabledTooltipText, uint8_t disabledValue) {
    std::span<const char*> span(comboArray, (size_t) count);
    return (int) UIWidgets::EnhancementCombobox(cvarName, span, defaultIndex, (bool) disabled,
                                                disabledTooltipText ? disabledTooltipText : "", disabledValue);
}

void UIWidgets_PaddedText(const char* text, int padTop, int padBottom) {
    UIWidgets::PaddedText(text, (bool) padTop, (bool) padBottom);
}

int UIWidgets_EnhancementSliderInt(const char* text, const char* id, const char* cvarName, int min, int max,
                                   const char* format, int defaultValue, int plusMinusButton, int disabled,
                                   const char* disabledTooltipText) {
    return (int) UIWidgets::EnhancementSliderInt(text, id, cvarName, min, max, format ? format : "%d", defaultValue,
                                                 (bool) plusMinusButton, (bool) disabled,
                                                 disabledTooltipText ? disabledTooltipText : "");
}

int UIWidgets_PaddedEnhancementSliderInt(const char* text, const char* id, const char* cvarName, int min, int max,
                                         const char* format, int defaultValue, int plusMinusButton, int padTop,
                                         int padBottom, int disabled, const char* disabledTooltipText) {
    return (int) UIWidgets::PaddedEnhancementSliderInt(
        text, id, cvarName, min, max, format ? format : "%d", defaultValue, (bool) plusMinusButton, (bool) padTop,
        (bool) padBottom, (bool) disabled, disabledTooltipText ? disabledTooltipText : "");
}

int UIWidgets_EnhancementSliderFloat(const char* text, const char* id, const char* cvarName, float min, float max,
                                     const char* format, float defaultValue, int isPercentage, int plusMinusButton,
                                     int disabled, const char* disabledTooltipText) {
    return (int) UIWidgets::EnhancementSliderFloat(text, id, cvarName, min, max, format ? format : "%f", defaultValue,
                                                   (bool) isPercentage, (bool) plusMinusButton, (bool) disabled,
                                                   disabledTooltipText ? disabledTooltipText : "");
}

int UIWidgets_PaddedEnhancementSliderFloat(const char* text, const char* id, const char* cvarName, float min, float max,
                                           const char* format, float defaultValue, int isPercentage,
                                           int plusMinusButton, int padTop, int padBottom, int disabled,
                                           const char* disabledTooltipText) {
    return (int) UIWidgets::PaddedEnhancementSliderFloat(
        text, id, cvarName, min, max, format ? format : "%f", defaultValue, (bool) isPercentage, (bool) plusMinusButton,
        (bool) padTop, (bool) padBottom, (bool) disabled, disabledTooltipText ? disabledTooltipText : "");
}

int UIWidgets_EnhancementRadioButton(const char* text, const char* cvarName, int id) {
    return (int) UIWidgets::EnhancementRadioButton(text, cvarName, id);
}

} // extern "C"

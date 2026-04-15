#pragma once

/**
 * UIWidgets_Bridge.h
 *
 * C bridge for the UIWidgets C++ namespace.
 * All functions are callable from C translation units.
 *
 * Naming convention: UIWidgets_<FunctionName>
 *
 * C-compatible replacements for C++ types:
 *   - bool             -> int  (0 = false, non-zero = true)
 *   - ImVec4 (color)   -> four floats (r, g, b, a)
 *   - std::span        -> const char** + int count
 *   - enum class       -> int
 */

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Enumerations (mirrors UIWidgets enums as plain int constants)
 * ---------------------------------------------------------------------- */

/* UIWidgets::CheckboxGraphics */
#define UIWIDGETS_CHECKBOX_CROSS 0
#define UIWIDGETS_CHECKBOX_CHECKMARK 1
#define UIWIDGETS_CHECKBOX_NONE 2

/* UIWidgets::LabelPosition */
#define UIWIDGETS_LABEL_NEAR 0
#define UIWIDGETS_LABEL_FAR 1
#define UIWIDGETS_LABEL_ABOVE 2
#define UIWIDGETS_LABEL_NONE 3
#define UIWIDGETS_LABEL_WITHIN 4

/* UIWidgets::ComponentAlignment */
#define UIWIDGETS_ALIGN_LEFT 0
#define UIWIDGETS_ALIGN_RIGHT 1

/* -------------------------------------------------------------------------
 * Options structs
 * All color fields are RGBA floats in [0,1].
 * ---------------------------------------------------------------------- */

typedef struct {
    float color_r, color_g, color_b, color_a; /**< Button color (default: Gray) */
    float size_x, size_y;                     /**< Button size (0,0 = inline, -1,0 = fill) */
    const char* tooltip;
    int disabled;
    const char* disabledTooltip;
} UIWidgets_ButtonOptions;

typedef struct {
    float color_r, color_g, color_b, color_a; /**< Checkbox accent color (default: Indigo) */
    const char* tooltip;
    int disabled;
    const char* disabledTooltip;
    int defaultValue;  /**< Only used by CVarCheckbox */
    int alignment;     /**< UIWidgets_ComponentAlignment */
    int labelPosition; /**< UIWidgets_LabelPosition */
} UIWidgets_CheckboxOptions;

typedef struct {
    float color_r, color_g, color_b, color_a; /**< Combobox accent color (default: Indigo) */
    const char* tooltip;
    int disabled;
    const char* disabledTooltip;
    uint32_t defaultIndex; /**< Only used by CVarCombobox */
    int alignment;         /**< UIWidgets_ComponentAlignment */
    int labelPosition;     /**< UIWidgets_LabelPosition */
    int flags;             /**< ImGuiComboFlags */
} UIWidgets_ComboboxOptions;

typedef struct {
    float color_r, color_g, color_b, color_a; /**< Slider color (default: Gray) */
    const char* tooltip;
    int disabled;
    const char* disabledTooltip;
    int showButtons;
    int flags;          /**< ImGuiSliderFlags */
    const char* format; /**< printf format, e.g. "%d" */
    uint32_t step;
    int alignment;     /**< UIWidgets_ComponentAlignment */
    int labelPosition; /**< UIWidgets_LabelPosition */
} UIWidgets_IntSliderOptions;

typedef struct {
    float color_r, color_g, color_b, color_a; /**< Slider color (default: Gray) */
    const char* tooltip;
    int disabled;
    const char* disabledTooltip;
    int showButtons;
    int flags;          /**< ImGuiSliderFlags */
    const char* format; /**< printf format, e.g. "%f" */
    float step;
    int isPercentage;  /**< Multiply displayed value by 100 */
    int alignment;     /**< UIWidgets_ComponentAlignment */
    int labelPosition; /**< UIWidgets_LabelPosition */
} UIWidgets_FloatSliderOptions;

/* -------------------------------------------------------------------------
 * Default option initializers
 * ---------------------------------------------------------------------- */

/** Returns a UIWidgets_ButtonOptions pre-filled with the C++ defaults. */
UIWidgets_ButtonOptions UIWidgets_DefaultButtonOptions(void);

/** Returns a UIWidgets_CheckboxOptions pre-filled with the C++ defaults. */
UIWidgets_CheckboxOptions UIWidgets_DefaultCheckboxOptions(void);

/** Returns a UIWidgets_ComboboxOptions pre-filled with the C++ defaults. */
UIWidgets_ComboboxOptions UIWidgets_DefaultComboboxOptions(void);

/** Returns a UIWidgets_IntSliderOptions pre-filled with the C++ defaults. */
UIWidgets_IntSliderOptions UIWidgets_DefaultIntSliderOptions(void);

/** Returns a UIWidgets_FloatSliderOptions pre-filled with the C++ defaults. */
UIWidgets_FloatSliderOptions UIWidgets_DefaultFloatSliderOptions(void);

/* -------------------------------------------------------------------------
 * Layout helpers
 * ---------------------------------------------------------------------- */

/**
 * Returns a heap-allocated string with automatic line-wrapping inserted.
 * Caller is responsible for freeing the returned pointer with free().
 */
char* UIWidgets_WrappedText(const char* text, unsigned int charactersPerLine);

void UIWidgets_SetLastItemHoverText(const char* text);
void UIWidgets_InsertHelpHoverText(const char* text);
void UIWidgets_Tooltip(const char* text);
void UIWidgets_Spacer(float height);

/**
 * Renders a separator with optional vertical padding above and below.
 *
 * @param padTop     Non-zero to add space above the separator.
 * @param padBottom  Non-zero to add space below the separator.
 * @param extraTop   Extra top padding in pixels.
 * @param extraBottom Extra bottom padding in pixels.
 */
void UIWidgets_PaddedSeparator(int padTop, int padBottom, float extraTop, float extraBottom);

void UIWidgets_DisableComponent(float alpha);
void UIWidgets_ReEnableComponent(const char* disabledTooltipText);

/* -------------------------------------------------------------------------
 * Menu / MenuBar
 * ---------------------------------------------------------------------- */

/** Push/pop menu style independently (color as RGBA floats). */
void UIWidgets_PushStyleMenu(float r, float g, float b, float a);
void UIWidgets_PopStyleMenu(void);

/**
 * Begin a styled ImGui menu.
 * @return Non-zero if the menu is open and items should be rendered.
 */
int UIWidgets_BeginMenu(const char* label, float r, float g, float b, float a);

void UIWidgets_PushStyleMenuItem(float r, float g, float b, float a);
void UIWidgets_PopStyleMenuItem(void);

/**
 * Render a styled menu item.
 * @return Non-zero if the item was activated.
 */
int UIWidgets_MenuItem(const char* label, const char* shortcut, float r, float g, float b, float a);

/* -------------------------------------------------------------------------
 * Button
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleButton(float r, float g, float b, float a);
void UIWidgets_PopStyleButton(void);

/**
 * Render a styled button.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if clicked.
 */
int UIWidgets_Button(const char* label, const UIWidgets_ButtonOptions* options);

/* -------------------------------------------------------------------------
 * Checkbox
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleCheckbox(float r, float g, float b, float a);
void UIWidgets_PopStyleCheckbox(void);

/**
 * Render a styled checkbox backed by a raw bool pointer.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the value changed.
 */
int UIWidgets_Checkbox(const char* label, int* value, const UIWidgets_CheckboxOptions* options);

/**
 * Render a CVar-bound checkbox.  Reads/writes the named CVar automatically.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the CVar changed.
 */
int UIWidgets_CVarCheckbox(const char* label, const char* cvarName, const UIWidgets_CheckboxOptions* options);

/* -------------------------------------------------------------------------
 * Combobox
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleCombobox(float r, float g, float b, float a);
void UIWidgets_PopStyleCombobox(void);

/**
 * Render a styled combobox backed by a raw uint8 pointer.
 * @param comboArray  Array of string pointers.
 * @param count       Number of entries in comboArray.
 * @param options     Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the value changed.
 */
int UIWidgets_Combobox(const char* label, uint8_t* value, const char** comboArray, int count,
                       const UIWidgets_ComboboxOptions* options);

/**
 * Render a CVar-bound combobox.
 * @param comboArray  Array of string pointers.
 * @param count       Number of entries in comboArray.
 * @param options     Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the CVar changed.
 */
int UIWidgets_CVarCombobox(const char* label, const char* cvarName, const char** comboArray, int count,
                           const UIWidgets_ComboboxOptions* options);

/* -------------------------------------------------------------------------
 * Integer slider
 * ---------------------------------------------------------------------- */

void UIWidgets_PushStyleSlider(float r, float g, float b, float a);
void UIWidgets_PopStyleSlider(void);

/**
 * Render a styled integer slider backed by a raw int32 pointer.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the value changed.
 */
int UIWidgets_SliderInt(const char* label, int32_t* value, int32_t min, int32_t max,
                        const UIWidgets_IntSliderOptions* options);

/**
 * Render a CVar-bound integer slider.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the CVar changed.
 */
int UIWidgets_CVarSliderInt(const char* label, const char* cvarName, int32_t min, int32_t max, int32_t defaultValue,
                            const UIWidgets_IntSliderOptions* options);

/* -------------------------------------------------------------------------
 * Float slider
 * ---------------------------------------------------------------------- */

/**
 * Render a styled float slider backed by a raw float pointer.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the value changed.
 */
int UIWidgets_SliderFloat(const char* label, float* value, float min, float max,
                          const UIWidgets_FloatSliderOptions* options);

/**
 * Render a CVar-bound float slider.
 * @param options  Pointer to options struct, or NULL to use defaults.
 * @return Non-zero if the CVar changed.
 */
int UIWidgets_CVarSliderFloat(const char* label, const char* cvarName, float min, float max, float defaultValue,
                              const UIWidgets_FloatSliderOptions* options);

/* -------------------------------------------------------------------------
 * Legacy / V1 wrappers
 * ---------------------------------------------------------------------- */

int UIWidgets_EnhancementCheckbox(const char* text, const char* cvarName, int disabled, const char* disabledTooltipText,
                                  int disabledGraphic, int defaultValue);

int UIWidgets_PaddedEnhancementCheckbox(const char* text, const char* cvarName, int padTop, int padBottom, int disabled,
                                        const char* disabledTooltipText, int disabledGraphic, int defaultValue);

/**
 * @param comboArray  NULL-terminated array of strings (no count needed).
 */
int UIWidgets_EnhancementCombobox(const char* cvarName, const char** comboArray, int count, uint8_t defaultIndex,
                                  int disabled, const char* disabledTooltipText, uint8_t disabledValue);

void UIWidgets_PaddedText(const char* text, int padTop, int padBottom);

int UIWidgets_EnhancementSliderInt(const char* text, const char* id, const char* cvarName, int min, int max,
                                   const char* format, int defaultValue, int plusMinusButton, int disabled,
                                   const char* disabledTooltipText);

int UIWidgets_PaddedEnhancementSliderInt(const char* text, const char* id, const char* cvarName, int min, int max,
                                         const char* format, int defaultValue, int plusMinusButton, int padTop,
                                         int padBottom, int disabled, const char* disabledTooltipText);

int UIWidgets_EnhancementSliderFloat(const char* text, const char* id, const char* cvarName, float min, float max,
                                     const char* format, float defaultValue, int isPercentage, int plusMinusButton,
                                     int disabled, const char* disabledTooltipText);

int UIWidgets_PaddedEnhancementSliderFloat(const char* text, const char* id, const char* cvarName, float min, float max,
                                           const char* format, float defaultValue, int isPercentage,
                                           int plusMinusButton, int padTop, int padBottom, int disabled,
                                           const char* disabledTooltipText);

int UIWidgets_EnhancementRadioButton(const char* text, const char* cvarName, int id);

#ifdef __cplusplus
}
#endif

#include "alchemy_combos.h"
#include "version.h"
#include "gfx/element_sprites.h"
#include "gfx/title_icon.h"
#include "gfx/title_logo.h"
#include "gfx/ui_sprites.h"
#include "oxygen/oxy_gfx.h"
#include "oxygen/oxy_gtk.h"
#include "oxygen/oxy_mouse.h"
#include "oxygen/oxy_widget.h"
#include "oxygen/gfx/cursorA.h"
#include "oxygen/gfx/cursorB.h"
#include "oxygen/gfx/cursorC.h"
#include "oxygen/gfx/cursorD.h"
#include "oxygen/gfx/cursorE.h"

#include <fileioc.h>
#include <graphx.h>
#include <keypadc.h>
#include <tice.h>
#include <ctype.h>
#include <compression.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

enum {
    COLOR_TRANSPARENT = 251,
    COLOR_BACKGROUND = 252,
    COLOR_TEXT = 253,
    COLOR_ACCENT = 254,
    COLOR_SELECTED_TEXT = 255,
    COLOR_LOGO_ACCENT = 224,
    COLOR_LOADING_WRAP = 250,
    CANVAS_WIDTH = 232,
    CANVAS_TOP = 0,
    CANVAS_BOTTOM = 240,
    CANVAS_ITEM_WIDTH = 40,
    CANVAS_ITEM_HEIGHT = 43,
    MAX_CANVAS_ITEMS = 16,
    TOOL_BUTTON_X = 204,
    RECYCLE_BUTTON_Y = 187,
    SETTINGS_BUTTON_Y = 214,
    PLAY_BUTTON_X = 90,
    PLAY_BUTTON_Y = 105,
    PLAY_BUTTON_WIDTH = 140,
    PLAY_BUTTON_HEIGHT = 46,
    TITLE_LOGO_SCALE = 2,
    SIDEBAR_ROWS = 5,
    HOVER_SIDEBAR_FIRST = 0,
    HOVER_ALPHABET_FIRST = HOVER_SIDEBAR_FIRST + SIDEBAR_ROWS,
    HOVER_SCROLLBAR = HOVER_ALPHABET_FIRST + 26,
    HOVER_RECYCLE = HOVER_SCROLLBAR + 1,
    HOVER_SETTINGS = HOVER_RECYCLE + 1,
    HOVER_CANVAS_FIRST = HOVER_SETTINGS + 1,
    MAX_ITEMS = 580,
    MAX_RESULTS = 3,
    SAVE_VERSION = 1
};

typedef enum {
    RESULT_READY,
    RESULT_NONE,
    RESULT_KNOWN,
    RESULT_NEW
} ResultState;

typedef enum {
    DRAG_NONE,
    DRAG_CANVAS,
    DRAG_SIDEBAR,
    DRAG_SCROLLBAR
} DragSource;

typedef struct {
    DragSource source;
    AlchemyItemId item_id;
    uint8_t canvas_index;
} DragState;

typedef struct {
    AlchemyItemId item_id;
    int x;
    int y;
} CanvasItem;

typedef struct {
    uint32_t magic;
    uint16_t version;
    uint16_t count;
    AlchemyItemId items[MAX_ITEMS];
} SaveData;

typedef struct {
    uint32_t magic;
    bool show_names;
    bool show_hints;
    bool confirm_clean;
    uint8_t pointer_speed;
} SettingsData;

typedef struct {
    const CanvasItem *canvas_items;
    uint8_t canvas_count;
    int selected_canvas_index;
    size_t selected_inventory_index;
    size_t sidebar_offset;
    const AlchemyItemId *results;
    ResultState result_state;
    bool confirm_reset;
    bool confirm_clean;
    const DragState *drag;
} GameRenderContext;

static const char SAVE_NAME[] = "ALCHSAVE";
static const char SETTINGS_NAME[] = "ALCHSET";
static const uint32_t SAVE_MAGIC = 0x48434C41;
static const uint32_t SETTINGS_MAGIC = 0x54455341;
static SaveData save_data;
static SettingsData settings;
static bool discovered[582];

/* title_logo is stored ZX7-compressed; decompress it once for scaled draws.
 * gfx_sprite_t only declares a 2-byte header, so size the buffer for the full
 * 88x28 palette sprite (2-byte header + 88*28 data = 2466 bytes) to avoid
 * zx7_Decompress overflowing into adjacent memory. */
static uint8_t title_logo_sprite[2 + 88 * 28];

static void draw_screen_contents(const GameRenderContext *context);

static void draw_element_sprite(AlchemyItemId item_id, int x, int y)
{
    const gfx_rletsprite_t *sprite = element_sprite(item_id);

    gfx_RLETSprite_NoClip(sprite, x, y);
}

static void draw_version_label(void) {
    gfx_SetTextFGColor(COLOR_TEXT);
    gfx_PrintStringXY(APP_VERSION, LCD_WIDTH - gfx_GetStringWidth(APP_VERSION) - 6, 6);
}

static void draw_game_background(void *arg) {
    draw_screen_contents((const GameRenderContext *)arg);
}

static void default_settings(void) {
    settings.magic = SETTINGS_MAGIC;
    settings.show_names = true;
    settings.show_hints = true;
    settings.confirm_clean = true;
    settings.pointer_speed = 4;
}

static void load_settings(void) {
    uint8_t handle = ti_Open(SETTINGS_NAME, "r");

    default_settings();
    if (!handle) {
        return;
    }
    if (ti_GetSize(handle) != sizeof(settings) ||
        ti_Read(&settings, sizeof(settings), 1, handle) != 1 ||
        settings.magic != SETTINGS_MAGIC || settings.pointer_speed < 2 ||
        settings.pointer_speed > 9) {
        default_settings();
    }
    ti_Close(handle);
}

static void save_settings(void) {
    uint8_t handle = ti_Open(SETTINGS_NAME, "w");

    if (!handle) {
        return;
    }
    if (ti_Write(&settings, sizeof(settings), 1, handle) == 1) {
        ti_SetArchiveStatus(true, handle);
    }
    ti_Close(handle);
}

static void sort_inventory(void) {
    uint16_t index;

    for (index = 1; index < save_data.count; index++) {
        AlchemyItemId item_id = save_data.items[index];
        uint16_t position = index;

        while (position > 0 &&
               strcmp(alchemy_item(save_data.items[position - 1])->name,
                      alchemy_item(item_id)->name) > 0) {
            save_data.items[position] = save_data.items[position - 1];
            position--;
        }
        save_data.items[position] = item_id;
    }
}

static size_t inventory_index_of(AlchemyItemId item_id) {
    size_t index;

    for (index = 0; index < save_data.count; index++) {
        if (save_data.items[index] == item_id) {
            return index;
        }
    }
    return 0;
}

static void new_game(void) {
    AlchemyItemId item_id;

    memset(&save_data, 0, sizeof(save_data));
    memset(discovered, 0, sizeof(discovered));
    save_data.magic = SAVE_MAGIC;
    save_data.version = SAVE_VERSION;
    save_data.count = 4;
    for (item_id = 1; item_id <= 4; item_id++) {
        save_data.items[item_id - 1] = item_id;
        discovered[item_id] = true;
    }
    sort_inventory();
}

static bool load_game(void) {
    uint8_t handle = ti_Open(SAVE_NAME, "r");
    uint16_t index;

    if (!handle) {
        return false;
    }
    if (ti_GetSize(handle) != sizeof(save_data) ||
        ti_Read(&save_data, sizeof(save_data), 1, handle) != 1) {
        ti_Close(handle);
        return false;
    }
    ti_Close(handle);
    if (save_data.magic != SAVE_MAGIC || save_data.version != SAVE_VERSION ||
        save_data.count < 4 || save_data.count > MAX_ITEMS) {
        return false;
    }

    memset(discovered, 0, sizeof(discovered));
    for (index = 0; index < save_data.count; index++) {
        AlchemyItemId item_id = save_data.items[index];
        if (item_id >= alchemy_item_table_size() || alchemy_item(item_id) == NULL ||
            discovered[item_id]) {
            return false;
        }
        discovered[item_id] = true;
    }
    if (!discovered[1] || !discovered[2] || !discovered[3] || !discovered[4]) {
        return false;
    }
    sort_inventory();
    return true;
}

static void save_game(void) {
    uint8_t handle = ti_Open(SAVE_NAME, "w");

    if (!handle) {
        return;
    }
    if (ti_Write(&save_data, sizeof(save_data), 1, handle) == 1) {
        ti_SetArchiveStatus(true, handle);
    }
    ti_Close(handle);
}

static size_t unlock_item(AlchemyItemId item_id) {
    size_t index;

    if (discovered[item_id]) {
        for (index = 0; index < save_data.count; index++) {
            if (save_data.items[index] == item_id) {
                return index;
            }
        }
    }

    index = save_data.count;
    if (index < MAX_ITEMS) {
        save_data.items[index] = item_id;
        save_data.count++;
        discovered[item_id] = true;
    }
    return index;
}

static size_t move_inventory_index(size_t current, int offset) {
    int next = (int)current + offset;

    while (next < 0) {
        next += save_data.count;
    }
    return (size_t)next % save_data.count;
}

static size_t sidebar_start(size_t selected_index) {
    size_t start = selected_index > 2 ? selected_index - 2 : 0;

    if (start + SIDEBAR_ROWS > save_data.count) {
        start = save_data.count > SIDEBAR_ROWS ? save_data.count - SIDEBAR_ROWS : 0;
    }
    return start;
}

static size_t inventory_index_for_letter(char letter) {
    size_t index;

    for (index = 0; index < save_data.count; index++) {
        char initial = (char)toupper(
            (unsigned char)alchemy_item(save_data.items[index])->name[0]
        );
        if (initial >= letter) {
            return index;
        }
    }
    return save_data.count - 1;
}

static void init_mouse(void) {
    size_t index;

    for (index = 2; index < cursorA_size; index++) {
        if (cursorA_data[index] == 0) {
            cursorA_data[index] = COLOR_TEXT;
        }
        if (cursorB_data[index] == 0) {
            cursorB_data[index] = COLOR_TEXT;
        }
        if (cursorC_data[index] == 0) {
            cursorC_data[index] = COLOR_TEXT;
        }
        if (cursorD_data[index] == 0) {
            cursorD_data[index] = COLOR_TEXT;
        }
        if (cursorE_data[index] == 0) {
            cursorE_data[index] = COLOR_TEXT;
        }
    }

    oxy_InitMouse();
    oxy_SetMouseSpeed(settings.pointer_speed);
    oxy_mouse.x = 152;
    oxy_mouse.y = 132;
}

static void add_gameplay_hovers(void) {
    size_t index;

    for (index = 0; index < SIDEBAR_ROWS; index++) {
        oxy_AddHover(CANVAS_WIDTH + 13, (uint8_t)(5 + index * 45), 67, 44);
    }
    for (index = 0; index < 26; index++) {
        oxy_AddHover(CANVAS_WIDTH, (uint8_t)(3 + index * 9), 13, 9);
    }
    oxy_AddHover(313, 3, 7, 234);
    oxy_AddHover(TOOL_BUTTON_X, RECYCLE_BUTTON_Y, 24, 24);
    oxy_AddHover(TOOL_BUTTON_X, SETTINGS_BUTTON_Y, 24, 24);
    for (index = 0; index < MAX_CANVAS_ITEMS; index++) {
        oxy_AddHover(0, 0, 0, 0);
    }
    for (index = HOVER_SIDEBAR_FIRST;
         index < HOVER_SIDEBAR_FIRST + SIDEBAR_ROWS; index++) {
        oxy_SetHoverCursors((uint8_t)index, OXY_MOUSE_CURSOR_POINTER,
                            OXY_MOUSE_CURSOR_GRAB);
    }
    oxy_SetHoverCursors(HOVER_SCROLLBAR, OXY_MOUSE_CURSOR_POINTER,
                        OXY_MOUSE_CURSOR_RESIZE_VERTICAL);
    for (index = 0; index < MAX_CANVAS_ITEMS; index++) {
        oxy_SetHoverCursors((uint8_t)(HOVER_CANVAS_FIRST + index),
                            OXY_MOUSE_CURSOR_POINTER,
                            OXY_MOUSE_CURSOR_GRAB);
    }
}

static void update_canvas_hovers(
    const CanvasItem canvas_items[MAX_CANVAS_ITEMS], uint8_t canvas_count
) {
    uint8_t index;

    for (index = 0; index < MAX_CANVAS_ITEMS; index++) {
        if (index < canvas_count) {
            int top = canvas_items[index].y > 4 ? canvas_items[index].y - 4 : 0;
            int height = canvas_items[index].y + 40 - top;
            oxy_SetHoverBounds((uint8_t)(HOVER_CANVAS_FIRST + index),
                               (uint16_t)(canvas_items[index].x - 4),
                               (uint8_t)top, 40, (uint8_t)height);
        } else {
            oxy_SetHoverBounds((uint8_t)(HOVER_CANVAS_FIRST + index),
                               0, 0, 0, 0);
        }
    }
}

static bool pointer_in_play_button(void) {
    return oxy_mouse.x >= PLAY_BUTTON_X &&
           oxy_mouse.x < PLAY_BUTTON_X + PLAY_BUTTON_WIDTH &&
           oxy_mouse.y >= PLAY_BUTTON_Y &&
           oxy_mouse.y < PLAY_BUTTON_Y + PLAY_BUTTON_HEIGHT;
}

static void draw_start_screen(bool play_hovered) {
    unsigned int play_width;

    gfx_SetTransparentColor(COLOR_TRANSPARENT);
    gfx_FillScreen(COLOR_BACKGROUND);
    gfx_SetTextBGColor(COLOR_BACKGROUND);
    gfx_SetTextTransparentColor(COLOR_BACKGROUND);
    gfx_SetTextFGColor(COLOR_TEXT);

    gfx_ScaledTransparentSprite_NoClip(
        (const gfx_sprite_t *)title_logo_sprite,
        (LCD_WIDTH - title_logo_width * TITLE_LOGO_SCALE) / 2, 35,
        TITLE_LOGO_SCALE, TITLE_LOGO_SCALE
    );
    draw_version_label();

    gfx_SetColor(COLOR_ACCENT);
    oxy_FillRoundRectangle(PLAY_BUTTON_X, PLAY_BUTTON_Y,
                           PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT, 0);
    if (play_hovered) {
        gfx_SetColor(COLOR_TEXT);
        oxy_RoundRectangle(PLAY_BUTTON_X - 2, PLAY_BUTTON_Y - 2,
                           PLAY_BUTTON_WIDTH + 4, PLAY_BUTTON_HEIGHT + 4, 0);
    }
    gfx_SetTextFGColor(COLOR_SELECTED_TEXT);
    gfx_SetTextScale(2, 2);
    play_width = gfx_GetStringWidth("PLAY");
    gfx_PrintStringXY("PLAY", PLAY_BUTTON_X + (PLAY_BUTTON_WIDTH - play_width) / 2,
                      PLAY_BUTTON_Y + 15);
    gfx_SetTextScale(1, 1);

    gfx_SetTextFGColor(COLOR_TEXT);
    gfx_PrintStringXY("Your discoveries are saved", 64, 174);
    gfx_BlitBuffer();
}

static bool show_start_screen(void) {
    bool previous_button_down = false;
    bool previous_hover = false;

    oxy_RemoveAllHover();
    oxy_AddHover(PLAY_BUTTON_X, PLAY_BUTTON_Y,
                 PLAY_BUTTON_WIDTH, PLAY_BUTTON_HEIGHT);
    draw_start_screen(false);
    while (true) {
        bool button_down;
        bool play_hovered;

        oxy_RenderMouse();
        button_down = (kb_Data[6] & kb_Enter) || (kb_Data[1] & kb_2nd);
        play_hovered = pointer_in_play_button();
        if (play_hovered != previous_hover) {
            draw_start_screen(play_hovered);
            previous_hover = play_hovered;
        }
        if (play_hovered && button_down && !previous_button_down) {
            oxy_RemoveAllHover();
            return true;
        }
        if (kb_Data[6] & kb_Clear) {
            oxy_RemoveAllHover();
            return false;
        }
        previous_button_down = button_down;
        oxy_ResetMouse();
    }
}

static void show_loading_screen(void) {
    unsigned int percent;
    uint16_t wrap_color = gfx_RGBTo1555(143, 0, 105);

    enum {
        BAR_X = PLAY_BUTTON_X,
        BAR_Y = PLAY_BUTTON_Y,
        BAR_WIDTH = PLAY_BUTTON_WIDTH,
        BAR_HEIGHT = PLAY_BUTTON_HEIGHT,
        WRAP_THICKNESS = 3,
        WRAP_LENGTH = (BAR_WIDTH + BAR_HEIGHT) * 2
    };

    gfx_SetPalette(&wrap_color, sizeof(wrap_color), COLOR_LOADING_WRAP);

    for (percent = 0; percent <= 100; percent++) {
        unsigned int remaining = percent * WRAP_LENGTH / 100;
        unsigned int segment;
        unsigned int percent_width;

        gfx_SetTransparentColor(COLOR_TRANSPARENT);
        gfx_FillScreen(COLOR_BACKGROUND);
        gfx_SetTextBGColor(COLOR_BACKGROUND);
        gfx_SetTextTransparentColor(COLOR_BACKGROUND);
        gfx_SetTextFGColor(COLOR_TEXT);
        gfx_ScaledTransparentSprite_NoClip(
            (const gfx_sprite_t *)title_logo_sprite,
            (LCD_WIDTH - title_logo_width * TITLE_LOGO_SCALE) / 2, 34,
            TITLE_LOGO_SCALE, TITLE_LOGO_SCALE
        );
        draw_version_label();

        gfx_SetColor(COLOR_LOGO_ACCENT);
        gfx_FillRectangle(BAR_X, BAR_Y + WRAP_THICKNESS,
                          BAR_WIDTH - WRAP_THICKNESS,
                          BAR_HEIGHT - WRAP_THICKNESS * 2);

        gfx_SetColor(COLOR_LOADING_WRAP);
        segment = remaining < BAR_WIDTH ? remaining : BAR_WIDTH;
        if (segment > 0) {
            gfx_FillRectangle(BAR_X, BAR_Y, segment, WRAP_THICKNESS);
            remaining -= segment;
        }
        segment = remaining < BAR_HEIGHT ? remaining : BAR_HEIGHT;
        if (segment > 0) {
            gfx_FillRectangle(BAR_X + BAR_WIDTH - WRAP_THICKNESS, BAR_Y,
                              WRAP_THICKNESS, segment);
            remaining -= segment;
        }
        segment = remaining < BAR_WIDTH ? remaining : BAR_WIDTH;
        if (segment > 0) {
            gfx_FillRectangle(BAR_X + BAR_WIDTH - segment,
                              BAR_Y + BAR_HEIGHT - WRAP_THICKNESS,
                              segment, WRAP_THICKNESS);
            remaining -= segment;
        }
        segment = remaining < BAR_HEIGHT ? remaining : BAR_HEIGHT;
        if (segment > 0) {
            gfx_FillRectangle(BAR_X,
                              BAR_Y + BAR_HEIGHT - segment,
                              WRAP_THICKNESS, segment);
        }

        gfx_SetTextFGColor(COLOR_SELECTED_TEXT);
        gfx_SetTextScale(2, 2);
        percent_width = gfx_GetStringWidth(percent < 10 ? "0%" :
                                           percent < 100 ? "00%" : "000%");
        gfx_SetTextXY(BAR_X + (BAR_WIDTH - percent_width) / 2,
                      BAR_Y + 16);
        gfx_PrintUInt(percent, 1);
        gfx_PrintString("%");
        gfx_SetTextScale(1, 1);
        gfx_BlitBuffer();
        delay(12);
    }

    element_sprites_set_palette();
}

static void draw_canvas_item(const CanvasItem *canvas_item, bool selected) {
    const AlchemyItem *item = alchemy_item(canvas_item->item_id);
    unsigned int name_width = gfx_GetStringWidth(item->name);
    int label_x = canvas_item->x + 16 - (int)name_width / 2;

    if (selected) {
        gfx_SetColor(COLOR_ACCENT);
        oxy_RoundRectangle(canvas_item->x - 4, canvas_item->y - 3, 40, 39, 0);
    }
    draw_element_sprite(canvas_item->item_id, canvas_item->x, canvas_item->y);
    if (settings.show_names) {
        gfx_SetTextFGColor(COLOR_TEXT);
        if (label_x < 2) {
            label_x = 2;
        } else if (label_x + (int)name_width >= CANVAS_WIDTH) {
            label_x = CANVAS_WIDTH - name_width - 2;
        }
        gfx_PrintStringXY(item->name, label_x, canvas_item->y + 34);
    }
}

static void draw_sidebar(size_t selected_index, size_t start) {
    size_t row;
    char letter[2] = "A";
    uint8_t thumb_height;
    uint8_t thumb_y;

    gfx_SetColor(COLOR_SELECTED_TEXT);
    gfx_FillRectangle(CANVAS_WIDTH + 12, 0, 76, 240);
    gfx_SetColor(COLOR_TEXT);
    gfx_VertLine(CANVAS_WIDTH, 0, 240);
    gfx_SetTextFGColor(COLOR_TEXT);
    for (row = 0; row < 26; row++) {
        letter[0] = (char)('A' + row);
        if (letter[0] == (char)toupper(
                (unsigned char)alchemy_item(save_data.items[selected_index])->name[0])) {
            gfx_SetTextFGColor(COLOR_ACCENT);
        }
        gfx_PrintStringXY(letter, CANVAS_WIDTH + 3, (uint8_t)(4 + row * 9));
        gfx_SetTextFGColor(COLOR_TEXT);
    }

    for (row = 0; row < SIDEBAR_ROWS && start + row < save_data.count; row++) {
        size_t inventory_index = start + row;
        AlchemyItemId item_id = save_data.items[inventory_index];
        const char *name = alchemy_item(item_id)->name;
        uint8_t y = (uint8_t)(8 + row * 45);
        char short_name[10];

        if (inventory_index == selected_index) {
            gfx_SetColor(COLOR_ACCENT);
            oxy_FillRoundRectangle(CANVAS_WIDTH + 14, y - 2, 65, 43, 0);
            gfx_SetTextFGColor(COLOR_SELECTED_TEXT);
        } else {
            gfx_SetTextFGColor(COLOR_TEXT);
        }
        draw_element_sprite(item_id, CANVAS_WIDTH + 34, y - 2);
        strncpy(short_name, name, sizeof(short_name) - 1);
        short_name[sizeof(short_name) - 1] = '\0';
        gfx_PrintStringXY(short_name, CANVAS_WIDTH + 16, y + 31);
    }

    gfx_SetColor(COLOR_BACKGROUND);
    oxy_FillRoundRectangle(313, 4, 6, 232, 0);
    thumb_height = save_data.count <= SIDEBAR_ROWS
        ? 232 : (uint8_t)(232 * SIDEBAR_ROWS / save_data.count);
    if (thumb_height < 12) {
        thumb_height = 12;
    }
    thumb_y = save_data.count <= SIDEBAR_ROWS
        ? 4
        : (uint8_t)(4 + start * (232 - thumb_height) /
                    (save_data.count - SIDEBAR_ROWS));
    gfx_SetColor(COLOR_ACCENT);
    oxy_FillRoundRectangle(313, thumb_y, 6, thumb_height, 0);

    gfx_RLETSprite_NoClip(recycle_button, TOOL_BUTTON_X, RECYCLE_BUTTON_Y);
    gfx_RLETSprite_NoClip(settings_button, TOOL_BUTTON_X, SETTINGS_BUTTON_Y);
}

typedef struct {
    struct oxy_gtk_form_t form;
    struct oxy_gtk_form_row_t rows[4];
    struct oxy_label_t labels[5];
    struct oxy_checkbox_t checkboxes[3];
    struct oxy_slider_t speed;
    struct oxy_button_t close;
} SettingsForm;

static void init_settings_form(SettingsForm *settings_form,
                               struct gtk_window_t *window) {
    static const char *labels[] = {
        "Show item names", "Show control hints", "Confirm clean canvas",
        "Pointer speed", "Close"
    };
    uint8_t index;

    memset(settings_form, 0, sizeof(*settings_form));
    for (index = 0; index < 5; index++) {
        oxy_InitWidget(&settings_form->labels[index].widget, OXY_LABEL_TYPE);
        oxy_SetLabelText(&settings_form->labels[index].widget, labels[index]);
        oxy_SetWidgetUnselectedColor(&settings_form->labels[index].widget,
                                     COLOR_BACKGROUND, COLOR_TEXT,
                                     COLOR_BACKGROUND);
        oxy_SetWidgetSelectedColor(&settings_form->labels[index].widget,
                       COLOR_BACKGROUND, COLOR_ACCENT,
                       COLOR_BACKGROUND);
        oxy_SetWidgetClickedColor(&settings_form->labels[index].widget,
                      COLOR_BACKGROUND, COLOR_SELECTED_TEXT,
                      COLOR_ACCENT);
    }
    for (index = 0; index < 3; index++) {
        oxy_InitWidget(&settings_form->checkboxes[index].widget,
                       OXY_CHECKBOX_TYPE);
        oxy_SetWidgetUnselectedColor(&settings_form->checkboxes[index].widget,
                                     COLOR_BACKGROUND, COLOR_TEXT,
                                     COLOR_BACKGROUND);
        oxy_SetWidgetSelectedColor(&settings_form->checkboxes[index].widget,
                                   COLOR_ACCENT, COLOR_SELECTED_TEXT,
                                   COLOR_BACKGROUND);
        oxy_SetWidgetClickedColor(&settings_form->checkboxes[index].widget,
                                  COLOR_ACCENT, COLOR_SELECTED_TEXT,
                                  COLOR_BACKGROUND);
        oxy_SetWidgetExtraColors(&settings_form->checkboxes[index].widget,
                                 COLOR_TEXT, COLOR_TEXT, COLOR_BACKGROUND);
        settings_form->rows[index].label = &settings_form->labels[index];
        settings_form->rows[index].control =
            &settings_form->checkboxes[index].widget;
    }
    oxy_InitWidget(&settings_form->speed.widget, OXY_SLIDER_TYPE);
    settings_form->speed.min = 2;
    settings_form->speed.max = 9;
    settings_form->speed.step = 1;
    settings_form->speed.alignment = SCROLLBAR_HORIZONTAL;
    oxy_SetWidgetUnselectedColor(&settings_form->speed.widget,
                                 COLOR_BACKGROUND, COLOR_TEXT,
                                 COLOR_BACKGROUND);
    oxy_SetWidgetSelectedColor(&settings_form->speed.widget,
                               COLOR_ACCENT, COLOR_SELECTED_TEXT,
                               COLOR_BACKGROUND);
    oxy_SetWidgetClickedColor(&settings_form->speed.widget,
                              COLOR_ACCENT, COLOR_SELECTED_TEXT,
                              COLOR_BACKGROUND);
    oxy_SetWidgetExtraColors(&settings_form->speed.widget,
                             COLOR_TEXT, COLOR_ACCENT, COLOR_BACKGROUND);
    settings_form->rows[3].label = &settings_form->labels[3];
    settings_form->rows[3].control = &settings_form->speed.widget;

    oxy_InitWidget(&settings_form->close.widget, OXY_BUTTON_TYPE);
    settings_form->close.label = &settings_form->labels[4];
    oxy_SetWidgetUnselectedColor(&settings_form->close.widget,
                                 COLOR_BACKGROUND, COLOR_TEXT,
                                 COLOR_BACKGROUND);
    oxy_SetWidgetSelectedColor(&settings_form->close.widget,
                               COLOR_ACCENT, COLOR_SELECTED_TEXT,
                               COLOR_BACKGROUND);
    oxy_SetWidgetClickedColor(&settings_form->close.widget,
                              COLOR_ACCENT, COLOR_SELECTED_TEXT,
                              COLOR_BACKGROUND);
    oxy_SetWidgetExtraColors(&settings_form->close.widget,
                             COLOR_TEXT, COLOR_BACKGROUND, COLOR_BACKGROUND);
    oxy_SetWidgetSelectedColor(&settings_form->labels[4].widget,
                               COLOR_ACCENT, COLOR_SELECTED_TEXT,
                               COLOR_ACCENT);
    oxy_SetWidgetClickedColor(&settings_form->labels[4].widget,
                              COLOR_ACCENT, COLOR_SELECTED_TEXT,
                              COLOR_ACCENT);
    oxy_InitGtkForm(&settings_form->form, window, settings_form->rows, 4,
                    &settings_form->close.widget);
    oxy_SetGtkFormSelectionColor(&settings_form->form, COLOR_ACCENT);
    oxy_SetGtkWindowRenderer(window, oxy_RenderGtkForm,
                             &settings_form->form);
    oxy_SetGtkWindowHitTest(window, oxy_GtkFormHitTest,
                            &settings_form->form);
}

static void sync_settings_form(SettingsForm *settings_form) {
    settings_form->checkboxes[0].on = settings.show_names;
    settings_form->checkboxes[1].on = settings.show_hints;
    settings_form->checkboxes[2].on = settings.confirm_clean;
    settings_form->speed.curr_value = settings.pointer_speed;
}

static void show_settings_window(const GameRenderContext *game_context) {
    struct gtk_window_t *window = oxy_CreateWindow("Settings", 28, 24, 264, 180);
    SettingsForm settings_form;
    uint8_t previous_actions = kb_Data[6];
    uint8_t previous_system = kb_Data[1];
    uint8_t previous_arrows = kb_Data[7];
    bool previous_mode = (kb_Data[1] & kb_Mode) != 0;
    bool pointer_mode = false;
    bool open = true;
    bool redraw = true;

    if (window == NULL) {
        return;
    }
    oxy_SetWindowColor(window, COLOR_TEXT, COLOR_BACKGROUND);
    oxy_SetWindowTextColor(window, COLOR_SELECTED_TEXT, COLOR_TEXT);
    oxy_SetGtkWindowFeatures(window, true, false, false, false);
    oxy_SetGtkWindowMinimumSize(window, 150, 90);
    init_settings_form(&settings_form, window);
    sync_settings_form(&settings_form);
    oxy_SetGtkWindowManagerBackground(draw_game_background, (void *)game_context);

    while (open) {
        uint8_t actions;
        uint8_t system;
        uint8_t arrows;
        bool mode_down;
        bool activate;
        bool action_down;
        bool window_handled = false;
        int pointer_target = -1;

        if (redraw) {
            sync_settings_form(&settings_form);
            oxy_RenderGtkWindows();
            gfx_BlitBuffer();
            redraw = false;
        }
        oxy_UpdateGtkWindow(window);
        if (pointer_mode) {
            oxy_RenderMouse();
        } else {
            kb_Scan();
        }
        actions = kb_Data[6];
        system = kb_Data[1];
        arrows = kb_Data[7];
        mode_down = (system & kb_Mode) != 0;
        activate = ((actions & kb_Enter) || (system & kb_2nd)) &&
                   !((previous_actions & kb_Enter) ||
                     (previous_system & kb_2nd));
                action_down = (actions & kb_Enter) || (system & kb_2nd);

        if (mode_down && !previous_mode) {
            pointer_mode = !pointer_mode;
            redraw = true;
        }

        if (pointer_mode) {
            window_handled = oxy_UpdateGtkWindowManager(
                oxy_mouse.x, oxy_mouse.y, action_down
            );
            open = window->widget.state.visible;
            if (oxy_GtkWindowManagerNeedsRedraw()) redraw = true;
            pointer_target = oxy_GtkFormRowAt(
                &settings_form.form, oxy_mouse.x, oxy_mouse.y);
            if (pointer_target >= 0 && pointer_target < 5 &&
                settings_form.form.selected_row != pointer_target) {
                oxy_SetGtkFormSelection(&settings_form.form,
                                        (uint8_t)pointer_target);
                redraw = true;
            }
        } else {
            oxy_UpdateGtkWindowManager(oxy_mouse.x, oxy_mouse.y, false);
            if ((arrows & kb_Up) && !(previous_arrows & kb_Up)) {
                uint8_t selected = settings_form.form.selected_row;
                oxy_SetGtkFormSelection(&settings_form.form,
                                        selected == 0 ? 4 : selected - 1);
                redraw = true;
            } else if ((arrows & kb_Down) && !(previous_arrows & kb_Down)) {
                oxy_SetGtkFormSelection(
                    &settings_form.form,
                    (uint8_t)((settings_form.form.selected_row + 1) % 5));
                redraw = true;
            }
        }
        if (activate && !window_handled) {
            int target = pointer_mode ? pointer_target
                                      : settings_form.form.selected_row;

            if (target == 0) {
                settings.show_names = !settings.show_names;
                redraw = true;
            } else if (target == 1) {
                settings.show_hints = !settings.show_hints;
                redraw = true;
            } else if (target == 2) {
                settings.confirm_clean = !settings.confirm_clean;
                redraw = true;
            } else if (target == 3 && pointer_mode) {
                int track_width = settings_form.speed.widget.size.width - 28;
                int position = oxy_mouse.x -
                               settings_form.speed.widget.position.x;
                if (position < 0) position = 0;
                if (position > track_width) position = track_width;
                settings.pointer_speed = track_width > 0
                    ? (uint8_t)(2 + 7 * position / track_width) : 2;
                oxy_SetMouseSpeed(settings.pointer_speed);
                redraw = true;
            } else if (target == 4) {
                open = false;
            }
        }
        if (!pointer_mode && settings_form.form.selected_row == 3 &&
            (arrows & kb_Left) &&
            !(previous_arrows & kb_Left) && settings.pointer_speed > 2) {
            settings.pointer_speed--;
            oxy_SetMouseSpeed(settings.pointer_speed);
            redraw = true;
        } else if (!pointer_mode && settings_form.form.selected_row == 3 &&
               (arrows & kb_Right) &&
                   !(previous_arrows & kb_Right) && settings.pointer_speed < 9) {
            settings.pointer_speed++;
            oxy_SetMouseSpeed(settings.pointer_speed);
            redraw = true;
        }
        if (!pointer_mode) {
            if (oxy_EnsureGtkFormSelectionVisible(&settings_form.form))
                redraw = true;
        }
        previous_actions = actions;
        previous_system = system;
        previous_arrows = arrows;
        previous_mode = mode_down;
    }
    save_settings();
    oxy_DestroyWindow(window);
    oxy_SetGtkWindowManagerBackground(NULL, NULL);
    draw_game_background((void *)game_context);
    gfx_BlitBuffer();
    while (kb_AnyKey()) {
        kb_Scan();
    }
}

static void draw_result(const AlchemyItemId results[MAX_RESULTS],
                        ResultState result_state) {
    const char *message;
    const char *result_name;
    int result_name_x;

    gfx_SetTextFGColor(COLOR_TEXT);
    if (result_state == RESULT_READY) {
        return;
    } else if (result_state == RESULT_NONE) {
        gfx_PrintStringXY("nothing happened", 8, 187);
        return;
    } else if (result_state == RESULT_NEW) {
        message = "new: ";
    } else {
        message = "known: ";
    }
    gfx_PrintStringXY(message, 8, 187);
    result_name = alchemy_item(results[0])->name;
    result_name_x = 16 + (int)gfx_GetStringWidth(message);
    gfx_PrintStringXY(result_name, result_name_x, 187);
}

static int canvas_item_at(const CanvasItem items[MAX_CANVAS_ITEMS],
                          uint8_t count, int x, int y, int ignored_index) {
    int index;

    for (index = (int)count - 1; index >= 0; index--) {
        if (index != ignored_index &&
            x >= items[index].x - 4 && x < items[index].x + 36 &&
            y >= items[index].y - 4 && y < items[index].y + 40) {
            return index;
        }
    }
    return -1;
}

static int overlapping_canvas_item(
    const CanvasItem items[MAX_CANVAS_ITEMS], uint8_t count,
    int x, int y, int ignored_index
) {
    int index;

    for (index = (int)count - 1; index >= 0; index--) {
        if (index != ignored_index && x < items[index].x + 32 &&
            x + 32 > items[index].x && y < items[index].y + 32 &&
            y + 32 > items[index].y) {
            return index;
        }
    }
    return -1;
}

static void clamp_canvas_position(int *x, int *y) {
    if (*x < 4) {
        *x = 4;
    } else if (*x > CANVAS_WIDTH - 36) {
        *x = CANVAS_WIDTH - 36;
    }
    if (*y < CANVAS_TOP) {
        *y = CANVAS_TOP;
    } else if (*y > CANVAS_BOTTOM - CANVAS_ITEM_HEIGHT) {
        *y = CANVAS_BOTTOM - CANVAS_ITEM_HEIGHT;
    }
    if (*x + CANVAS_ITEM_WIDTH > TOOL_BUTTON_X &&
        *y + CANVAS_ITEM_HEIGHT > RECYCLE_BUTTON_Y) {
        *x = TOOL_BUTTON_X - CANVAS_ITEM_WIDTH;
    }
}

static void remove_canvas_item(CanvasItem items[MAX_CANVAS_ITEMS],
                               uint8_t *count, uint8_t index) {
    while (index + 1 < *count) {
        items[index] = items[index + 1];
        index++;
    }
    (*count)--;
}

static size_t sidebar_start_for_mouse(int y) {
    size_t maximum = save_data.count > SIDEBAR_ROWS
        ? save_data.count - SIDEBAR_ROWS : 0;
    int thumb_height;
    int travel;
    int position;

    if (maximum == 0) {
        return 0;
    }
    thumb_height = 232 * SIDEBAR_ROWS / save_data.count;
    if (thumb_height < 12) thumb_height = 12;
    travel = 232 - thumb_height;
    position = y - 4 - thumb_height / 2;
    if (position < 0) position = 0;
    if (position > travel) position = travel;
    return travel > 0 ? (size_t)position * maximum / travel : 0;
}

static void draw_screen_contents(const GameRenderContext *context) {
    const CanvasItem *canvas_items = context->canvas_items;
    uint8_t canvas_count = context->canvas_count;
    int selected_canvas_index = context->selected_canvas_index;
    size_t selected_inventory_index = context->selected_inventory_index;
    size_t sidebar_offset = context->sidebar_offset;
    const AlchemyItemId *results = context->results;
    ResultState result_state = context->result_state;
    bool confirm_reset = context->confirm_reset;
    bool confirm_clean = context->confirm_clean;
    const DragState *drag = context->drag;
    uint8_t index;

    gfx_SetTransparentColor(COLOR_TRANSPARENT);
    gfx_FillScreen(COLOR_BACKGROUND);
    gfx_SetTextBGColor(COLOR_BACKGROUND);
    gfx_SetTextTransparentColor(COLOR_BACKGROUND);
    gfx_SetTextFGColor(COLOR_TEXT);
    for (index = 0; index < canvas_count; index++) {
        if (drag->source != DRAG_CANVAS || index != drag->canvas_index) {
            draw_canvas_item(&canvas_items[index], index == selected_canvas_index);
        }
    }
    gfx_RLETSprite_NoClip(title_icon, 7, 4);
    gfx_SetTextFGColor(COLOR_TEXT);
    gfx_PrintStringXY(APP_TITLE_WITH_VERSION, 26, 9);
    draw_result(results, result_state);
    draw_sidebar(selected_inventory_index, sidebar_offset);

    if (drag->source == DRAG_CANVAS || drag->source == DRAG_SIDEBAR) {
        int drag_x = oxy_mouse.x - 16;
        int drag_y = oxy_mouse.y - 16;
        if (drag_x < 0) {
            drag_x = 0;
        }
        if (drag_y < 0) {
            drag_y = 0;
        }
        draw_element_sprite(drag->item_id, drag_x, drag_y);
    }

    gfx_SetTextFGColor(COLOR_TEXT);
    gfx_SetTextScale(2, 2);
    gfx_SetTextXY(8, 204);
    gfx_PrintUInt(save_data.count, 1);
    gfx_PrintString("/580");
    gfx_SetTextScale(1, 1);

    gfx_SetTextFGColor(COLOR_TEXT);
    if (confirm_clean) {
        gfx_PrintStringXY("Clean again clears canvas", 8, 228);
    } else if (confirm_reset) {
        gfx_PrintStringXY("DEL again resets progress", 8, 228);
    } else if (settings.show_hints && drag->source != DRAG_NONE) {
        gfx_PrintStringXY("Drop empty; overlap to mix", 8, 228);
    } else if (settings.show_hints) {
        gfx_PrintStringXY("Hold ENTER/2nd to drag", 8, 228);
    }
    gfx_SetTransparentColor(COLOR_TRANSPARENT);
}

static void draw_screen(
    const CanvasItem canvas_items[MAX_CANVAS_ITEMS],
    uint8_t canvas_count,
    int selected_canvas_index,
    size_t selected_inventory_index,
    size_t sidebar_offset,
    const AlchemyItemId results[MAX_RESULTS],
    ResultState result_state,
    bool confirm_reset,
    bool confirm_clean,
    const DragState *drag
) {
    GameRenderContext context = {
        canvas_items, canvas_count, selected_canvas_index,
        selected_inventory_index, sidebar_offset, results, result_state,
        confirm_reset, confirm_clean, drag
    };

    draw_screen_contents(&context);
    gfx_BlitBuffer();
}

static bool combine_items(AlchemyItemId first, AlchemyItemId second,
                          AlchemyItemId results[MAX_RESULTS],
                          ResultState *result_state) {
    bool found_new = false;
    size_t index;
    size_t result_count;
    size_t stored_count;

    result_count = alchemy_combine(first, second, results, MAX_RESULTS);
    if (result_count == 0) {
        *result_state = RESULT_NONE;
        return false;
    }

    stored_count = result_count < MAX_RESULTS ? result_count : MAX_RESULTS;
    for (index = 0; index < stored_count; index++) {
        if (!discovered[results[index]]) {
            found_new = true;
        }
        unlock_item(results[index]);
    }
    sort_inventory();
    *result_state = found_new ? RESULT_NEW : RESULT_KNOWN;
    if (found_new) {
        save_game();
    }
    return true;
}

int main(void) {
    CanvasItem canvas_items[MAX_CANVAS_ITEMS];
    uint8_t canvas_count = 0;
    int selected_canvas_index = -1;
    size_t selected_inventory_index = 0;
    size_t sidebar_offset = 0;
    AlchemyItemId results[MAX_RESULTS] = {0};
    uint8_t previous_actions = 0;
    uint8_t previous_system = 0;
    ResultState result_state = RESULT_READY;
    DragState drag = {DRAG_NONE, ALCHEMY_INVALID_ITEM, 0};
    bool confirm_reset = false;
    bool confirm_clean = false;
    bool needs_redraw = true;
    bool running = true;

    if (!element_sprites_init()) {
        gfx_Begin();
        gfx_SetTextFGColor(1);
        gfx_SetTextBGColor(0);
        gfx_FillScreen(0);
        gfx_PrintStringXY("Missing ALCHM00-ALCHM09 AppVars", 20, 100);
        gfx_PrintStringXY("Install all sprite packs.", 20, 120);
        while (kb_AnyKey()) {
            kb_Scan();
        }
        while (!kb_AnyKey()) {
            kb_Scan();
        }
        gfx_End();
        return 1;
    }

    load_settings();
    if (!load_game()) {
        new_game();
        save_game();
    }

    /* Decompress the ZX7-compressed title logo once for scaled draws. */
    zx7_Decompress(title_logo_sprite, title_logo_compressed);

    gfx_Begin();
    gfx_SetDrawBuffer();
    element_sprites_set_palette();
    gfx_SetTransparentColor(COLOR_TRANSPARENT);
    init_mouse();
    if (!show_start_screen()) {
        gfx_End();
        return 0;
    }
    show_loading_screen();
    add_gameplay_hovers();

    while (running) {
        uint8_t actions;
        uint8_t system;
        int clicked_hover;
        bool button_down;
        bool click_pressed;
        bool click_released;

        if (needs_redraw) {
            update_canvas_hovers(canvas_items, canvas_count);
            draw_screen(canvas_items, canvas_count, selected_canvas_index,
                        selected_inventory_index, sidebar_offset, results,
                        result_state, confirm_reset, confirm_clean, &drag);
            needs_redraw = false;
        }

        oxy_RenderMouse();
        actions = kb_Data[6];
        system = kb_Data[1];
        clicked_hover = oxy_ReturnClickedIndex();
        button_down = (actions & kb_Enter) || (system & kb_2nd);
        click_pressed = button_down &&
                        !((previous_actions & kb_Enter) || (previous_system & kb_2nd));
        click_released = !button_down &&
                         ((previous_actions & kb_Enter) || (previous_system & kb_2nd));

        if (click_pressed) {
            int canvas_index = canvas_item_at(
                canvas_items, canvas_count, oxy_mouse.x, oxy_mouse.y, -1
            );

            if (clicked_hover == HOVER_RECYCLE) {
                if (!settings.confirm_clean || confirm_clean) {
                    canvas_count = 0;
                    selected_canvas_index = -1;
                    result_state = RESULT_READY;
                    confirm_clean = false;
                } else if (canvas_count > 0) {
                    confirm_clean = true;
                }
            } else if (clicked_hover == HOVER_SETTINGS) {
                GameRenderContext context = {
                    canvas_items, canvas_count, selected_canvas_index,
                    selected_inventory_index, sidebar_offset, results,
                    result_state, confirm_reset, confirm_clean, &drag
                };
                show_settings_window(&context);
            } else if (canvas_index >= 0 && oxy_mouse.x < CANVAS_WIDTH) {
                selected_canvas_index = canvas_index;
                drag.source = DRAG_CANVAS;
                drag.canvas_index = (uint8_t)canvas_index;
                drag.item_id = canvas_items[canvas_index].item_id;
            } else if (clicked_hover >= HOVER_SIDEBAR_FIRST &&
                       clicked_hover < HOVER_SIDEBAR_FIRST + SIDEBAR_ROWS) {
                size_t inventory_index = sidebar_offset +
                    (size_t)(clicked_hover - HOVER_SIDEBAR_FIRST);
                if (inventory_index < save_data.count) {
                    selected_inventory_index = inventory_index;
                    drag.source = DRAG_SIDEBAR;
                    drag.item_id = save_data.items[inventory_index];
                }
            } else if (clicked_hover >= HOVER_ALPHABET_FIRST &&
                       clicked_hover < HOVER_ALPHABET_FIRST + 26) {
                char letter = (char)('A' + clicked_hover - HOVER_ALPHABET_FIRST);
                selected_inventory_index = inventory_index_for_letter(letter);
                sidebar_offset = sidebar_start(selected_inventory_index);
                result_state = RESULT_READY;
            } else if (clicked_hover == HOVER_SCROLLBAR) {
                drag.source = DRAG_SCROLLBAR;
                sidebar_offset = sidebar_start_for_mouse(oxy_mouse.y);
            }
            if (clicked_hover != HOVER_RECYCLE) {
                confirm_clean = false;
            }
            if (clicked_hover != HOVER_SETTINGS) {
                confirm_reset = false;
            }
            needs_redraw = true;
        }
        if (drag.source == DRAG_SCROLLBAR && button_down) {
            sidebar_offset = sidebar_start_for_mouse(oxy_mouse.y);
            needs_redraw = true;
        } else if (drag.source != DRAG_NONE && button_down) {
            needs_redraw = true;
        }
        if (drag.source != DRAG_NONE && click_released) {
            if (drag.source != DRAG_SCROLLBAR && oxy_mouse.x < CANVAS_WIDTH &&
                oxy_mouse.y >= CANVAS_TOP && oxy_mouse.y < CANVAS_BOTTOM) {
                int drop_x = oxy_mouse.x - 16;
                int drop_y = oxy_mouse.y - 16;
                int ignored_index = drag.source == DRAG_CANVAS
                    ? drag.canvas_index : -1;
                int target_index;

                clamp_canvas_position(&drop_x, &drop_y);
                target_index = overlapping_canvas_item(
                    canvas_items, canvas_count, drop_x, drop_y, ignored_index
                );
                if (target_index >= 0) {
                    if (combine_items(drag.item_id,
                                      canvas_items[target_index].item_id,
                                      results, &result_state)) {
                        canvas_items[target_index].item_id = results[0];
                        selected_inventory_index = inventory_index_of(results[0]);
                        sidebar_offset = sidebar_start(selected_inventory_index);
                        selected_canvas_index = target_index;
                        if (drag.source == DRAG_CANVAS) {
                            if (drag.canvas_index < target_index) {
                                selected_canvas_index--;
                            }
                            remove_canvas_item(canvas_items, &canvas_count,
                                               drag.canvas_index);
                        }
                    }
                } else if (drag.source == DRAG_CANVAS) {
                    canvas_items[drag.canvas_index].x = drop_x;
                    canvas_items[drag.canvas_index].y = drop_y;
                    selected_canvas_index = drag.canvas_index;
                    result_state = RESULT_READY;
                } else if (canvas_count < MAX_CANVAS_ITEMS) {
                    canvas_items[canvas_count].item_id = drag.item_id;
                    canvas_items[canvas_count].x = drop_x;
                    canvas_items[canvas_count].y = drop_y;
                    selected_canvas_index = canvas_count;
                    canvas_count++;
                    result_state = RESULT_READY;
                }
            }

            drag.source = DRAG_NONE;
            drag.item_id = ALCHEMY_INVALID_ITEM;
            confirm_reset = false;
            confirm_clean = false;
            needs_redraw = true;
        }
        if ((actions & kb_Sub) && !(previous_actions & kb_Sub)) {
            selected_inventory_index = move_inventory_index(
                selected_inventory_index, -SIDEBAR_ROWS
            );
            sidebar_offset = sidebar_start(selected_inventory_index);
            result_state = RESULT_READY;
            confirm_reset = false;
            confirm_clean = false;
            needs_redraw = true;
        }
        if ((actions & kb_Add) && !(previous_actions & kb_Add)) {
            selected_inventory_index = move_inventory_index(
                selected_inventory_index, SIDEBAR_ROWS
            );
            sidebar_offset = sidebar_start(selected_inventory_index);
            result_state = RESULT_READY;
            confirm_reset = false;
            confirm_clean = false;
            needs_redraw = true;
        }
        if ((system & kb_Del) && !(previous_system & kb_Del)) {
            if (confirm_reset) {
                new_game();
                save_game();
                canvas_count = 0;
                selected_canvas_index = -1;
                selected_inventory_index = 0;
                sidebar_offset = 0;
                result_state = RESULT_READY;
                confirm_reset = false;
            } else {
                confirm_reset = true;
            }
            needs_redraw = true;
        }
        if (actions & kb_Clear) {
            save_game();
            running = false;
        }

        oxy_ResetMouse();
        previous_actions = actions;
        previous_system = system;
    }

    gfx_End();
    return 0;
}
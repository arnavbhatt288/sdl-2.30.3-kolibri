
#include "../../SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_KOLIBRI

#include <sys/ksys.h>

#include "SDL.h"

#include "../../events/SDL_events_c.h"
#include "../../events/SDL_keyboard_c.h"
#include "../SDL_sysvideo.h"

#include "SDL_kolibrievents.h"
#include "SDL_kolibrivideo.h"
#include "SDL_kolibriwindow.h"

static SDL_Keycode sdlkeys[0x80] = {
    // 0x0*
    0, SDLK_ESCAPE, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6,
    SDLK_7, SDLK_8, SDLK_9, SDLK_0, SDLK_MINUS, SDLK_EQUALS, SDLK_BACKSPACE, SDLK_TAB,
    // 0x1*
    SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i,
    SDLK_o, SDLK_p, SDLK_LEFTBRACKET, SDLK_RIGHTBRACKET, SDLK_RETURN, SDLK_LCTRL, SDLK_a, SDLK_s,
    // 0x2*
    SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k, SDLK_l, SDLK_SEMICOLON,
    SDLK_QUOTE, SDLK_BACKQUOTE, SDLK_LSHIFT, SDLK_BACKSLASH, SDLK_z, SDLK_x, SDLK_c, SDLK_v,
    // 0x3*
    SDLK_b, SDLK_n, SDLK_m, SDLK_COMMA, SDLK_PERIOD, SDLK_SLASH, SDLK_RSHIFT, SDLK_KP_MULTIPLY,
    SDLK_LALT, SDLK_SPACE, SDLK_CAPSLOCK, SDLK_F1, SDLK_F2, SDLK_F3, SDLK_F4, SDLK_F5,
    // 0x4*
    SDLK_F6, SDLK_F7, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_NUMLOCKCLEAR, SDLK_SCROLLLOCK, SDLK_KP_7,
    SDLK_KP_8, SDLK_KP_9, SDLK_KP_MINUS, SDLK_KP_4, SDLK_KP_5, SDLK_KP_6, SDLK_KP_PLUS, SDLK_KP_1,
    // 0x5*
    SDLK_KP_2, SDLK_KP_3, SDLK_KP_0, SDLK_KP_PERIOD, 0, 0, 0, SDLK_F11,
    SDLK_F12, 0, 0, 0, 0, 0, 0, 0,
    // 0x6*
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    // 0x7*
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

static SDL_Keycode sdlkeys_shift[0x80] = {
    // 0x0*
    0, SDLK_ESCAPE, SDLK_EXCLAIM, SDLK_AT, SDLK_HASH, SDLK_DOLLAR, '%', SDLK_CARET,
    SDLK_AMPERSAND, SDLK_ASTERISK, SDLK_LEFTPAREN, SDLK_RIGHTPAREN, SDLK_UNDERSCORE, SDLK_PLUS, SDLK_BACKSPACE, SDLK_TAB,
    // 0x1*
    SDLK_q, SDLK_w, SDLK_e, SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i,
    SDLK_o, SDLK_p, '{', '}', SDLK_RETURN, SDLK_LCTRL, SDLK_a, SDLK_s,
    // 0x2*
    SDLK_d, SDLK_f, SDLK_g, SDLK_h, SDLK_j, SDLK_k, SDLK_l, SDLK_COLON,
    SDLK_QUOTEDBL, '~', SDLK_LSHIFT, '|', SDLK_z, SDLK_x, SDLK_c, SDLK_v,
    // 0x3*
    SDLK_b, SDLK_n, SDLK_m, SDLK_LESS, SDLK_GREATER, SDLK_QUESTION, SDLK_RSHIFT, SDLK_KP_MULTIPLY,
    SDLK_LALT, SDLK_SPACE, SDLK_CAPSLOCK, SDLK_F1, SDLK_F2, SDLK_F3, SDLK_F4, SDLK_F5,
    // 0x4*
    SDLK_F6, SDLK_F7, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_NUMLOCKCLEAR, SDLK_SCROLLLOCK, SDLK_KP_7,
    SDLK_KP_8, SDLK_KP_9, SDLK_KP_MINUS, SDLK_KP_4, SDLK_KP_5, SDLK_KP_6, SDLK_KP_PLUS, SDLK_KP_1,
    // 0x5*
    SDLK_KP_2, SDLK_KP_3, SDLK_KP_0, SDLK_KP_PERIOD, 0, 0, 0, SDLK_F11,
    SDLK_F12, 0, 0, 0, 0, 0, 0, 0,
    // 0x6*
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    // 0x7*
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

static SDL_Keycode sdlkeys_e0[0x80] = {
    // 0x0*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // 0x1*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SDLK_KP_ENTER,
    SDLK_RCTRL,
    0,
    0,
    // 0x2*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // 0x3*
    0,
    0,
    0,
    0,
    0,
    SDLK_KP_DIVIDE,
    0,
    SDLK_PRINTSCREEN,
    SDLK_RALT,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // 0x4*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SDLK_HOME,
    SDLK_UP,
    SDLK_PAGEUP,
    0,
    SDLK_LEFT,
    0,
    SDLK_RIGHT,
    0,
    SDLK_END,
    // 0x5*
    SDLK_DOWN,
    SDLK_PAGEDOWN,
    SDLK_INSERT,
    SDLK_DELETE,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    SDLK_MENU,
    0,
    0,
    // 0x6*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    // 0x7*
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};

static SDL_Keymod SDL_KOLIBRI_get_mod_state(void)
{
    unsigned controlstate = _ksys_get_control_key_state();
    SDL_Keymod res = 0;
    if (controlstate & KSYS_CONTROL_LSHIFT)
        res |= KMOD_LSHIFT;
    if (controlstate & KSYS_CONTROL_RSHIFT)
        res |= KMOD_RSHIFT;
    if (controlstate & KSYS_CONTROL_LCTRL)
        res |= KMOD_LCTRL;
    if (controlstate & KSYS_CONTROL_RCTRL)
        res |= KMOD_RCTRL;
    if (controlstate & KSYS_CONTROL_LALT)
        res |= KMOD_LALT;
    if (controlstate & KSYS_CONTROL_RALT)
        res |= KMOD_RALT;
    if (controlstate & KSYS_CONTROL_CAPS)
        res |= KMOD_CAPS;
    if (controlstate & KSYS_CONTROL_NUM_LOCK)
        res |= KMOD_NUM;
    return res;
}

void KOLIBRI_InitOSKeymap(void)
{
    _ksys_set_key_input_mode(KSYS_KEY_INPUT_MODE_SCANC);
}

extern void kos_CheckMouseMode(_THIS);

void KOLIBRI_PumpEvents(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->driverdata;
    SDL_Window *window = SDL_GetWindowFromID(data->window_id);
    uint32_t kos_event;
    ksys_pos_t mouse_pos;
    ksys_pos_t center_pos;
    ksys_thread_t thread_info;
    int scancode = 0;
    int pressed = 0;
    SDL_Keycode keycode = SDLK_UNKNOWN;
    SDL_Keymod mod = 0;
    static int ext_code = 0;
    static uint8_t old_mode = 0;
    static uint32_t old_mouse_but = 0;

    while (1) {
        kos_event = _ksys_check_event();
        switch (kos_event) {
        case KSYS_EVENT_NONE:
            return;
        case KSYS_EVENT_REDRAW:
            KOLIBRI_RepaintWnd(_this);
            break;
        case KSYS_EVENT_KEY:
            scancode = _ksys_get_key().code;
            if (scancode == 0xE0 || scancode == 0xE1) {
                ext_code = scancode;
                break;
            }
            if (ext_code == 0xE1 && (scancode & 0x7F) == 0x1D) {
                break;
            }
            if (ext_code == 0xE1 && scancode == 0xC5) {
                ext_code = 0;
                break;
            }

            mod = SDL_KOLIBRI_get_mod_state();
            if (ext_code == 0xE1)
                mod &= ~KMOD_CTRL;
            if (!(scancode & 0x80))
                old_mode = mod;
            SDL_SetModState(mod);

            pressed = (scancode & 0x80) ? SDL_RELEASED : SDL_PRESSED;
            scancode &= 0x7F;

            if (ext_code == 0xE1 && scancode == 0x45)
                keycode = SDLK_PAUSE;
            else if (ext_code == 0xE0)
                keycode = sdlkeys_e0[scancode];
            else if (old_mode & KMOD_SHIFT)
                keycode = sdlkeys_shift[scancode];
            else
                keycode = sdlkeys[scancode];

            ext_code = 0;
            if (!keycode)
                break;

            SDL_SendKeyboardKey(pressed, SDL_GetScancodeFromKey(keycode));
            break;
        case KSYS_EVENT_BUTTON:
            if (_ksys_get_button() == 1)
                exit(0);
            break;
        case KSYS_EVENT_MOUSE:
        {
            mouse_pos = _ksys_get_mouse_pos(KSYS_MOUSE_WINDOW_POS);
            if (mouse_pos.x >= 0 && mouse_pos.x < window->w && mouse_pos.y >= 0 && mouse_pos.y < window->h || SDL_GetMouse()->relative_mode) {
                if (SDL_GetMouse()->relative_mode) {
                    center_pos.x = mouse_pos.x - window->w / 2;
                    center_pos.y = mouse_pos.y - window->h / 2;
                    if (center_pos.x || center_pos.y) {
                        SDL_SendMouseMotion(window, 0, SDL_TRUE, center_pos.x, center_pos.y);

                        int top = _ksys_thread_info(&thread_info, KSYS_THIS_SLOT);
                        if (top == thread_info.pos_in_window_stack) {
                            int x = thread_info.winx_start + thread_info.clientx + window->w / 2;
                            int y = thread_info.winy_start + thread_info.clienty + window->h / 2;
                            _ksys_set_mouse_pos(x, y);
                        }
                    }
                } else
                    SDL_SendMouseMotion(window, 0, SDL_FALSE, mouse_pos.x, mouse_pos.y);

                uint32_t mouse_but = _ksys_get_mouse_buttons();
                if ((mouse_but ^ old_mouse_but) & KSYS_MOUSE_LBUTTON_PRESSED) {
                    if (mouse_but & KSYS_MOUSE_LBUTTON_PRESSED)
                        SDL_SendMouseButton(window, 0, SDL_PRESSED, SDL_BUTTON_LEFT);
                    else
                        SDL_SendMouseButton(window, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
                }

                if ((mouse_but ^ old_mouse_but) & KSYS_MOUSE_RBUTTON_PRESSED) {
                    if (mouse_but & KSYS_MOUSE_RBUTTON_PRESSED)
                        SDL_SendMouseButton(window, 0, SDL_PRESSED, SDL_BUTTON_RIGHT);
                    else
                        SDL_SendMouseButton(window, 0, SDL_RELEASED, SDL_BUTTON_RIGHT);
                }

                if ((mouse_but ^ old_mouse_but) & KSYS_MOUSE_MBUTTON_PRESSED) {
                    if (mouse_but & KSYS_MOUSE_MBUTTON_PRESSED)
                        SDL_SendMouseButton(window, 0, SDL_PRESSED, SDL_BUTTON_MIDDLE);
                    else
                        SDL_SendMouseButton(window, 0, SDL_RELEASED, SDL_BUTTON_MIDDLE);
                }

                old_mouse_but = mouse_but;
            }
        }
        }
    }
}

#endif

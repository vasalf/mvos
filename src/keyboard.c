#include <keyboard.h>
#include <ports.h>
#include <stdio.h>
#include <system.h>
#include <string.h>
#include <timer.h>
#include <asm/keyboard.h>
#include <kvirtmem.h>

uint16_t keyboard_port;

static void parse_kbd_signal(uint8_t x);

void keyboard_irq(void)
{
    uint8_t signal;
    signal = inb(keyboard_port);
#ifdef VERBOSE_KEYBOARD
    printf("keyboard_irq called.\n");
    printf("Keyboard sent %#4hhX\n", signal);
#endif
    parse_kbd_signal(signal);
#ifdef VERBOSE_UPTIME
    printf("Uptime: %ds\n", uptime / TIMER_FREQ);
#endif
}

void check_keyboard(void)
{
    if (iob(keyboard_port, 0xee) == 0xfe)
        panic("Keyboard not found at port %#hhX", keyboard_port);
}

keyboard_locks_t keyboard_locks;
bool* kbd_currently_pressed;

void init_keyboard(void)
{
    keyboard_port = 0x60;
    check_keyboard();
    isr_register_handler(0x21, _asm_keyboard_irq);
    kbd_currently_pressed = kcalloc(sizeof(bool), KBD_SCANCODE_QUAN);
}

static void parse_kbd_signal(uint8_t x)
{
    bool val = x < 0x80;
    if (!val)
        x -= 0x80;
    switch(x)
    {
        case 0x01:
            kbd_currently_pressed[KBD_SCANCODE_ESC] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_ESC\n");
#endif
            break;
        case 0x02:
            kbd_currently_pressed[KBD_SCANCODE_1] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_1\n");
#endif
            break;
        case 0x03:
            kbd_currently_pressed[KBD_SCANCODE_2] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_2\n");
#endif
            break;
        case 0x04:
            kbd_currently_pressed[KBD_SCANCODE_3] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_3\n");
#endif
            break;
        case 0x05:
            kbd_currently_pressed[KBD_SCANCODE_4] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_4\n");
#endif
            break;
        case 0x06:
            kbd_currently_pressed[KBD_SCANCODE_5] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_5\n");
#endif
            break;
        case 0x07:
            kbd_currently_pressed[KBD_SCANCODE_6] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_6\n");
#endif
            break;
        case 0x08:
            kbd_currently_pressed[KBD_SCANCODE_7] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_7\n");
#endif
            break;
        case 0x09:
            kbd_currently_pressed[KBD_SCANCODE_8] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_8\n");
#endif
            break;
        case 0x0A:
            kbd_currently_pressed[KBD_SCANCODE_9] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_9\n");
#endif
            break;
        case 0x0B:
            kbd_currently_pressed[KBD_SCANCODE_0] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_0\n");
#endif
            break;
        case 0x0C:
            kbd_currently_pressed[KBD_SCANCODE_MINUS] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_MINUS\n");
#endif
            break;
        case 0x0D:
            kbd_currently_pressed[KBD_SCANCODE_EQUAL] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_EQUAL\n");
#endif
            break;
        case 0x0E:
            kbd_currently_pressed[KBD_SCANCODE_BACKSPACE] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_BACKSPACE\n");
#endif
            break;
        case 0x0F:
            kbd_currently_pressed[KBD_SCANCODE_TAB] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_TAB\n");
#endif
            break;
        case 0x10:
            kbd_currently_pressed[KBD_SCANCODE_Q] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_Q\n");
#endif
            break;
        case 0x11:
            kbd_currently_pressed[KBD_SCANCODE_W] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_W\n");
#endif
            break;
        case 0x12:
            kbd_currently_pressed[KBD_SCANCODE_E] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_E\n");
#endif
            break;
        case 0x13:
            kbd_currently_pressed[KBD_SCANCODE_R] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_R\n");
#endif
            break;
        case 0x14:
            kbd_currently_pressed[KBD_SCANCODE_T] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_T\n");
#endif
            break;
        case 0x15:
            kbd_currently_pressed[KBD_SCANCODE_Y] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_Y\n");
#endif
            break;
        case 0x16:
            kbd_currently_pressed[KBD_SCANCODE_U] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_U\n");
#endif
            break;
        case 0x17:
            kbd_currently_pressed[KBD_SCANCODE_I] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_I\n");
#endif
            break;
        case 0x18:
            kbd_currently_pressed[KBD_SCANCODE_O] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_O\n");
#endif
            break;
        case 0x19:
            kbd_currently_pressed[KBD_SCANCODE_P] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_P\n");
#endif
            break;
        case 0x1A:
            kbd_currently_pressed[KBD_SCANCODE_SQUARE_BRACKET_OPEN] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SQUARE_BRACKET_OPEN\n");
#endif
            break;
        case 0x1B:
            kbd_currently_pressed[KBD_SCANCODE_SQUARE_BRACKET_CLOSE] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SQUARE_BRACKET_CLOSE\n");
#endif
            break;
        case 0x1C:
            kbd_currently_pressed[KBD_SCANCODE_ENTER] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_ENTER\n");
#endif
            break;
        case 0x1D:
            kbd_currently_pressed[KBD_SCANCODE_LCTRL] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_LCTRL\n");
#endif
            break;
        case 0x1E:
            kbd_currently_pressed[KBD_SCANCODE_A] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_A\n");
#endif
            break;
        case 0x1F:
            kbd_currently_pressed[KBD_SCANCODE_S] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_S\n");
#endif
            break;
        case 0x20:
            kbd_currently_pressed[KBD_SCANCODE_D] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_D\n");
#endif
            break;
        case 0x21:
            kbd_currently_pressed[KBD_SCANCODE_F] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F\n");
#endif
            break;
        case 0x22:
            kbd_currently_pressed[KBD_SCANCODE_G] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_G\n");
#endif
            break;
        case 0x23:
            kbd_currently_pressed[KBD_SCANCODE_H] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_H\n");
#endif
            break;
        case 0x24:
            kbd_currently_pressed[KBD_SCANCODE_J] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_J\n");
#endif
            break;
        case 0x25:
            kbd_currently_pressed[KBD_SCANCODE_K] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_K\n");
#endif
            break;
        case 0x26:
            kbd_currently_pressed[KBD_SCANCODE_L] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_L\n");
#endif
            break;
        case 0x27:
            kbd_currently_pressed[KBD_SCANCODE_SEMICOLON] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SEMICOLON\n");
#endif
            break;
        case 0x28:
            kbd_currently_pressed[KBD_SCANCODE_APOSTROPHE] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_APOSTROPHE\n");
#endif
            break;
        case 0x29:
            kbd_currently_pressed[KBD_SCANCODE_TILDE] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_TILDE\n");
#endif
            break;
        case 0x2A:
            kbd_currently_pressed[KBD_SCANCODE_LSHIFT] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_LSHIFT\n");
#endif
            break;
        case 0x2B:
            kbd_currently_pressed[KBD_SCANCODE_BACKSLASH] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_BACKSLASH\n");
#endif
            break;
        case 0x2C:
            kbd_currently_pressed[KBD_SCANCODE_Z] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_Z\n");
#endif
            break;
        case 0x2D:
            kbd_currently_pressed[KBD_SCANCODE_X] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_X\n");
#endif
            break;
        case 0x2E:
            kbd_currently_pressed[KBD_SCANCODE_C] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_C\n");
#endif
            break;
        case 0x2F:
            kbd_currently_pressed[KBD_SCANCODE_V] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_V\n");
#endif
            break;
        case 0x30:
            kbd_currently_pressed[KBD_SCANCODE_B] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_B\n");
#endif
            break;
        case 0x31:
            kbd_currently_pressed[KBD_SCANCODE_N] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_N\n");
#endif
            break;
        case 0x32:
            kbd_currently_pressed[KBD_SCANCODE_M] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_M\n");
#endif
            break;
        case 0x33:
            kbd_currently_pressed[KBD_SCANCODE_COMMA] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_COMMA\n");
#endif
            break;
        case 0x34:
            kbd_currently_pressed[KBD_SCANCODE_DOT] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_DOT\n");
#endif
            break;
        case 0x35:
            kbd_currently_pressed[KBD_SCANCODE_SLASH] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SLASH\n");
#endif
            break;
        case 0x36:
            kbd_currently_pressed[KBD_SCANCODE_RSHIFT] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_RSHIFT\n");
#endif
            break;
        case 0x37:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_WILDCARD] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_WILDCARD\n");
#endif
            break;
        case 0x38:
            kbd_currently_pressed[KBD_SCANCODE_LALT] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_LALT\n");
#endif
            break;
        case 0x39:
            kbd_currently_pressed[KBD_SCANCODE_SPACE] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SPACE\n");
#endif
            break;
        case 0x3A:
            kbd_currently_pressed[KBD_SCANCODE_CAPSLOCK] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_CAPSLOCK\n");
#endif
            break;
        case 0x3B:
            kbd_currently_pressed[KBD_SCANCODE_F1] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F1\n");
#endif
            break;
        case 0x3C:
            kbd_currently_pressed[KBD_SCANCODE_F2] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F2\n");
#endif
            break;
        case 0x3D:
            kbd_currently_pressed[KBD_SCANCODE_F3] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F3\n");
#endif
            break;
        case 0x3E:
            kbd_currently_pressed[KBD_SCANCODE_F4] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F4\n");
#endif
            break;
        case 0x3F:
            kbd_currently_pressed[KBD_SCANCODE_F5] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F5\n");
#endif
            break;
        case 0x40:
            kbd_currently_pressed[KBD_SCANCODE_F6] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F6\n");
#endif
            break;
        case 0x41:
            kbd_currently_pressed[KBD_SCANCODE_F7] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F7\n");
#endif
            break;
        case 0x42:
            kbd_currently_pressed[KBD_SCANCODE_F8] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F8\n");
#endif
            break;
        case 0x43:
            kbd_currently_pressed[KBD_SCANCODE_F9] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F9\n");
#endif
            break;
        case 0x44:
            kbd_currently_pressed[KBD_SCANCODE_F10] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F10\n");
#endif
            break;
        case 0x45:
            kbd_currently_pressed[KBD_SCANCODE_NUMLOCK] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_NUMLOCK\n");
#endif
            break;
        case 0x46:
            kbd_currently_pressed[KBD_SCANCODE_SCRLOCK] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_SCRLOCK\n");
#endif
            break;
        case 0x47:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_7] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_7\n");
#endif
            break;
        case 0x48:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_8] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_8\n");
#endif
            break;
        case 0x49:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_9] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_9\n");
#endif
            break;
        case 0x4A:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_MINUS] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_MINUS\n");
#endif
            break;
        case 0x4B:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_4] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_4\n");
#endif
            break;
        case 0x4C:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_5] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_5\n");
#endif
            break;
        case 0x4D:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_6] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_6\n");
#endif
            break;
        case 0x4E:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_PLUS] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_PLUS\n");
#endif
            break;
        case 0x4F:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_1] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_1\n");
#endif
            break;
        case 0x50:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_2] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_2\n");
#endif
            break;
        case 0x51:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_3] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_3\n");
#endif
            break;
        case 0x52:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_0] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_0\n");
#endif
            break;
        case 0x53:
            kbd_currently_pressed[KBD_SCANCODE_KEYPAD_DOT] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_KEYPAD_DOT\n");
#endif
            break;
        case 0x57:
            kbd_currently_pressed[KBD_SCANCODE_F11] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F11\n");
#endif
            break;
        case 0x58:
            kbd_currently_pressed[KBD_SCANCODE_F12] = val;
#ifdef KBDDBG
            printf("I parse it as KBD_SCANCODE_F12\n");
#endif
            break;
    }
}

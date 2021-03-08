#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>


#define KEY_0 SDL_SCANCODE_1
#define KEY_1 SDL_SCANCODE_2
#define KEY_2 SDL_SCANCODE_3
#define KEY_3 SDL_SCANCODE_4
#define KEY_4 SDL_SCANCODE_5
#define KEY_5 SDL_SCANCODE_6
#define KEY_6 SDL_SCANCODE_7
#define KEY_7 SDL_SCANCODE_8
#define KEY_8 SDL_SCANCODE_9
#define KEY_9 SDL_SCANCODE_0


#define KEY_KP_0 SDL_SCANCODE_KP_1
#define KEY_KP_1 SDL_SCANCODE_KP_2
#define KEY_KP_2 SDL_SCANCODE_KP_3
#define KEY_KP_3 SDL_SCANCODE_KP_4
#define KEY_KP_4 SDL_SCANCODE_KP_5
#define KEY_KP_5 SDL_SCANCODE_KP_6
#define KEY_KP_6 SDL_SCANCODE_KP_7
#define KEY_KP_7 SDL_SCANCODE_KP_8
#define KEY_KP_8 SDL_SCANCODE_KP_9
#define KEY_KP_9 SDL_SCANCODE_KP_0

#define KEY_A SDL_SCANCODE_A
#define KEY_B SDL_SCANCODE_B
#define KEY_C SDL_SCANCODE_C
#define KEY_D SDL_SCANCODE_D
#define KEY_E SDL_SCANCODE_E
#define KEY_F SDL_SCANCODE_F
#define KEY_G SDL_SCANCODE_G
#define KEY_H SDL_SCANCODE_H
#define KEY_I SDL_SCANCODE_I
#define KEY_J SDL_SCANCODE_J
#define KEY_K SDL_SCANCODE_K
#define KEY_L SDL_SCANCODE_L
#define KEY_M SDL_SCANCODE_M
#define KEY_N SDL_SCANCODE_N
#define KEY_O SDL_SCANCODE_O
#define KEY_P SDL_SCANCODE_P
#define KEY_Q SDL_SCANCODE_Q
#define KEY_R SDL_SCANCODE_R
#define KEY_S SDL_SCANCODE_S
#define KEY_T SDL_SCANCODE_T
#define KEY_U SDL_SCANCODE_U
#define KEY_V SDL_SCANCODE_V
#define KEY_W SDL_SCANCODE_W
#define KEY_X SDL_SCANCODE_X
#define KEY_Y SDL_SCANCODE_Y
#define KEY_Z SDL_SCANCODE_Z


#define KEY_F1 SDL_SCANCODE_F1
#define KEY_F2 SDL_SCANCODE_F2
#define KEY_F3 SDL_SCANCODE_F3
#define KEY_F4 SDL_SCANCODE_F4
#define KEY_F5 SDL_SCANCODE_F5
#define KEY_F6 SDL_SCANCODE_F6
#define KEY_F7 SDL_SCANCODE_F7
#define KEY_F8 SDL_SCANCODE_F8
#define KEY_F9 SDL_SCANCODE_F9
#define KEY_F10 SDL_SCANCODE_F10
#define KEY_F11 SDL_SCANCODE_F11
#define KEY_F12 SDL_SCANCODE_F12
#define KEY_F13 SDL_SCANCODE_F13
#define KEY_F14 SDL_SCANCODE_F14
#define KEY_F15 SDL_SCANCODE_F15
#define KEY_F16 SDL_SCANCODE_F16
#define KEY_F17 SDL_SCANCODE_F17
#define KEY_F18 SDL_SCANCODE_F18
#define KEY_F19 SDL_SCANCODE_F19
#define KEY_F20 SDL_SCANCODE_F20
#define KEY_F21 SDL_SCANCODE_F21
#define KEY_F22 SDL_SCANCODE_F22
#define KEY_F23 SDL_SCANCODE_F23
#define KEY_F24 SDL_SCANCODE_F24


#define KEY_HOME SDL_SCANCODE_HOME
#define KEY_INS SDL_SCANCODE_INSERT
#define KEY_DEL SDL_SCANCODE_DELETE
#define KEY_PGUP SDL_SCANCODE_PAGEUP
#define KEY_PGDN SDL_SCANCODE_PAGEDOWN


#define KEY_LEFT  SDL_SCANCODE_LEFT
#define KEY_UP    SDL_SCANCODE_UP
#define KEY_RIGHT SDL_SCANCODE_RIGHT
#define KEY_DOWN  SDL_SCANCODE_DOWN

#define KEY_SPACE SDL_SCANCODE_SPACE
#define KEY_LCTRL SDL_SCANCODE_LCTRL
#define KEY_RCTRL SDL_SCANCODE_RCTRL

#define KEY_LEFT_ALT SDL_SCANCODE_LALT
#define KEY_RIGHT_ALT SDL_SCANCODE_RALT




typedef struct game_control_t {
        int k_up;
        int k_down;
        int k_left;
        int k_right;
        int k_jump;
        int k_action;
        int joystick;
        int32_t flags;
}game_control_t;


#define KEY_UP_FLAG     0x0001
#define KEY_DOWN_FLAG   0x0002
#define KEY_LEFT_FLAG   0x0004
#define KEY_RIGHT_FLAG  0x0008
#define KEY_JUMP_FLAG   0x00010
#define KEY_ACTION_FLAG 0x00020


void keyboard_init(void);
void keyboard_set(game_control_t* cnt, int up, int down, int left, int right, int jump, int action, int use_joy);
void keyboard_handle_keys(SDL_Event *event, game_control_t *cnt);
int keyboard_check(game_control_t *cnt, int key);

game_control_t *keyboard_get_player_control();


void keyboard_save_to_file(game_control_t *cnt,  const char *output);
void keyboard_load_from_file(game_control_t *cnt,  const char *output);
void keyboard_load_from_mem(void *mem, game_control_t *cnt);

int key_is_up(game_control_t *cnt);
int key_is_down(game_control_t *cnt);
int key_is_left(game_control_t *cnt);
int key_is_right(game_control_t *cnt);
int key_is_jump(game_control_t *cnt);
int key_is_action(game_control_t *cnt);

#endif // KEYBOARD_H

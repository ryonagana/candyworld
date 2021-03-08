#include <stdio.h>
#include <stdlib.h>

#include "keyboard.h"
#include "window.h"
#include "log.h"
#include "shared.h"




static game_control_t player_control;

void keyboard_init()
{
    keyboard_set(&player_control,
                 KEY_W,
                 KEY_S,
                 KEY_A,
                 KEY_D,
                 KEY_SPACE,
                 KEY_Z,
                 0
                 );



    FILE *fp = NULL;

    if((fp = fopen("control.dat", "rb")) == NULL){
        DLOG("control.dat does not exists creating a  fresh one!");

        keyboard_save_to_file(&player_control, "control.dat");
        keyboard_load_from_file(&player_control, "control.dat");
        return;
    }

     void *blk = malloc(sizeof(game_control_t));
     fread(blk, sizeof (game_control_t), 1, fp);
     keyboard_load_from_mem(blk, &player_control);
     fclose(fp);

    return;
}




int keyboard_check(game_control_t *cnt, int key)
{
    if(key == cnt->k_up) return 1;
    if(key == cnt->k_down) return 1;
    if(key == cnt->k_left) return 1;
    if(key == cnt->k_right) return 1;
    if(key == cnt->k_jump) return 1;
    if(key == cnt->k_action) return 1;

    return 0;

}


void keyboard_handle_keys(SDL_Event *event, game_control_t *cnt)
{
            const Uint8 *key_snapshot = SDL_GetKeyboardState(NULL);
            int key =  key_snapshot[event->key.keysym.scancode];

            if(key == cnt->k_up)     cnt->flags |= KEY_UP_FLAG;
            if(key == cnt->k_down)   cnt->flags |= KEY_DOWN_FLAG;
            if(key == cnt->k_left)   cnt->flags |= KEY_LEFT_FLAG;
            if(key == cnt->k_right)  cnt->flags |= KEY_RIGHT_FLAG;
            if(key == cnt->k_jump)   cnt->flags |= KEY_JUMP_FLAG;
            if(key == cnt->k_action) cnt->flags |= KEY_ACTION_FLAG;


}

void keyboard_set(game_control_t *cnt, int up, int down, int left, int right, int jump, int action, int use_joy)
{
    cnt->k_up = up;
    cnt->k_down = down;
    cnt->k_left = left;
    cnt->k_right = right;
    cnt->k_jump = jump;
    cnt->k_action = action;
    cnt->joystick = use_joy;
    cnt->flags = 0;

}

game_control_t *keyboard_get_player_control()
{
    return &player_control;
}

int key_is_up(game_control_t *cnt)
{

    return cnt->k_up & KEY_UP_FLAG? 1 : 0;
}

int key_is_down(game_control_t *cnt)
{

    return cnt->k_down & KEY_DOWN_FLAG    ? 1 : 0;
}

int key_is_left(game_control_t *cnt)
{
    return cnt->k_left & KEY_LEFT_FLAG     ? 1 : 0;
}

int key_is_right(game_control_t *cnt)
{
    return cnt->k_right & KEY_RIGHT_FLAG   ? 1 : 0;
}

int key_is_jump(game_control_t *cnt)
{
    return cnt->k_jump & KEY_JUMP_FLAG    ? 1 : 0;
}

int key_is_action(game_control_t *cnt)
{
    return cnt->k_action & KEY_ACTION_FLAG ? 1 : 0;
}

void keyboard_save_to_file(game_control_t *cnt, const char *output)
{
    FILE *fp = NULL;

    if((fp = fopen(output,"wb+")) == NULL ){
        DCRITICAL("cannot save %s", output);
        return;
    }

    fwrite(cnt, sizeof(game_control_t), 1, fp);
    fclose(fp);
}

void keyboard_load_from_file(game_control_t *cnt, const char *output)
{
    FILE *fp = NULL;

    if((fp = fopen(output,"rb+")) == NULL ){
        DCRITICAL("cannot load %s", output);
        return;
    }



    fread(cnt, sizeof(game_control_t), 1, fp);
    fclose(fp);
}

void keyboard_load_from_mem(void *mem, game_control_t *cnt)
{
    game_control_t *tmp = (game_control_t *)mem;
    memcpy(cnt, tmp, sizeof (game_control_t));

    if(mem){
        free(mem);
    }
}

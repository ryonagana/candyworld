#include "shared.h"

void rect_init(rect_t *r){

    r->x = 0;
    r->y = 0;
    r->width = 0;
    r->height = 0;
    r->top = 0;
    r->bottom = 0;
    r->left = 0;
    r->right = 0;
    return;

}
void rect_set(rect_t *r, int x, int y, int w, int h){
    r->x = x;
    r->y = y;
    r->width = w;
    r->height = h;
    r->top = y;
    r->bottom = y + h;
    r->left = x;
    r->right = x + w;
    return;
}

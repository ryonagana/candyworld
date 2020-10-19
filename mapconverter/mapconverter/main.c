#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ini.h"
#include <string.h>

#ifdef __GNUC__
#include <errno.h>
#endif


#include "map.h"



int main()
{

    map_t* root = NULL;

    root = map_init();
    read_config(root, "test");

    return 0;
}

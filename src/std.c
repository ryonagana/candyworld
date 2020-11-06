#include "std.h"
#include <string.h>

const char *std_basename(const char *path, char separator)
{
    if((strrchr(path, separator)) == NULL){
        return  strdup(path);
    }

    return strdup(strrchr(path + 1, separator) + 1);
}

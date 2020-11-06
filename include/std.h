#ifndef STD_H
#define STD_H


const char *std_basename(const char *path, char separator);


#define BASENAME(p) std_basename(p, '/')


#endif // STD_H


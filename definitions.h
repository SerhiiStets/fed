#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef _WIN32
#define HOME_PATH "USERPROFILE"
#endif
#ifdef linux
#define HOME_PATH "HOME"
#endif

#define CLI_NAME "fed"
#define VERSION "0.0.1"
#define ARRAY_SIZE(x) (sizeof(x) / sizeof(x[0]))
#define MAX 255
#endif

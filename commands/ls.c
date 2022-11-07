#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"
#include "../definitions.h"

int cmd_ls(int argc, const char **argv)
{
    int limit;
    FILE *filePointer;
    int i = 1;
    int bufferLength = 255;
    char buffer[bufferLength]; /* not ISO 90 compatible */

    if (argc)
        limit = atoi(argv[0]);

    char *homepath = get_home_path();
    char *conf_path = malloc(strlen(homepath) + 2);
    strcpy(conf_path, homepath);
    strncat(conf_path, "\\", 2);
    strncat(conf_path, "fed.cfg", 8);
    filePointer = fopen(conf_path, "r");

    fprintf(stdout, "%s: Favourite folders:\n\n", CLI_NAME);

    while (fgets(buffer, bufferLength, filePointer))
    {
        fprintf(stdout, "%d. %s", i, buffer);
        if (limit == i)
            break;
        i++;
    }

    fclose(filePointer);
    free(conf_path);

    return 1;
}

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"
#include "../definitions.h"

int cmd_ls(int argc, const char **argv)
{
    int i = 1;
    int limit = 0;
    int bufferLength = 255;
    char buffer[bufferLength]; /* not ISO 90 compatible */
    FILE *filePointer;

    if (argc)
        limit = atoi(argv[0]);

    char *conf_path = get_cfg_path();
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

    if (limit == 0 && i == 1)
    {
        fprintf(stdout, "No favourite folders.\n\nUse %s <add> command to add folders.\n", CLI_NAME);
    }
    else
    {
        fprintf(stdout, "\nUse the number with %s <cd> command to cd into selected directory\n", CLI_NAME);
    }

    return 1;
}

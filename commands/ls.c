#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils.h"
#include "../definitions.h"

/**
 * @brief Shows a numbered list of favourite folders
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int cmd_ls(int argc, const char **argv)
{
    FILE *pFile;
    int i = 1;
    int limit = 0;
    char buffer[MAX]; /* not ISO 90 compatible */

    /* If argument passed */
    /* limit of how much of ls would be shown is int of passed argv */
    if (argc)
        limit = atoi(argv[0]);

    char *conf_path = get_cfg_path();
    pFile = fopen(conf_path, "r");

    fprintf(stdout, "%s: Favourite folders:\n\n", CLI_NAME);

    while (fgets(buffer, MAX, pFile))
    {
        fprintf(stdout, "%d. %s", i, buffer);
        /* if limit reached -> break */
        /* since limit by default = 0 and i by default = 1 */
        /* then if no argv passed the list would be shown full as 0 != 1 */
        if (limit == i)
            break;
        i++;
    }
    fclose(pFile);
    free(conf_path);

    /* if i is not moved at all and limit is not changed then no folders in favourite */
    if (limit == 0 && i == 1)
        fprintf(stdout, "No favourite folders.\n\nUse %s <add> command to add folders.\n", CLI_NAME);
    else
        fprintf(stdout, "\nUse the number with %s <cd> command to cd into selected directory\n", CLI_NAME);

    return 1;
}

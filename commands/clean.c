#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "../definitions.h"
#include "../utils.h"

int cmd_clean(int argc, const char **argv)
{
    if (!argc)
    {
        fprintf(stderr, "%s %s", CLI_NAME, ": Need directory as an argument!\n\n");
        fprintf(stderr, "%s", "Use '.' or full dir path or <all> to clear all favourite fodlers.\n");
        return 1;
    }

    while (argc)
    {
        if (!strcmp(argv[0], "all"))
        {
            FILE *pFile;
            char *conf_path = get_cfg_path();
            pFile = fopen(conf_path, "w");
            fclose(pFile);
            free(conf_path);
            fprintf(stdout, "%s: favourite folders are now empty.\n", CLI_NAME);
            return 1;
        }

        if (!strcmp(argv[0], "."))
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                argv[0] = cwd;
        }

        // TODO number list removal
        remove_from_config(argv[0]);

        argc--;
        argv++;
    }
    return 0;
}
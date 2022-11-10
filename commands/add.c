#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include "../definitions.h"
#include "../utils.h"

int cmd_add(int argc, const char **argv)
{
    int append_status;
    int in_favourites;

    if (!argc)
    {
        fprintf(stderr, "%s %s", CLI_NAME, ": Need directory as an argument!\n\n");
        fprintf(stderr, "%s", "Use '.' or full dir path whith <add>.\n");
        return 1;
    }

    while (argc)
    {
        DIR *dir = opendir(argv[0]);
        if (dir)
        {
            if (!strcmp(argv[0], "."))
            {
                char cwd[PATH_MAX];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                    argv[0] = cwd;
            }

            in_favourites = check_in_favourites(argv[0]);

            if (in_favourites)
            {
                fprintf(stdout, "%s: %s is already in favourites.\n", CLI_NAME, argv[0]);
                argv++;
                argc--;
                continue;
            }

            append_status = append_to_config(argv[0]);

            if (append_status)
                fprintf(stdout, "%s directory is added to favourites.\n\n", argv[0]);
            else
                fprintf(stderr, "%s: error appending %s directory to favourites\n\n", CLI_NAME, argv[0]);
        }
        else if (ENOENT == errno)
            fprintf(stderr, "%s: '%s' is not a real directory.\n\n", CLI_NAME, argv[0]);

        closedir(dir);
        argv++;
        argc--;
    }

    return 0;
}

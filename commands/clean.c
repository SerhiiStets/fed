#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "../definitions.h"
#include "../utils.h"

/**
 * @brief Removes given folders from favourites directory
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
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
        FILE *pFile;
        int i = 1;
        int is_in_favourites = 0;
        char buffer[MAX];
        char *conf_path = get_cfg_path();
        char delim[3] = "[]";
        char *token;
        Named_dir alias_dir;

        /* If "all" as an argument, delete all folders in favourites */
        if (!strcmp(argv[0], "all"))
        {
            pFile = fopen(conf_path, "w");
            fclose(pFile);
            fprintf(stdout, "%s: favourite folders are now empty.\n", CLI_NAME);
            return 1;
        }

        /* "." = current directory */
        /* if "." is passed then change argv[0] to current folder for further deletion */
        if (!strcmp(argv[0], "."))
        {
            char cwd[PATH_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
                argv[0] = cwd;
        }

        /* Check if the user passed a number of full dir path for removal */
        pFile = fopen(conf_path, "r");
        while (fgets(buffer, MAX, pFile))
        {

            buffer[strlen(buffer) - 1] = '\0';
            if (i == atoi(argv[0]) || !strcmp(argv[0], buffer))
            {
                is_in_favourites = 1;
                break;
            }

            char temp[MAX];
            strncpy(temp, buffer, strlen(buffer) + 1);
            token = strtok(temp, delim);
            alias_dir.alias = token;
            token = strtok(NULL, delim);
            alias_dir.directory = token;

            /* If there's an alias folder then directory will be NULL */
            /* as strtok would not find [] delimeters and only split once */
            /* return second NULL */
            if (alias_dir.directory)
            {
                if (!strcmp(argv[0], alias_dir.alias))
                {
                    is_in_favourites = 1;
                    break;
                }
            }
            i++;
        }
        free(conf_path);
        fclose(pFile);

        if (is_in_favourites)
        {
            /* The directory can be removed from the list */
            remove_from_config(buffer);
            fprintf(stdout, "%s: The directory %s is deleted from favourites.\n", CLI_NAME, buffer);
        }
        else
        {
            /* Passed number/directory/command is not recognized */
            fprintf(stdout, "%s: The directory %s is not in favourites.\n", CLI_NAME, buffer);
        }

        argc--;
        argv++;
    }
    return 0;
}

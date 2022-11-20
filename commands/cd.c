#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "../utils.h"
#include "../definitions.h"

/**
 * @brief Adds given folders to favourites
 * Adding can be done just by folder name or
 * given with alias with -a flag for better
 * interaction with other functions
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int cmd_cd(int argc, const char **argv)
{
    if (!argc)
    {
        fprintf(stdout, "%s: add number of a folder to cd into.\n", CLI_NAME);
        return 1;
    }

    FILE *pFile;
    Named_dir alias_dir;
    int i = 1;
    int status = 0;
    int is_in_favourites = 0;
    char buffer[MAX]; /* not ISO 90 compatible */
    char *conf_path = get_cfg_path();
    const char delim[3] = "[]";
    char *token;
    char temp[MAX];

    pFile = fopen(conf_path, "r");
    while (fgets(buffer, MAX, pFile))
    {
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(temp, buffer);
        if (i == atoi(argv[0]))
        {
            token = strtok(temp, delim);
            alias_dir.alias = token;
            token = strtok(NULL, delim);
            alias_dir.directory = token;
            if (alias_dir.directory)
                strcpy(buffer, alias_dir.directory + 1);
            is_in_favourites = 1;
            break;
        }

        token = strtok(temp, delim);
        alias_dir.alias = token;
        token = strtok(NULL, delim);
        alias_dir.directory = token;

        if (!strcmp(alias_dir.alias, argv[0]))
        {
            is_in_favourites = 1;
            strcpy(buffer, alias_dir.directory + 1);
            break;
        }
        i++;
    }

    fclose(pFile);
    free(conf_path);

    if (is_in_favourites)
    {
        fprintf(stdout, "%s: %s is your directory.\n\n", CLI_NAME, buffer);

#ifdef WIN32
        /* For Windows to move between drives we need to add <drive>: command before cd */
        char drive = buffer[0];
        char and_cmd[9] = ": && cd ";
        char *cd_command = malloc(strlen(buffer) + 1 + sizeof(drive) + strlen(and_cmd) + 1);
        cd_command[0] = drive;
        cd_command[1] = '\0';
        strncat(cd_command, and_cmd, strlen(and_cmd) + 1);
        strncat(cd_command, buffer, strlen(buffer) + 1);
#endif
#ifdef linux
        char *cd_command = malloc(strlen(buffer) + 1 + 4);
        strncpy(cd_command, "cd ", 4);
#endif

        status = add_to_clipboard(cd_command);

        if (status)
            fprintf(stdout, "The command <%s> is copied to your clipboard.\
                \nUse Ctr+V to get the command.\n\n",
                    cd_command);
        else
            fprintf(stdout, "%s: There was an error with adding %s command to clipboard.\n\n", CLI_NAME, cd_command);

        free(cd_command);
        return 1;
    }

    fprintf(stderr, "%s: %s is not in favourites.\
        \nUse %s <ls> to see what directoris are in favourites.\n\n",
            CLI_NAME, argv[0], CLI_NAME);

    return 1;
}

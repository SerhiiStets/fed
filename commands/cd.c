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
    FILE *pFile;
    Named_dir alias_dir;
    int i = 1;
    int status = 0;
    int is_in_favourites = 0;
    char buffer[MAX]; /* not ISO 90 compatible */
    char temp[MAX];
    char delim[3] = "[]";
    char *token;

    if (!argc)
    {
        fprintf(stdout, "%s: add number of a folder to cd into.\n", CLI_NAME);
        return 1;
    }

    char *conf_path = get_cfg_path();

    pFile = fopen(conf_path, "r");
    while (fgets(buffer, MAX, pFile))
    {
        buffer[strlen(buffer) - 1] = '\0';
        /* Storing file line to temp to not mess with buffer that's gonna be used later */
        strcpy(temp, buffer);

        /* if argument is a number then check which dir it is in the list and break */
        if (i == atoi(argv[0]))
        {
            /* Trying to fecth a directory from temp if the line has alias */
            /* if alias_dir.directory is NULL then there was no alias */
            /* and there's no need to change the value of the buffer */
            token = strtok(temp, delim);
            alias_dir.alias = token;
            token = strtok(NULL, delim);
            alias_dir.directory = token;
            if (alias_dir.directory)
                strcpy(buffer, alias_dir.directory + 1);
            is_in_favourites = 1;
            break;
        }

        /* if the code goes here then the user did not pass a number */
        /* so code tries to see if the alias was passed and if it exists */
        token = strtok(temp, delim);
        alias_dir.alias = token;
        token = strtok(NULL, delim);
        alias_dir.directory = token;

        if (alias_dir.directory)
        {
            /* if alias == argument passed, copy parsed directory to buffer for future wokr */
            if (!strcmp(alias_dir.alias, argv[0]))
            {
                is_in_favourites = 1;
                strcpy(buffer, alias_dir.directory + 1);
                break;
            }
        }
        i++;
    }

    fclose(pFile);
    free(conf_path);

    if (is_in_favourites)
    {
        fprintf(stdout, "%s: %s is your directory.\n\n", CLI_NAME, buffer);

        /* Generating cd commands */
#ifdef WIN32
        /* Windows only */
        /* For Windows to move between drives we need to add <drive>: command before cd */
        char drive = buffer[0];
        char and_cmd[9] = ": && cd ";
        char *cd_command = malloc(strlen(buffer) + 1 + sizeof(drive) + strlen(and_cmd) + 1);
        cd_command[0] = drive;
        cd_command[1] = '\0';

        sprintf(cd_command, "%s: && cd %s", cd_command, buffer);

        /* Adding genereted command to the clipboard */
        status = add_to_clipboard(cd_command);
        if (status)
            fprintf(stdout, "The command <%s> is copied to your clipboard.\
                \nUse Ctr+V to get the command.\n\n",
                    cd_command);
        else
            fprintf(stdout, "%s: There was an error with adding %s command to clipboard.\n\n", CLI_NAME, cd_command);
#endif
#ifdef linux
        /* TODO: Linux clipboard if possible */
        char *cd_command = malloc(strlen(buffer) + 1 + 4);
        sprintf(cd_command, "cd %s", buffer);
        fprintf(stdout, "%s\n\n", cd_command);
#endif

        free(cd_command);
        return 1;
    }

    /* Inform user if argument passed can not be traced to favourte folders */
    fprintf(stderr, "%s: %s is not in favourites.\
        \nUse %s <ls> to see what directoris are in favourites.\n\n",
            CLI_NAME, argv[0], CLI_NAME);

    return 1;
}

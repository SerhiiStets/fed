#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>

#ifdef WIN32
#include <windows.h>
#endif

#include "../utils.h"
#include "../definitions.h"

int cmd_cd(int argc, const char **argv)
{
    if (!argc)
    {
        fprintf(stdout, "%s: add number of a folder to cd into.\n", CLI_NAME);
        return 1;
    }

    FILE *filePointer;
    int i = 1;
    int status = 0;
    int buffer_length = 255;
    char buffer[buffer_length]; /* not ISO 90 compatible */
    int is_in_favourites = 0;

    char *conf_path = get_cfg_path();
    filePointer = fopen(conf_path, "r");
    while (fgets(buffer, buffer_length, filePointer))
    {
        buffer[strlen(buffer) - 1] = '\0';
        if (i == atoi(argv[0]))
        {
            is_in_favourites = 1;
            break;
        }
        i++;
    }

    fclose(filePointer);
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
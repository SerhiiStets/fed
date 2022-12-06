#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include "../utils.h"
#include "../definitions.h"

/**
 * @brief Opens the folder in explorer
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int cmd_open(int argc, const char **argv)
{
    FILE *pFile;
    Named_dir alias_dir;
    int i = 1;
    int is_in_favourites = 0;
    char buffer[MAX]; /* not ISO 90 compatible */
    char temp[MAX];
    char delim[3] = "[]";
    char *token;

    if (!argc)
    {
        fprintf(stdout, "%s: no paramters passed. Please use \n\n%s open <alias>/<number> \n\n", CLI_NAME, CLI_NAME);
        return 0;
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
        char open_explr_cmd[MAX];
        strncpy(open_explr_cmd, "start \"\" \"", 11);
        strncat(open_explr_cmd, buffer, strlen(buffer) + 1);
        strncat(open_explr_cmd, "\"", 2);
        fprintf(stdout, "%s: openning %s directory.\n\n", CLI_NAME, buffer);
        system(open_explr_cmd);
        return 1;
    }
    
    /* Inform user if argument passed can not be traced to favourte folders */
    fprintf(stderr, "%s: %s is not in favourites.\
        \nUse %s <ls> to see what directoris are in favourites.\n\n",
            CLI_NAME, argv[0], CLI_NAME);

    return 1;
}

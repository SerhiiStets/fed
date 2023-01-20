#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../utils.h"
#include "../definitions.h"


/**
 * @brief Renames directory alias
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int cmd_rename(int argc, const char **argv)
{
    if (!argc || argc != 2)
    {
        fprintf(stdout, "%s: <rename> takes two arguments:\n %s rename [old name] [new name].\n", CLI_NAME, CLI_NAME);
        return 1;
    }
    
    FILE *pFile;
    const char *old_name = argv[0];
    const char *new_name = argv[1];
    char buffer[MAX];
    char *conf_path = get_cfg_path();
    char delim[3] = "[]";
    char *token;
    int i = 1;
    int is_in_favourites = 0;
    Named_dir alias_dir;

    pFile = fopen(conf_path, "r");
    
    while (fgets(buffer, MAX, pFile))
    {
        buffer[strlen(buffer) - 1] = '\0';
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
        /* Add directory back with a new alias name */ 
        int alias_len = strlen(new_name) + 1;
        /* Remove all white space from the beginning of string  */ 
        while(isspace((unsigned char) *alias_dir.directory) ) { ++alias_dir.directory; }
        /* Create an entry with a new alias */
        int directory_len = strlen(alias_dir.directory) + 1;
        char *alias_string = malloc(2 + alias_len + 3 + directory_len);
        sprintf(alias_string, "[%s] %s", new_name, alias_dir.directory);
        /* Append new entry to the config */
        append_to_config(alias_string);
        free(alias_string);
        fprintf(stdout, "%s: The directory %s alias is changed\n%s -> %s\n", CLI_NAME, alias_dir.directory, alias_dir.alias, new_name);
    }
    else
    {
        /* Passed number/directory/command is not recognized */
        fprintf(stdout, "%s: The directory %s is not in favourites.\n", CLI_NAME, old_name);
    }


    return 0;
}

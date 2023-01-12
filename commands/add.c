#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>

#include "../definitions.h"
#include "../utils.h"

/**
 * @brief Adds directory to favourites with alias
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int add_alias_dir(int argc, const char **argv)
{
    DIR *dir;
    int append_status;
    int in_favourites;
    int alias_exists = 0;
    Named_dir alias_dir;

    /* Check if alias was in passed arguments */
    argv++;
    argc--;

    if (!argc)
    {
        fprintf(stdout, "%s: no alias and directory, please use \n\n%s add -a <alias> <directory>\n\n", CLI_NAME, CLI_NAME);
        return 0;
    }

    alias_dir.alias = argv[0];

    /* Check if directory was in passed arguments */
    argv++;
    argc--;

    if (!argc)
    {
        fprintf(stdout, "%s: directory not specified, please use \n\n%s add -a <alias> <directory>\n\n", CLI_NAME, CLI_NAME);
        return 0;
    }

    /* If dir and alias is passed, check if alias already exists */
    /* TODO: if dir in favourites but doesn't have an alias */
    /* TODO: alias renaming */
    alias_exists = check_alias_exists(alias_dir.alias);

    if (alias_exists)
    {
        fprintf(stdout, "%s: alias [%s] already exists, please chose a new one or delete the old one.\n\n", CLI_NAME, alias_dir.alias);
        return 0;
    }

    dir = opendir(argv[0]);
    if (dir)
    {
        /* . represents current path */
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
            return 0;
        }

        alias_dir.directory = argv[0];

        int alias_len = strlen(alias_dir.alias) + 1;
        int directory_len = strlen(alias_dir.directory) + 1;
        char *alias_string = malloc(2 + alias_len + 3 + directory_len);

        sprintf(alias_string, "[%s] %s", alias_dir.alias, alias_dir.directory);

        append_status = append_to_config(alias_string);
        free(alias_string);

        if (append_status)
            fprintf(stdout, "%s directory is added to favourites.\n\n", argv[0]);
        else
            fprintf(stderr, "%s: error appending %s directory to favourites\n\n", CLI_NAME, argv[0]);
    }
    else if (ENOENT == errno)
        fprintf(stderr, "%s: '%s' is not a real directory.\n\n", CLI_NAME, argv[0]);

    closedir(dir);
    return 0;
}

/**
 * @brief Add directory/ies to favourites without aliases
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int add_non_alias_dir(int argc, const char **argv)
{
    int append_status;
    int in_favourites;

    /* Adding every passed argument to favourite folders if directory exists */
    while (argc)
    {
        DIR *dir = opendir(argv[0]);
        if (dir)
        {
            /* . represents current path */
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
    return 1;
}

/**
 * @brief <add> command for adding new folders to favourites
 *
 * @param argc Number of arguments passed
 * @param argv Arguments
 * @return int Status of function success
 */
int cmd_add(int argc, const char **argv)
{
    int status = 0;

    if (!argc)
    {
        fprintf(stderr, "%s %s", CLI_NAME, ": Need directory as an argument!\n\n");
        fprintf(stderr, "%s", "Use '.' or full dir path whith <add>.\n");
        return 1;
    }

    if (!strcmp("--alias", argv[0]) || !strcmp("-a", argv[0]))
        argv[0] = "alias";

    if (!strcmp("alias", argv[0]))
        status = add_alias_dir(argc, argv);
    else
        status = add_non_alias_dir(argc, argv);

    return status;
}

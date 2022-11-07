#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "definitions.h"

#ifdef WIN32
#include <io.h>
#include <windows.h>
#define HOME_PATH "USERPROFILE"
#endif
#ifdef linux
#define HOME_PATH "HOME"
#endif

char *get_home_path()
{
    char *homedir;
    homedir = getenv(HOME_PATH);
    return homedir;
}

int append_to_config(const char *path)
{
    FILE *pFile;
    char *homepath = get_home_path();
    char *conf_path = malloc(strlen(homepath) + 2);
    strcpy(conf_path, homepath);
    strncat(conf_path, "\\", 2);
    strncat(conf_path, "fed.cfg", 8);

    pFile = fopen(conf_path, "a");
    if (pFile == NULL)
    {

        fprintf(stderr, "%s: Error opening config file.\n\n", CLI_NAME);
        fclose(pFile);
        return 0;
    }
    fprintf(pFile, "%s\n", path);
    free(conf_path);
    fclose(pFile);
    return 1;
}

int create_config()
{
    char *homepath = get_home_path();
    char *conf_path = malloc(strlen(homepath) + 2);
    strcpy(conf_path, homepath);
    strncat(conf_path, "\\", 2);
    strncat(conf_path, "fed.cfg", 8);

    if (_access(conf_path, 0))
    {
        FILE *fp;
        fp = fopen(conf_path, "w");
        if (!fp)
        {
            fprintf(stderr, "%s: Error opening config file.\n\n", CLI_NAME);
            return 0;
        }
        fclose(fp);
    }
    free(conf_path);
    return 1;
}
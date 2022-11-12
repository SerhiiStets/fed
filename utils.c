#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "definitions.h"

#ifdef WIN32
#include <io.h>
#include <windows.h>
#endif

char *get_cfg_path()
{
    char *homedir;
    homedir = getenv(HOME_PATH);
    char *conf_path = malloc(strlen(homedir) + 12);
    strcpy(conf_path, homedir);
    strncat(conf_path, "/", 2);
    strncat(conf_path, "fed.cfg", 8);
    return conf_path;
}

int add_to_clipboard(char *command)
{
    const size_t len = strlen(command) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len);
    if (hMem)
    {
        memcpy(GlobalLock(hMem), command, len);
        GlobalUnlock(hMem);
        OpenClipboard(0);
        EmptyClipboard();
        SetClipboardData(CF_TEXT, hMem);
        CloseClipboard();
        return 1;
    }
    return 0;
}

int append_to_config(const char *path)
{
    FILE *pFile;
    char *conf_path = get_cfg_path();
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

int remove_from_config(const char *path)
{
    FILE *pFile, *temp;
    int in_favourites = 0;
    int buffer_length = 255;
    char buffer[buffer_length]; /* not ISO 90 compatible */

    char *conf_path = get_cfg_path();
    char *temp_path = malloc(strlen(conf_path) + 5);
    strncpy(temp_path, conf_path, strlen(conf_path) + 2);
    strncat(temp_path, ".tmp", 5);

    pFile = fopen(conf_path, "r");
    temp = fopen(temp_path, "w");
    while (fgets(buffer, buffer_length, pFile))
    {
        char temp_buffer[strlen(buffer) + 2];
        strncpy(temp_buffer, buffer, strlen(buffer) + 1);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(path, buffer))
            fprintf(temp, "%s", temp_buffer);
        else
            in_favourites = 1;
    }
    fclose(temp);
    fclose(pFile);

    pFile = fopen(conf_path, "w");
    temp = fopen(temp_path, "r");
    while (fgets(buffer, buffer_length, temp))
    {
        fprintf(pFile, "%s", buffer);
    }
    fclose(temp);
    fclose(pFile);

    remove(temp_path);
    free(conf_path);
    free(temp_path);

    if (!in_favourites)
    {
        fprintf(stdout, "%s: The directory %s is not in favourites.\n", CLI_NAME, path);
        return 0;
    }

    fprintf(stdout, "%s: The directory %s is deleted from favourites.\n", CLI_NAME, path);
    return 1;
}

int create_config()
{
    char *conf_path = get_cfg_path();

    if (access(conf_path, 0))
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

int check_in_favourites(const char *path)
{
    FILE *filePointer;
    int bufferLength = 255;
    char buffer[bufferLength]; /* not ISO 90 compatible */

    char *conf_path = get_cfg_path();
    filePointer = fopen(conf_path, "r");

    while (fgets(buffer, bufferLength, filePointer))
    {
        buffer[strlen(buffer) - 1] = '\0';
        if (!strcmp(buffer, path))
            return 1;
    }

    fclose(filePointer);
    free(conf_path);
    return 0;
}
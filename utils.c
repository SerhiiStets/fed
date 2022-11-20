#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "definitions.h"

#ifdef WIN32
#include <io.h>
#include <windows.h>
#endif

/**
 * @brief Creating a full path to fed.cfg
 *
 * Using getenv() with defined HOME_PATH depending on OS,
 * we have a Home dir and then append '/fed.cfg' for full path.
 * TODO: check getenv return on errors
 * TODO: possibly go without *conf_path but only with *homedir
 * @return char* Full path to fed.cfg file
 */
char *get_cfg_path()
{
    char *homedir;
    homedir = getenv(HOME_PATH);
    char *conf_path = malloc(strlen(homedir) + 12);
    strcpy(conf_path, homedir);
    strncat(conf_path, "/fed.cfg", 9);
    return conf_path;
}

/**
 * @brief Appending generated fed <cd> command to the clipboard
 *
 * TODO: better error check
 * TODO: Linux solution
 * @param command fed Generated command for cd into favourite folder
 * @return int Status of successfull completion
 */
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

/**
 * @brief Append given folder path to fed.cfg file in HOME dir
 *
 * @param path Folder path
 * @return int Status of function success
 */
int append_to_config(const char *path, int is_alias)
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

/**
 * @brief Remove given folder path from fed.cfg file in HOME dir
 *
 * TODO: better error check
 * @param path Folder path
 * @return int Status of function success
 */
int remove_from_config(const char *path)
{
    FILE *pFile, *temp;
    char buffer[MAX]; /* not ISO 90 compatible */

    char *conf_path = get_cfg_path();
    char *temp_path = malloc(strlen(conf_path) + 5);
    strncpy(temp_path, conf_path, strlen(conf_path) + 2);
    strncat(temp_path, ".tmp", 5);

    pFile = fopen(conf_path, "r");
    temp = fopen(temp_path, "w");
    while (fgets(buffer, MAX, pFile))
    {
        char temp_buffer[strlen(buffer) + 2];
        strncpy(temp_buffer, buffer, strlen(buffer) + 1);
        buffer[strlen(buffer) - 1] = '\0';
        if (strcmp(path, buffer))
            fprintf(temp, "%s", temp_buffer);
    }
    fclose(temp);
    fclose(pFile);

    pFile = fopen(conf_path, "w");
    temp = fopen(temp_path, "r");
    while (fgets(buffer, MAX, temp))
    {
        fprintf(pFile, "%s", buffer);
    }
    fclose(temp);
    fclose(pFile);

    remove(temp_path);
    free(conf_path);
    free(temp_path);
    return 1;
}

/**
 * @brief Create a fed.cfg config file in HOME dir
 *
 * fed.cfg will hold all information for user's favourite folders
 * @return int Status of function success
 */
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

/**
 * @brief Checks for given folder path in fed.cfg file in HOME dir
 *
 * TODO: better error check
 * @param path Folder path
 * @return int Status of function success
 */
int check_in_favourites(const char *path)
{
    FILE *pFile;
    char buffer[MAX]; /* not ISO 90 compatible */

    char *conf_path = get_cfg_path();
    pFile = fopen(conf_path, "r");

    while (fgets(buffer, MAX, pFile))
    {
        buffer[strlen(buffer) - 1] = '\0';
        if (!strcmp(buffer, path))
            return 1;
    }

    fclose(pFile);
    free(conf_path);
    return 0;
}

/**
 * @brief Checks if alias already exists for fav folder
 *
 * @param alias Alias name
 * @return int Status of if alias exists or not
 */
int check_alias_exists(const char *alias)
{
    FILE *pFile;
    char buffer[MAX]; /* not ISO 90 compatible */
    char temp[MAX];
    char *token;
    char *conf_path = get_cfg_path();
    const char delim[3] = "[]";

    pFile = fopen(conf_path, "r");
    while (fgets(buffer, MAX, pFile))
    {
        buffer[strlen(buffer) - 1] = '\0';
        strcpy(temp, buffer);
        token = strtok(temp, delim);
        if (!strcmp(alias, token))
            return 1;
    }
    free(conf_path);
    return 0;
}
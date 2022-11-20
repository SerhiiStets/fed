#ifndef UTILS_H
#define UTILS_H

typedef struct
{
    const char *alias;
    const char *directory;

} Named_dir;

char *get_cfg_path();
int add_to_clipboard(char *command);
int append_to_config(const char *path);
int remove_from_config(const char *path);
int create_config();
int check_in_favourites(const char *path);
int check_alias_exists(const char *alias);
#endif

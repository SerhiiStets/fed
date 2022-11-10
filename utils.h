#ifndef UTILS_H
#define UTILS_H

char *get_cfg_path();
int check_in_favourites(const char *path);
int append_to_config(const char *path);
int remove_from_config(const char *path);
int create_config();
#endif
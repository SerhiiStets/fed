#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

// TODO check all imports
#include "commands/add.h"
#include "commands/help.h"
#include "commands/ls.h"
#include "commands/clean.h"
#include "definitions.h"
#include "utils.h"

static const char *const builtin_log_usage[] = {
    /*
    N_("git log [<options>] [<revision-range>] [[--] <path>...]"),
    N_("git show [<options>] <object>..."),
    NULL
    */
};

struct cmd_struct
{
    const char *cmd;               /* Command name */
    int (*fn)(int, const char **); /* Command func to run that takes argc and argv */
};

/* List of Command structures */
static struct cmd_struct commands[] = {
    {"add", cmd_add},
    {"ls", cmd_ls},
    {"clean", cmd_clean},
    {"version", cmd_add},
    {"help", cmd_help},
};

/* Returning a pointer to Command structure with given command name */
static struct cmd_struct *get_builtin(const char *s)
{
    int i;
    for (i = 0; i < ARRAY_SIZE(commands); i++)
    {
        struct cmd_struct *p = commands + i;
        if (!strcmp(s, p->cmd))
            return p;
    }
    return NULL;
}

static int run_builtin(struct cmd_struct *p, int argc, const char **argv)
{
    int status;
    status = p->fn(argc, argv);
    return status;
}

int main(int argc, const char *argv[], char **env)
{
    const char *cmd;
    struct cmd_struct *builtin;

    /* Look for flags.. */
    argv++;
    argc--;

    int conf;
    conf = create_config();

    if (!conf)
    {
        fprintf(stderr, "%s: Couldn't create a config file in HOME dir.", CLI_NAME);
        return 1;
    }

    if (!argc)
    {
        /* The user didn't specify a command; give them help */
        cmd_help(argc, argv);
        return 0;
    }

    if (!strcmp("--version", argv[0]) || !strcmp("-v", argv[0]))
        argv[0] = "version";
    else if (!strcmp("--help", argv[0]) || !strcmp("-h", argv[0]))
        argv[0] = "help";

    cmd = argv[0];

    /* Getting pointer to command or NULL */
    builtin = get_builtin(cmd);
    if (builtin)
    {
        /* if command exists in cmd_struct commands[] */
        /* run the command with argv */
        argc--;
        argv++;
        return run_builtin(builtin, argc, argv);
    }

    fprintf(stderr, "%s: %s is not a fed command. See 'fed --help'.\n", CLI_NAME, cmd);

    return 0;
}
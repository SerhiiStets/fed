
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils.h"
#include "../definitions.h"


int cmd_rename(int argc, const char **argv)
{
    if (!argc || argc != 2)
    {
        fprintf(stdout, "%s: <rename> takes two arguments:\n %s rename [old name] [new name].\n", CLI_NAME, CLI_NAME);
        return 1;
    }
    return 1;
}

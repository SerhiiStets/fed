#include <stdio.h>
#include "../definitions.h"

int cmd_help(int argc, const char **argv)
{
    fprintf(stdout, "\n%s usage:\n\n\
    add\t\t[. | <directory>] \t- add current or chosen dir to favourites.\n\
    ls\t\t<range> \t\t- show favoutite fodlers\n\
    clean\t[all | <folder>] \t- remove folders from favourites\n\
    help\t\t\t\t- display help\n\
    version\t\t\t\t- display cli version\n",
            CLI_NAME);
    // TODO add cd
    return 0;
}

int cmd_version(int argc, const char **argv)
{
    fprintf(stdout, "%s version %s\n", CLI_NAME, VERSION);
    return 0;
}
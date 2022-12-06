#include <stdio.h>
#include "../definitions.h"

int cmd_help(int argc, const char **argv)
{
    fprintf(stdout, "\n%s usage:\n\n\
    '.' - dot symbol can be used in commands to represent current directory.\n\n\
    add\n\
    \t\t<directory>\t\t\tadds current or chosen directory to favourites.\n\
    \t\t-a <alias> <directory>\t\tadds directory with given alias to favourites.\n\n\
    cd\n\
    \t\t<number>\tcopies command to cd into folder to clipboard given by folder number in <ls>.\n\
    \t\t<alias>\t\tcopies command to cd into folder to clipboad given by folder alias.\n\
    ls\n\
    \t\t<range> \tshows favoutite fodlers.\n\n\
    clean\n\
    \t\tall\t\tremoves all folders from favourites.\n\
    \t\t<alias>\t\tremoves folder from favourite by given alias.\n\
    \t\t<number>\tremoves fodler given by number in ls list.\n\
    \t\t<directory>\tremoves folder from favourites.\n\n\
    open\n\
    \t\t<alias>\t\topens folder in explorer from favourite by given alias.\n\
    \t\t<number>\topens fodler in explorer given by number in ls list.\n\n\
    help\t\t\tdisplay help.\n\n\
    version\t\t\tdisplay cli version.\n",
            CLI_NAME);
    return 0;
}

int cmd_version(int argc, const char **argv)
{
    fprintf(stdout, "%s version %s\n", CLI_NAME, VERSION);
    return 0;
}

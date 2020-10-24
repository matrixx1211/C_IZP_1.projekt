#include <stdio.h>  /* fprintf */
#include <unistd.h> /* getopt */

int main(int argc, char *argv[])
{
    unsigned verbosity = 0;
    for (;;)
    {
        int opt = getopt(argc, argv, "v");
        if (opt == -1)
            break;
        switch (opt)
        {
        case 'v':
            verbosity++;
            break;
        default:
            /* Unexpected option */
            return 1;
        }
    }

    fprintf(stdout, "Verbosity level: %u\n", verbosity);
    return 0;
}
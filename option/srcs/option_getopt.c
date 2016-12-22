#include "option.h"
#include "option_private.h"

int option_getopt(t_arguments *args, const char *optstring)
{
    return (__option_getopt(args, &((t_option_arguments){optstring, 0, 0, 0})));
}
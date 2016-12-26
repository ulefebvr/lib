#include "option.h"
#include "option_private.h"

int option_getopt_long_only(t_arguments *args, t_option_arguments *options)
{
    return (__option_getopt(args, options, 1));
}
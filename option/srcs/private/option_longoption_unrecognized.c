#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

/*
** Can't find it as a long option.  If this is not getopt_long_only,
** or the option starts with '--' or is not a valid short
** option, then it's an error.
** Otherwise interpret it as a short option.
*/

int __option_treat_longoption_unrecognized(char **argv, t_option_data *d)
{
    if (d->opterr)
    {
        if (argv[d->optind][1] == '-')
            ft_fdprint(2, "%s: unrecognized option '--%s'\n",
                argv[0], d->__nextchar);
        else
            ft_fdprint(2, "%s: unrecognized option '%c%s'\n",
                argv[0], argv[d->optind][0], d->__nextchar);
    }
    d->__nextchar = (char *) "";
    d->optind++;
    d->optopt = 0;
    return ('?');
}
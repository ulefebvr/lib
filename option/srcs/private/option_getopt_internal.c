#include "option.h"
#include "option_private.h"
#include "option_tools.h"

char                    *optarg;
int                     opterr = 1;
int                     optind = 1;
int                     optopt = '?';
static t_option_data    getopt_data;

int __option_r(int argc, char **argv, t_option_data *d)
{
    __option_preparation(d);
    if (-1 == __option_advance_to_next_argv_element(argc, argv, d))
        return (-1);
    if (d->longopts != 0
        && (argv[d->optind][1] == '-'
        || (d->long_only && (argv[d->optind][2]
            || !ft_strchr(d->optstring, argv[d->optind][1])))))
        return (__option_treat_longoption(argc, argv, d));
    return (__option_treat_shortoption(argc, argv, d));
}

int __option_getopt(t_arguments *args, t_option_arguments *options)
{
    int result;

    getopt_data.optind = optind;
    getopt_data.opterr = opterr;

    getopt_data.optstring = options->optstring;
    getopt_data.longopts = options->longopts;
    getopt_data.long_only = options->long_only;
    getopt_data.longind = options->longind;

    result = __option_r(
        args->argc, args->argv, &getopt_data
    );

    optind = getopt_data.optind;
    optarg = getopt_data.optarg;
    optopt = getopt_data.optopt;

    return (result);
}

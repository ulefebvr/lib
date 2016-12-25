#include "option.h"
#include "option_private.h"
#include "option_tools.h"

char                    *g_option_optarg;
int                     g_option_opterr = 1;
int                     g_option_optind = 1;
int                     g_option_optopt = '?';
static t_option_data    g_option_getopt_data;

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

    g_option_getopt_data.optind = g_option_optind;
    g_option_getopt_data.opterr = g_option_opterr;

    g_option_getopt_data.optstring = options->optstring;
    g_option_getopt_data.longopts = options->longopts;
    g_option_getopt_data.long_only = options->long_only;
    g_option_getopt_data.longind = options->longind;

    result = __option_r(
        args->argc, args->argv, &g_option_getopt_data
    );

    g_option_optind = g_option_getopt_data.optind;
    g_option_optarg = g_option_getopt_data.optarg;
    g_option_optopt = g_option_getopt_data.optopt;

    return (result);
}

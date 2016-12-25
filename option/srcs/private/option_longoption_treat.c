#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

int __option_treat_longoption(int argc, char **argv, t_option_data *d)
{
    t_treat_longoption info;

    info = (t_treat_longoption){0, 0, 0, 0, 0, 0, 0, 0};
    info.namelen = __option_treat_longoption_get_namelen(&info, d);
    __option_treat_longoption_test_match(&info, d);
    if (info.ambig_list != 0 && !info.exact)
        return (__option_treat_longoption_ambiguous(argv, &info, d));
    if (info.pfound != 0)
        return (__option_treat_longoption_arguments(&(t_arguments){argc, argv, 0}, &info, d));
    if (!d->long_only || argv[d->optind][1] == '-'
        || ft_strchr (d->optstring, *d->__nextchar) == 0)
        return (__option_treat_longoption_unrecognized(argv, d));
    return (0);
}

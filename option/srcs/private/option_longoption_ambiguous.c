#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

int __option_treat_longoption_ambiguous(char **argv, t_treat_longoption *info, t_option_data *d)
{
    struct option_list first;

    if (d->opterr)
    {
        first.p = info->pfound;
        first.next = info->ambig_list;
        info->ambig_list = &first;
        ft_fdprint(2, "%s: option '%s' is ambiguous; possibilities:", 
            argv[0], argv[d->optind]);
        while (info->ambig_list != 0)
        {
            ft_fdprint(2, " '--%s'", info->ambig_list->p->name);
            info->ambig_list = info->ambig_list->next;
        }
        ft_fdprint(2, "\n");
    }
    d->__nextchar += ft_strlen(d->__nextchar);
    d->optind++;
    d->optopt = 0;
    return ('?');
}

#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

#include <stdlib.h>

int __option_treat_longoption_ambiguous(char **argv, t_treat_longoption *info, t_option_data *d)
{
    t_option_list *tmp;

    if (d->opterr)
    {
        ft_fdprint(2, "%s: option '%s' is ambiguous; possibilities: '--%s'", 
            argv[0], argv[d->optind], info->pfound->name);
        while (info->ambig_list != 0)
        {
            ft_fdprint(2, " '--%s'", info->ambig_list->p->name);
            tmp = info->ambig_list;
            info->ambig_list = info->ambig_list->next;
            free(tmp);
        }
        ft_fdprint(2, "\n");
    }
    d->__nextchar += ft_strlen(d->__nextchar);
    d->optind++;
    d->optopt = 0;
    return ('?');
}

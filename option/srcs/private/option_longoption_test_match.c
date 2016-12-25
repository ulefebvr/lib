#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

#include <stdlib.h>

/*
** Decode the current option-ARGV-element.
** 
** Check whether the ARGV-element is a long option.
** 
** If long_only and the ARGV-element has the form "-f", where f is
** a valid short option, don't consider it an abbreviated form of
** a long option that starts with f.  Otherwise there would be no
** way to give the -f short option.
** 
** On the other hand, if there's a long option "fubar" and
** the ARGV-element is "-fu", do consider that an abbreviation of
** the long option, just like "--fu", and not "-f" with arg "u".
** 
** This distinction seems to be the most useful approach.
*/

int __option_treat_longoption_get_namelen(t_treat_longoption *info, t_option_data *d)
{
    info->nameend = d->__nextchar;
    while (info->nameend && *info->nameend && '=' != *info->nameend)
        ++info->nameend;
    return (info->nameend - d->__nextchar);
}

void __option_treat_longoption_test_match_exact_match(t_treat_longoption *info)
{
    info->pfound = info->p;
    info->indfound = info->option_index;
    info->exact = 1;
}

void __option_treat_longoption_test_match_nonexact_match(t_treat_longoption *info, t_option_data *d)
{
    t_option_list *newp;

    newp = 0;
    if (info->pfound == 0)
    {
        info->pfound = info->p;
        info->indfound = info->option_index;
    }
    else if (d->long_only
        || info->pfound->has_arg != info->p->has_arg
        || info->pfound->flag != info->p->flag
        || info->pfound->val != info->p->val)
    {
        newp = (t_option_list *)malloc(sizeof(*newp));
        newp->p = info->p;
        newp->next = info->ambig_list;
        info->ambig_list = newp;
    }
}

/*
** Test all long options for either exact match
** or abbreviated matches.
*/

void __option_treat_longoption_test_match(t_treat_longoption *info, t_option_data *d)
{
    info->p = d->longopts;
    info->option_index = 0;
    while (info->p->name)
    {
        if (!ft_strncmp(info->p->name, d->__nextchar, info->namelen))
        {
            if (info->namelen == ft_strlen(info->p->name))
            {
                __option_treat_longoption_test_match_exact_match(info);
                break ;
            }
            else
                __option_treat_longoption_test_match_nonexact_match(info, d);
        }
        info->p++;
        info->option_index++;
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_longoption_argument.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 18:51:19 by ulefebvr          #+#    #+#             */
/*   Updated: 2016/12/26 18:51:19 by ulefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "option_private.h"
#include "option_longoption.h"
#include "option_tools.h"

int __option_treat_longoption_arguments_required(t_arguments *args, t_treat_longoption *info, t_option_data *d)
{
    if (d->optind < args->argc)
        d->optarg = args->argv[d->optind++];
    else
    {
        if (d->opterr)
        {
            ft_fdprint(2, "%s: option '--%s' requires an argument\n",
                args->argv[0], info->pfound->name);
        }
        d->__nextchar += ft_strlen (d->__nextchar);
        d->optopt = info->pfound->val;
        return (d->optstring[0] == ':' ? ':' : '?');
    }
    return (0);
}

int __option_treat_longoption_arguments_dont(t_arguments *args, t_treat_longoption *info, t_option_data *d)
{
    if (info->pfound->has_arg)
        d->optarg = info->nameend + 1;
    else
    {
        if (d->opterr)
        {
            if (args->argv[d->optind - 1][1] == '-')
                ft_fdprint(2, "%s: option '--%s' doesn't allow an argument\n",
                    args->argv[0], info->pfound->name);
            else
                ft_fdprint(2, "%s: option '%c%s' doesn't allow an argument\n",
                    args->argv[0], args->argv[d->optind - 1][0], info->pfound->name);
        }
        d->__nextchar += ft_strlen(d->__nextchar);
        d->optopt = info->pfound->val;
        return ('?');
    }
    return (0);
}

int __option_treat_longoption_arguments(t_arguments *args, t_treat_longoption *info, t_option_data *d)
{
    int ret;

    info->option_index = info->indfound;
    d->optind++;
    if (info->nameend && *info->nameend)
    {
        if (0 != (ret = __option_treat_longoption_arguments_dont(args, info, d)))
            return (ret);
    }
    else if (1 == info->pfound->has_arg)
    {
        if (0 != (ret = __option_treat_longoption_arguments_required(args, info, d)))
            return (ret);
    }
    d->__nextchar += ft_strlen(d->__nextchar);
    if (d->longind != 0)
        *d->longind = info->option_index;
    if (info->pfound->flag)
    {
        *(info->pfound->flag) = info->pfound->val;
        return (0);
    }
    return (info->pfound->val);
}

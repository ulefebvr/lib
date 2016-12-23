#include "option.h"
#include "option_private.h"

/*
** Bottom segment is the short one.
** Swap it with the top part of the top segment.
** Exclude the moved bottom segment from further swapping.
*/

int __option_exhange_swap_segment_bottom(char **argv, int bottom, int middle, int top)
{
    char *tem;
    int len;
    int i;

    i = -1;
    len = middle - bottom;
    while (++i < len)
    {
        tem = argv[bottom + i];
        argv[bottom + i] = argv[top - (middle - bottom) + i];
        argv[top - (middle - bottom) + i] = tem;
    }
    top -= len;
    return len;
}

/*
** Top segment is the short one.
** Swap it with the bottom part of the bottom segment.
** Exclude the moved top segment from further swapping.
*/

int __option_exhange_swap_segment_top(char **argv, int bottom, int middle, int top)
{
    char *tem;
    int len;
    int i;

    i = -1;
    len = top - middle;
    while (++i < len)
    {
        tem = argv[bottom + i];
        argv[bottom + i] = argv[middle + i];
        argv[middle + i] = tem;
    }
    bottom += len;
    return len;
}

/*
** Exchange two adjacent subsequences of ARGV.
** One subsequence is elements [first_nonopt,last_nonopt)
** which contains all the non-options that have been skipped so far.
** The other is elements [last_nonopt,optind), which contains all
** the options processed since those non-options were skipped.
** 
** `first_nonopt' and `last_nonopt' are relocated so that they describe
** the new indices of the non-options in ARGV after they are moved.
*/

void __option_exchange(char **argv, t_option_data *d)
{
    int bottom;
    int middle;
    int top;

    bottom = d->__first_nonopt;
    middle = d->__last_nonopt;
    top = d->optind;
    while (top > middle && middle > bottom)
    {
        if (top - middle > middle - bottom)
        {
            top -= __option_exhange_swap_segment_bottom(argv, bottom, middle, top);
        }
        else
        {
            bottom += __option_exhange_swap_segment_top(argv, bottom, middle, top);
        }
    }
    d->__first_nonopt += (d->optind - d->__last_nonopt);
    d->__last_nonopt = d->optind;
}

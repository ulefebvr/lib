#include "option.h"
#include "option_private.h"
#include "option_tools.h"

/*
** Give FIRST_NONOPT & LAST_NONOPT rational values if OPTIND has been
** moved back by the user (who may also have changed the arguments).
*/

void __option_check_nonopt_values(t_option_data *d)
{
    if (d->__last_nonopt > d->optind)
        d->__last_nonopt = d->optind;
    if (d->__first_nonopt > d->optind)
        d->__first_nonopt = d->optind;
}

/*
** If we have just processed some options following some non-options,
** exchange them so that the options come first.
** 
** Skip any additional non-options
** and extend the range of non-options previously skipped.
*/

void __option_permute_prepare(int argc, char **argv, t_option_data *d)
{
    if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optind)
        __option_exchange((char **) argv, d);
    else if (d->__last_nonopt != d->optind)
        d->__first_nonopt = d->optind;
    while (d->optind < argc && NONOPTION_P)
        d->optind++;
    d->__last_nonopt = d->optind;
}

/*
** The special ARGV-element `--' means premature end of options.
** Skip it like a null option,
** then exchange with previous non-options as if it were an option,
** then skip everything else like a non-option.
*/

void __option_premature_end(int argc, char **argv, t_option_data *d)
{
    d->optind++;
    if (d->__first_nonopt != d->__last_nonopt && d->__last_nonopt != d->optind)
        __option_exchange ((char **) argv, d);
    else if (d->__first_nonopt == d->__last_nonopt)
        d->__first_nonopt = d->optind;
    d->__last_nonopt = argc;
    d->optind = argc;
}

/*
** If we have done all the ARGV-elements, stop the scan
** and back over any non-options that we skipped and permuted.
** Set the next-arg-index to point at the non-options
** that we previously skipped, so the caller will digest them.
*/

int __option_handle_reach_end(t_option_data *d)
{
    if (d->__first_nonopt != d->__last_nonopt)
        d->optind = d->__first_nonopt;
    return (-1);
}

/*
** If we have come to a non-option and did not permute it,
** either stop the scan or describe it to the caller and pass it by.
*/

int __option_handle_reach_nonoption(char **argv, t_option_data *d)
{
    if (d->__ordering == REQUIRE_ORDER)
        return (-1);
    d->optarg = argv[d->optind++];
    return (1);
}

/*
** Advance to the next ARGV-element.
*/

int __option_advance_to_next_argv_element(int argc, char **argv, t_option_data *d)
{
    if (0 == d->__nextchar || 0 == *d->__nextchar)
    {
        __option_check_nonopt_values(d);
        if (d->__ordering == PERMUTE)
            __option_permute_prepare(argc, argv, d);
        if (d->optind != argc && !ft_strcmp(argv[d->optind], "--"))
            __option_premature_end(argc, argv, d);
        if (d->optind == argc)
            return (__option_handle_reach_end(d));
        if (NONOPTION_P)
            return (__option_handle_reach_nonoption(argv, d));
        d->__nextchar = (argv[d->optind] + 1
            + (d->longopts != 0 && argv[d->optind][1] == '-'));
    }
    return (1);
}

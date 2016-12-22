#include "option.h"
#include "option_private.h"

/*
** Determine how to handle the ordering of options and nonoptions.
*/

void __option_handle_ordering(t_option_data *d)
{
    if (*d->optstring == '-')
    {
        d->__ordering = RETURN_IN_ORDER;
        ++d->optstring;
    }
    else if (*d->optstring == '+')
    {
        d->__ordering = REQUIRE_ORDER;
        ++d->optstring;
    }
    else
        d->__ordering = PERMUTE;
}

/*
** Start processing options with ARGV-element 1 (since ARGV-element 0
** is the program name); the sequence of previously skipped
** non-option ARGV-elements is empty.
*/

const char *__option_initialize(t_option_data *d)
{
        d->optind = d->optind ? d->optind : 1;
        d->__first_nonopt = d->optind;
        d->__last_nonopt = d->optind;
        __option_handle_ordering(d);
        d->__initialized = 1;
        return (d->optstring);
}

void __option_preparation(t_option_data *d)
{
    d->optarg = 0;
    if (d->optind == 0 || d->__initialized == 0)
        __option_initialize(d);
    else if (*d->optstring == '-' || *d->optstring == '+')
        ++d->optstring;
    if (*d->optstring == ':')
        d->opterr = 0;
}

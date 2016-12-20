typedef struct          s_arguments
{
    int                 argc;
    char                **argv;
    char                **env;
}                       t_arguments;

typedef struct          s_option_info
{
    const char          *name;
    int                 has_arg;
    int                 *flag;
    int                 val;
}                       t_option_info;

typedef struct          s_option_arguments
{
    const char          *optstring;
    t_option_info       *longopts;
    int                 *longind;
    int                 long_only;
}                       t_option_arguments;


# define no_argument		0
# define required_argument	1
# define optional_argument	2

typedef enum            e_ordering
{
    REQUIRE_ORDER, PERMUTE, RETURN_IN_ORDER
}                       t_ordering;

typedef struct          s_option_data
{
    const char          *optstring;
    t_option_info       *longopts;
    int                 long_only;

    int                 optind;
    int                 opterr;
    int                 optopt;
    char                *optarg;

    int                 __initialized;
    char                *__nextchar;

    t_ordering          __ordering;

    int                 __first_nonopt;
    int                 __last_nonopt;
}                       t_option_data;

char                    *optarg;
int                     opterr = 1;
int                     optind = 1;
int                     optopt = '?';
static t_option_data    getopt_data;

/*
** Test whether ARGV[optind] points to a non-option argument.
** Either it does not have option syntax, or there is an environment flag
** from the shell indicating it is not an option.  The later information
** is only used when the used in the GNU libc.
*/

# define NONOPTION_P (argv[d->optind][0] != '-' || argv[d->optind][1] == '\0')

/*
** Retun if the returned is equal to 'status'.
*/

# define RETURN_IF(equation, status) if ((equation) == (status)){return (status);}

/*-----------------------------------------------------------------*/

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

const char *__option_initialize(char **av, t_option_data *d)
{
        d->optind = d->optind ? d->optind : 1;
        d->__first_nonopt = d->optind;
        d->__last_nonopt = d->optind;
        __option_handle_ordering(d);
        d->__initialized = 1;
        return (d->optstring);
}

void __option_preparation(char **argv, t_option_data *d)
{
    d->optarg = 0;
    if (d->optind == 0 || d->__initialized == 0)
        __option_initialize(argv, d);
    else if (*d->optstring == '-' || *d->optstring == '+')
        ++d->optstring;
    if (*d->optstring == ':')
        d->opterr = 0;
}

/*-----------------------------------------------------------------*/

/*
** Bottom segment is the short one.
** Swap it with the top part of the top segment.
** Exclude the moved bottom segment from further swapping.
*/

void __option_exhange_swap_segment_bottom(char **argv, int bottom, int middle, int top)
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
}

/*
** Top segment is the short one.
** Swap it with the bottom part of the bottom segment.
** Exclude the moved top segment from further swapping.
*/

void __option_exhange_swap_segment_top(char **argv, int bottom, int middle, int top)
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
    char *tem;

    bottom = d->__first_nonopt;
    middle = d->__last_nonopt;
    top = d->optind;
    while ((unsigned)(top - middle) < bottom)
    {
        if (top - middle > middle - bottom)
        {
            __option_exhange_swap_segment_bottom(argv, bottom, middle, top);
        }
        else
        {
            __option_exhange_swap_segment_top(argv, bottom, middle, top);
        }
    }
    d->__first_nonopt += (d->optind - d->__last_nonopt);
    d->__last_nonopt = d->optind;
}

/*-----------------------------------------------------------------*/

int ft_strcmp(char *p1, char *p2)
{
    if (0 == p1 || 0 == p2)
        return (-1);
    while ((unsigned char)*p1 == (unsigned char)*p2)
    {
        if ((unsigned char)*p1 == '\0')
            return ((unsigned char)p1 - (unsigned char)p2);
        ++p1;
        ++p2;
    }
    return ((unsigned char)*p1 - (unsigned char)*p2);
}

/*-----------------------------------------------------------------*/

char *ft_strchr(const char *str, char c)
{
    while (str && *str)
        if (*str == c)
            return ((char *)str);
        else
            ++str;
    return (0);
}

/*-----------------------------------------------------------------*/

int ft_strlen(const char *str)
{
    char *p;

    p = (char *)str;
    while (p && *p)
        p++;
    return (p - str);
}

/*-----------------------------------------------------------------*/

int ft_strncmp(const char *p1, const char *p2, int size)
{
    if (0 == p1 || 0 == p2)
        return (-1);
    while ((unsigned char)*p1 == (unsigned char)*p2 && --size)
    {
        if ((unsigned char)*p1 == '\0')
            return ((unsigned char)p1 - (unsigned char)p2);
        ++p1;
        ++p2;
    }
    return ((unsigned char)*p1 - (unsigned char)*p2);
}

/*-----------------------------------------------------------------*/

#include <stdarg.h>
#include <unistd.h>

int ft_putstr_fd(char *str, int fd)
{
    return (write(fd, str, ft_strlen(str)));
}

int ft_putchar_fd(int c, int fd)
{
    return (write(fd, (char *)&c, 1));
}

void		run_print(int fd, const char *fmt, va_list list)
{
	while (*fmt)
	{
		if (*fmt == '%' && fmt++)
		{
			if (*fmt == 's')
				ft_putstr_fd(va_arg(list, char *), fd);
			else if (*fmt == 'c')
				ft_putchar_fd(va_arg(list, int), fd);
			fmt++;
		}
		else
			write(fd, fmt++, 1);
	}
}

int			ft_fdprint(int fd, const char *fmt, ...)
{
	va_list		list;

	if (fmt)
	{
		va_start(list, fmt);
		run_print(fd, fmt, list);
		va_end(list);
	}
	return (1);
}

/*-----------------------------------------------------------------*/

#define IF_PERMUTE(x) if (getopt_data.__ordering == PERMUTE) {x}

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

int __option_handle_reach_end(int argc, t_option_data *d)
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
        if (getopt_data.__ordering == PERMUTE)
            __option_permute_prepare(argc, argv, d);
        if (d->optind != argc && !ft_strcmp(argv[d->optind], "--"))
            __option_premature_end(argc, argv, d);
        if (d->optind == argc)
            return (__option_handle_reach_end(argc, d));
        if (NONOPTION_P)
            return (__option_handle_reach_nonoption(argv, d));
        d->__nextchar = (argv[d->optind] + 1
            + (d->longopts != 0 && argv[d->optind][1] == '-'));
    }
    return (1);
}



/*-----------------------------------------------------------------*/

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

typedef struct              option_list
{
    t_option_info           *p;
    struct option_list      *next;
}                           t_option_list;

typedef struct              s_treat_longoption
{
    char                    *nameend;
    unsigned int            namelen;
    t_option_info           *p;
    t_option_info           *pfound;
    t_option_list           *ambig_list;
    int                     exact;
    int                     indfound;
    int                     option_index;
}                           t_treat_longoption;

#include <stdlib.h>

int __option_treat_longoption_get_namelen(t_treat_longoption *info, t_option_data *d)
{
    char *nameend;

    nameend = d->__nextchar;
    while (nameend && *nameend && '=' != *nameend)
        ++nameend;
    return (nameend - d->__nextchar);
}

int __option_treat_longoption_test_match_exact_match(t_treat_longoption *info, t_option_data *d)
{
    info->pfound = info->p;
    info->indfound = info->option_index;
    info->exact = 1;
}

int __option_treat_longoption_test_match_nonexact_match(t_treat_longoption *info, t_option_data *d)
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
                __option_treat_longoption_test_match_exact_match(info, d);
                break ;
            }
            else
                __option_treat_longoption_test_match_nonexact_match(info, d);
        }
        info->p++;
        info->option_index++;
    }
}

/*-----------------------------------------------------------------*/

int __option_treat_longoption_ambiguous(char **argv, t_treat_longoption *info, t_option_data *d, int *ret)
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
    return ((*ret = '?'));
}

/*-----------------------------------------------------------------*/

int __option_treat_longoption_arguments(char **argv, t_treat_longoption *info, t_option_data *d, int *ret)
{
    
}

/*-----------------------------------------------------------------*/

int __option_treat_longoption(int argc, char **argv, t_option_data *d, int *ret)
{
    t_treat_longoption info;

    info = (t_treat_longoption){0, 0, 0, 0, 0, 0, 0, 0};
    if (d->longopts != 0
        && (argv[d->optind][1] == '-'
        || (d->long_only && (argv[d->optind][2]
            || !ft_strchr(d->optstring, argv[d->optind][1])))))
    {
        info.namelen = __option_treat_longoption_get_namelen(&info, d);
        __option_treat_longoption_test_match(&info, d);
        if (info.ambig_list != 0 && !info.exact)
            return (__option_treat_longoption_ambiguous(argv, &info, d, ret));
        if (info.pfound != 0)
            return (__option_treat_longoption_arguments(argv, &info, d, ret));
    }
    return (0);
}

/*-----------------------------------------------------------------*/

int __option_r(int argc, char **argv, t_option_data *d, int *longind)
{
    int         ret;

    ret = 0;
    __option_preparation(argv, d);
    if (-1 == __option_advance_to_next_argv_element(argc, argv, d))
        return (-1);
    if (0 != __option_treat_longoption(argc, argv, d, &ret))
        return (ret);
}

int __option_getopt(t_arguments *args, t_option_arguments *options)
{
    int result;

    getopt_data.optind = optind;
    getopt_data.opterr = opterr;
    getopt_data.optstring = options->optstring;
    getopt_data.longopts = options->longopts;
    getopt_data.long_only = options->long_only;
    
    result = __option_r(
        args->argc, args->argv, &getopt_data, options->longind
    );

    optind = getopt_data.optind;
    optarg = getopt_data.optarg;
    optopt = getopt_data.optopt;

    return (result);
}

int option_getopt(t_arguments *args, const char *optstring)
{
    return (__option_getopt(args, &((t_option_arguments){optstring, 0, 0, 0})));
}

int option_getoptlong(t_arguments *args, t_option_arguments *options)
{
    return (__option_getopt(args, options));
}
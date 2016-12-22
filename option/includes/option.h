#ifndef OPTION_H
# define OPTION_H

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

extern char                    *optarg;
extern int                     opterr;
extern int                     optind;
extern int                     optopt;

int option_getopt(t_arguments *args, const char *optstring);
int option_getopt_long(t_arguments *args, t_option_arguments *options);
int option_getopt_long_only(t_arguments *args, t_option_arguments *options);

#endif
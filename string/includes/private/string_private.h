#ifndef STRING_PRIVATE_H
# define STRING_PRIVATE_H

/*
** Return the len a of the given argument.
*/

int						str_len(char *);

/*
** Allocate and join the two given arguments.
*/

char					*str_join(char *str1, char *str2);

/*
** Concatenate the two given arguments.
*/

char					*str_cat(char *str1, char *str2);

#endif
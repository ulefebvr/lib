#include "string.h"

char *string_add(char *str, char c)
{
    char    add[2];

    add[0] = c;
    add[1] = 0;
    return (string_cat(str, add));
}
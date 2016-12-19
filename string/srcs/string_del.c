#include "string.h"

char *string_del(char *str)
{
    free(STRING(str)->str);
    free(STRING(str));
    return (0);
}
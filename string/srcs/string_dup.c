#include "string.h"

char *string_dup(char *str)
{
    return (string_new(STRING(str)->str));
}
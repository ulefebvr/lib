#include "string.h"
#include "string_private.h"

char			*string_join(char *str, char *add)
{
	char *tmp;

	tmp = STRING(str)->str;
	STRING(str)->str = str_join(STRING(str)->str, add);
	STRING(str)->len = str_len(STRING(str)->str);
	free(tmp);
	return ((char *)&STRING(str)->str);
}
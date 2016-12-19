#include "string_private.h"

#include <stdlib.h>

char		*str_join(char *str1, char *str2)
{
	char	*str;

	if (0 != (str = (char *)malloc(
		sizeof(char) * (str_len(str1) + str_len(str2)))))
		str_cat(str_cat(str, str1), str2);
	return (str);
}
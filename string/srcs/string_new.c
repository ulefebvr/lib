#include "string.h"

char				*string_new(char *str)
{
	t_string		*string;

	if (0 == (string = (t_string *)malloc(sizeof(t_string))))
		return 0;
	string->str = 0;
	string->len = 0;
	string_cat((char *)&string->str, str);
	return ((char *)&string->str);
}

int				str_len(char *str)
{
	char		*len;

	len = str;
	while(len && *len)
		++len;
	return (len - str);
}

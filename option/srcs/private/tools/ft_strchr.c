char *ft_strchr(const char *str, char c)
{
    while (str && *str)
        if (*str == c)
            return ((char *)str);
        else
            ++str;
    return (0);
}

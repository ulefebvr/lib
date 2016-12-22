int ft_strlen(const char *str)
{
    char *p;

    p = (char *)str;
    while (p && *p)
        p++;
    return (p - str);
}

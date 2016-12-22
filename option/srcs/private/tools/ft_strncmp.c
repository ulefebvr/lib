int ft_strncmp(const char *p1, const char *p2, int size)
{
    if (0 == p1 || 0 == p2)
        return (-1);
    while ((unsigned char)*p1 == (unsigned char)*p2 && --size)
    {
        if ((unsigned char)*p1 == '\0')
            return ((unsigned char)*p1 - (unsigned char)*p2);
        ++p1;
        ++p2;
    }
    return ((unsigned char)*p1 - (unsigned char)*p2);
}

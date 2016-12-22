int ft_strcmp(char *p1, char *p2)
{
    if (0 == p1 || 0 == p2)
        return (-1);
    while ((unsigned char)*p1 == (unsigned char)*p2)
    {
        if ((unsigned char)*p1 == '\0')
            return ((unsigned char)*p1 - (unsigned char)*p2);
        ++p1;
        ++p2;
    }
    return ((unsigned char)*p1 - (unsigned char)*p2);
}

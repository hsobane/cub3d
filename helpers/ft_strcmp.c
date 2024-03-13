#include "cub3d.h"

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    if (s1[i] == NULL && s2[i] == NULL)
        return (0);
    return (s1[i] - s2[i]);
}
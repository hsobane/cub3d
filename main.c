

#include "cub3d.h"

int main(int ac, char **av)
{
    char **map;

    if (ac != 2)
    {
        write (1, "invalid number of arguments\n", 28);
        reutrn (0);
    }
    map = parser(av[1]);
    if (map == NULL)
        return (0);
}
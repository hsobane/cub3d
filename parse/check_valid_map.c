#include "../cub3d.h"

int is_valid_extension(char *file)
{
    char *extension;
    int len;

    extension = ".cub";
    len = ft_strlen(file);
    if (len <= 4)
    {
        write (1, "invalid extension\n", 18);
        return (0);
    }
    if (!ft_strcmp(file + (len - 4), ".cub"))
    {
        write (1, "invalid extension\n", 18);
        return (0);
    }
    return (1);
}

int is_valid_map(char **map)
{
    
}
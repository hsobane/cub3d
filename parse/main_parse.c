
#include "../cub3d.h"

char *reallocation(t_parser *parser, int len)
{
    char **new_arr;
    int i;

    i = 0;
    new_arr = malloc(len + 2);
    if (!new_arr)
    {
        (free_list(parser));
        exit(1);
    }
    while  (i < len)
    {
        new_arr[i] = parser->map[i];
        i++;
    }
    new_arr[i] = NULL;
    free(parser->map);
    return (new_arr);
}

int is_texture(t_parser *parser, char *line)
{
    char **tmp;

    tmp = split(line, ' ');
    if (!tmp)
    {
        (free_list(parser), free(line));
        exit (1);
    }
    if (!(*tmp))
        return (-1);
    if (ft_strcmp(tmp[0] , "SO") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    if (ft_strcmp(tmp[0] , "NO") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    if (ft_strcmp(tmp[0] , "WE") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    if (ft_strcmp(tmp[0] , "EA") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    if (ft_strcmp(tmp[0] , "C") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    if (ft_strcmp(tmp[0] , "F") == 0)
        return (ft_copy(tmp, parser->SO), 1);
    return (0);
}

void remplissage(t_parser *parser)
{
    int i;
    int fd;
    char *line;

    i = 0;
    fd = open("file", O_RDONLY);
    parser->map = malloc(1);
    while (1)
    {
        line = get_next_line(fd);
        if (!line)
            break ;
        if (!is_texture(&parser, line))
        {
            parser->map[i++] = line;
            reallocation(&parser, i);
        }
    }
}

int parser(char *file)
{
    int fd;
    t_parser parser;
    char **map;
    
    if (!is_valid_extension(file))
    {
        write (1, "invalid extension\n", 18);
        return (NULL);
    }
    initialize(&parser);
    remplissage(&parser);
    if (!check_valid_map(map))
        return (free_tab(map), NULL);
    return (map);
}
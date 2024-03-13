#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

typedef enum s_texture
{
    NO,
    SO,
    WE,
    EA,
    F,
    C,
    EMPTY,
    MAP
}   t_texture;

typedef struct s_pareser
{
    t_texture       texture;
    char            *line;
    struct s_parser *next;
}   t_parser;

typedef struct s_parser
{
    char **map;
    char **NO;
    char **SO;
    char **WE;
    char **EA;
    char **F;
    char **C;
}   t_parser;

#endif
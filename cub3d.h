#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
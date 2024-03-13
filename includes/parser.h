/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsobane <hsobane@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:50:03 by hsobane           #+#    #+#             */
/*   Updated: 2024/03/13 14:15:41 by hsobane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "cub3d.h"

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

// typedef struct s_parser
// {
//     char **map;
//     char **NO;
//     char **SO;
//     char **WE;
//     char **EA;
//     char **F;
//     char **C;
// }   t_parser;

#endif
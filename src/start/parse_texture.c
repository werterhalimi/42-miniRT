/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/21 16:51:14 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"



char	*get_ppm_line(int fd)
{
	char	*tmp;
	char	*line;

	line = get_next_line(fd);
	while (line && *line == '#')
		line = get_next_line(fd);
	if (!line)
		return (0);
	tmp = ft_strtrim(line, " \t");
	free(line);
	return (tmp);
}


int	read_ppm(t_object *obj, int fd)
{
	int		valid;
	char	*line;
	char 	*tmp;

	line= malloc(15);
	tmp = line;
	t_texture *texture = ft_calloc(1, sizeof(t_texture));
	texture->value = 0;
	texture->height = 0;
	texture->width = 0;
	valid = 0;

	read(fd, line, 15);
	while (texture->value == 0)
	{
		if (ft_strncmp(line, "P6", 2) == 0)
		{
			if (valid)
				return (print_error(ERROR, "PPM file has two P6 declaration"));
			valid = 1;
			while (*(++line) && (*line != '\n'))
				continue ;
			if (*line == '\n') line++;
		}
		while (*line && valid)
		{
			if (*line && texture->width == 0)
				texture->width = ft_atoi(line);
			else if (*line && texture->height == 0)
				texture->height = ft_atoi(line);
			else
			{
				texture->value = ft_atoi(line);
				break ;
			}
			while (*(line) && (*line != ' ' && *line != '\n'))
				line++;
			if (*line == ' ' || *line == '\n') line++;
		}
	}
	free(tmp);
	if (!valid) 
		return (print_error(ERROR, "PPM file doesn't have P3 declaration"));

	texture->value = 255 / texture->value;
	unsigned char	*map;
	map = malloc(sizeof(*map) * texture->width*texture->height*3);
	read(fd,map, texture->width*texture->height*3);
	texture->pixels = ft_calloc(texture->height - 1, sizeof(*texture->pixels));

	int	i;
	int	j;
	int	y;

	j = 0;
	i = 0;
	while(i < texture->height)
	{
		y = 0;
		texture->pixels[i] = ft_calloc(texture->width - 1, sizeof(t_color));
		while (y < texture->width)
		{
			texture->pixels[i][y] = (t_color) {map[j], map[j+1], map[j+2]};
			j += 3;
			y++;
		}
		i++;
	}
	free(map);
	obj->texture = texture;
	return (SUCCESS);
}

int	parse_texture(t_object *object, char *item)
{
	char		*tmp;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	tmp = ft_strtrim(item, "\n \t");
	fd = open(tmp, O_RDONLY);
	free(tmp);
	if (fd < 0)
		return (print_error(ERROR, "invalid texture file"));
	return (read_ppm(object, fd));
}

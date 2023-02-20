/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/21 00:20:29 by shalimi          ###   ########.fr       */
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

	t_texture *texture = ft_calloc(1, sizeof(t_texture));
	texture->value = 0;
	texture->height = 0;
	texture->width = 0;
	valid = 0;

	while (texture->value == 0)
	{
		line = get_ppm_line(fd);
		if (ft_strncmp(line, "P3", 2) == 0)
		{
			if (valid)
				return (print_error(ERROR, "PPM file has two P3 declaration"));
			valid = 1;
			while (*(++line) && (*line != ' ' && *line != '\t'))
				continue ;
		}
		while (*line && valid)
		{
			if (*line && texture->width == 0)
			{
				texture->width = ft_atoi(line);
				while (*(++line) && (*line != ' ' && *line != '\t'))
					continue ;
			}
			if (*line && texture->height == 0)
			{
				texture->height = ft_atoi(line);
				while (*(++line) && (*line != ' ' && *line != '\t'))
					continue ;
			}
			if (*line && texture->value == 0)
			{
				texture->value = ft_atoi(line);
				break;
			}
			line++;
		}
	}
	if (!valid) 
		return (print_error(ERROR, "PPM file doesn't have P3 declaration"));

	texture->value = 255 / texture->value;
	texture->pixels = ft_calloc(texture->height - 1, sizeof(*texture->pixels));
	int		i;
	int		j;
	int		y;

	i = 0;
	while (i < texture->height - 1)
	{
		printf("%i\n", i);
		y = 0;
		texture->pixels[i] = ft_calloc(texture->width - 1, sizeof(t_color));
		while (y < texture->width - 1)
		{
			line = get_ppm_line(fd);
			if (!line) break;
			j = 0;
			while (*line)
			{
				while (*line && !ft_isdigit(*line))
					line++;
				if (!*line) break;
				if (j == 0)
				{
					texture->pixels[i][y].r = (char) (ft_atoi(line) / texture->value);
					j++;
					while (*line && ft_isdigit(*line)) line++;
					continue ;
				}
				if (j == 1)
				{
					texture->pixels[i][y].g = (char) (ft_atoi(line) / texture->value);
					j++;
					while (*line && ft_isdigit(*line)) line++;
					continue ;
				}
				if (j == 2)
				{
					texture->pixels[i][y].b = (char) (ft_atoi(line) / texture->value);
					j = 0;
					y++;
					while (*line && ft_isdigit(*line)) line++;
					continue ; 
				}
			}
		/*	split = ft_split(line, ' ');
			len = 0;
			j = 0;
			while (split[len])
				len++;
			while (j < len)
			{
				texture->pixels[i][y].r = (char) (ft_atoi(split[j]) / texture->value);
				texture->pixels[i][y].g = (char) (ft_atoi(split[(j + 1)]) / texture->value);
				texture->pixels[i][y].b = (char) (ft_atoi(split[(j + 2)]) / texture->value);
				j+=3;
				y++;
			}*/
		}
		i++;
	}
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

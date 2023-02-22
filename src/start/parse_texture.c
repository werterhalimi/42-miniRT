/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shalimi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 15:42:50 by shalimi           #+#    #+#             */
/*   Updated: 2023/02/22 17:52:06 by shalimi          ###   ########.fr       */
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

static char	*append(char *str, char a)
{
	char	*ret;
	int		len;

	len = ft_strlen(str) + 1;
	ret = malloc(sizeof(char) * len + 1);
	ft_memcpy(ret, str, len);
	ret[len - 1] = a;
	ret[len] = 0;
	free(str);
	return (ret);
}

static char	*get_header(int fd)
{
	char	*ret;
	char	*tmp;
	int		nb;

	tmp = malloc(sizeof(char) * 2);
	ret = malloc(sizeof(char) * 2);
	tmp[1] = 0;
	ret[1] = 0;
	nb = 0;
	while (nb < 3 && read(fd, tmp, 1) > 0)
	{
		ret = append(ret, *tmp);
		if (*tmp == '\n')
			nb++;
	}
	free(tmp);
	return ret;
}

int	read_ppm(t_texture **tex, int fd)
{
	int		valid;
	char	*line = malloc(17);

	t_texture *texture = ft_calloc(1, sizeof(t_texture));
	texture->value = 0;
	texture->height = 0;
	texture->width = 0;
	valid = 0;

	line = get_header(fd);
	while (texture->value == 0)
	{
		if (ft_strncmp(line, "P6", 2) == 0)
		{
			if (valid)
				return (print_error(ERROR, "PPM file has two P6 declaration"));
			valid = 1;
			while (*line && *line != '\n')
				line++;
			line++;
		}
		while (*line && valid)
		{
			if (*line && texture->width == 0)
			{
				texture->width = ft_atoi(line);
				while (*(line++) && (*line != ' '))
					continue ;
				if (*line == ' ') line++;

			}
			if (*line && texture->height == 0)
			{
				texture->height = ft_atoi(line);
				while (*(line++) && (*line != '\n'))
					continue ;
				if (*line == '\n') line++;
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

	unsigned char	*test = malloc(sizeof(*test) * texture->width*texture->height*3);
	read(fd,test, texture->width*texture->height*3);
	close(fd);
	texture->pixels = ft_calloc(texture->height, sizeof(*texture->pixels));

	int	i;
	int	j;
	int	y;

	j = 0;
	i = 0;
	while(i < texture->height)
	{
		y = 0;
		printf("%i\n", i);
		texture->pixels[i] = ft_calloc(texture->width, sizeof(t_color));
		while (y < texture->width)
		{
			texture->pixels[i][y] = (t_color) {(double) test[j] / texture->value,(double) test[j+1] / texture->value, (double)test[j+2] / texture->value};
			j += 3;
			y++;
		}
		i++;
	}
	texture->height -= 1;
	texture->width -= 1;
/*	int		i;
	int		j;
	int		y;

	i = 0;
	j = 0;
	while (i < texture->height)
	{
		printf("%i/%i\n", i, texture->height - 1);
		y = 0;
		texture->pixels[i] = ft_calloc(texture->width - 1, sizeof(t_color));
		while (y < texture->width)
		{
			line = get_next_line(fd);
			if (j == 0)
			{
				texture->pixels[i][y].r = (char) (ft_atoi(line) / texture->value);
				j++;
			}
			else if (j == 1)
			{
				texture->pixels[i][y].g = (char) (ft_atoi(line) / texture->value);
				j++;
			}
			else
			{
				texture->pixels[i][y].b = (char) (ft_atoi(line) / texture->value);
				j = 0;
				y++;
			}
			free(line);
		// *	split = ft_split(line, ' ');
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
			} //
		}
		i++;
	}*/
	*tex = texture;
	return (SUCCESS);
}

int	parse_texture(t_object *object, char *item)
{
	char		*tmp;
	int			i;
	int			fd;

	if (!item)
		return (print_error(ERROR, "A texture is missing"));
	i = 0;
	while (item[i])
	{
		if (item[i] == ' ')
		{
			item[i] = 0;
			break ;
		}
		i++;
	}
	tmp = ft_strtrim(item, "\n \t");
	fd = open(tmp, O_RDONLY);
	if (fd < 0)
		return (print_error(ERROR, "invalid texture file"));
	if (i > 0)
		item[i] = ' ';
	return (read_ppm(&object->texture, fd));
}

int	parse_normal_map(t_object *object, char *item)
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
	return (read_ppm(&object->normal_map, fd));
}

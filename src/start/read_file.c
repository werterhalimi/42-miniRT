/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:38:15 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/15 13:21:41 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	quit_read(int status, int fd, int size)
{
	close(fd);
	if (!status)
		return (size);
	return (print_error(status, "List allocation failed"));
}

static int	empty_line(char const *line)
{
	while (*line == ' ')
		line++;
	if (!(*line) || *line == '\n' || *line == '#')
		return (YES);
	return (NO);
}

static int	check_arg(int argc, char **argv)
{
	int		fd;
	size_t	length;

	if (argc != 2)
		return (print_error(ERROR_NEG, \
			"Invalid number of arguments. Usage : ./miniRT scene.rt"));
	length = ft_strlen(argv[1]);
	if (ft_strncmp(argv[1] + length - 3, ".rt", 4))
		return (print_error(ERROR_NEG, \
			"Invalid argument extension. Required : *.rt"));
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (print_error(ERROR_NEG, "Impossible to open the given file"));
	return (fd);
}

static int	add_object(char *line, t_list **objects)
{
	t_list	*item;
	char	*hash;
	char	*content;

	content = ft_strtrim(line, " ");
	ft_free(line);
	hash = ft_strchr(content, '#');
	if (hash)
		*hash = '\n';
	item = ft_lstnew(content);
	if (!item)
		return (ERROR);
	ft_lstadd_back(objects, item);
	return (SUCCESS);
}

int	read_file(int argc, char **argv, t_list **objects)
{
	int		fd;
	int		size;
	char	*line;

	fd = check_arg(argc, argv);
	if (fd < 0)
		return (ERROR_NEG);
	size = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (empty_line(line))
			ft_free(line);
		else if (++size && add_object(line, objects))
			return (quit_read(ERROR_NEG, fd, 0));
		line = get_next_line(fd);
	}
	return (quit_read(SUCCESS, fd, size - 2));
}

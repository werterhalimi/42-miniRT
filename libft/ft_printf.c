/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:00:10 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/13 11:11:12 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/// @brief Write the total result on fd and free the result
/// @return the total length written
static int	ft_print_fd(t_str *result, int fd)
{
	int		total;
	t_str	*tmp;

	total = 0;
	while (result)
	{
		write(fd, result->str, result->len);
		total += result->len;
		tmp = result->next;
		str_lstdelone(result);
		result = tmp;
	}
	return (total);
}

/// @brief Allocate memory depending on the format
/// @return the address of memory, NULL if error
static char	*malloc_format(char format, va_list *args, int *len)
{
	if (format == 'c')
		return (malloc_char(va_arg(*args, int), len));
	else if (format == 's')
		return (malloc_string(va_arg(*args, char *), len));
	else if (format == 'p')
		return (malloc_pointer(va_arg(*args, void *), len));
	else if (format == 'd' || format == 'i')
		return (malloc_signed(va_arg(*args, int), len));
	else if (format == 'u')
		return (malloc_unsigned(va_arg(*args, unsigned int), len));
	else if (format == 'x' || format == 'X')
		return (malloc_hex(format, va_arg(*args, unsigned int), len));
	else if (format == '%')
		return (malloc_char(format, len));
	return (NULL);
}

/// @brief Add a new element in result containing str
/// @return 0 on success, -1 if error
static int	add_substr(t_str **result, char *str, int len)
{
	t_str	*new;

	if (!str)
		return (-1);
	new = str_lstnew(str, len);
	if (!new)
	{
		free(str);
		return (-1);
	}
	str_lstadd_back(result, new);
	return (0);
}

/// @brief Parsing of str into *result
/// @return the total length of *result, negative if error
static int	parsing(t_str **result, const char *str, int j, va_list *args)
{
	int		i;
	char	*new;

	i = j;
	while (str[i] && str[i] != '%')
		i++;
	if (i - j > 0)
		if (add_substr(result, ft_substr(str, j, i - j), i - j))
			return (-1);
	j = i;
	if (str[i] == '%' && str[j++])
	{
		new = malloc_format(str[j], args, &i);
		if (add_substr(result, new, i))
			return (-1);
		j++;
	}
	return (j);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_str	*result;
	int		len;

	if (!str)
		return (0);
	len = 0;
	result = NULL;
	va_start(args, str);
	while (str[len])
	{
		len = parsing(&result, str, len, &args);
		if (len < 0)
		{
			va_end(args);
			str_lstclear(&result);
			return (len);
		}
	}
	va_end(args);
	len = ft_print_fd(result, STDOUT_FILENO);
	return (len);
}

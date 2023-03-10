/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:12:49 by ncotte            #+#    #+#             */
/*   Updated: 2023/02/17 21:48:46 by shalimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*next_item(char *line)
{
	if (!line)
		return (NULL);
	while (*line && *line != '\n' && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	if (!(*line) || *line == '\n')
		return (NULL);
	return (line);
}

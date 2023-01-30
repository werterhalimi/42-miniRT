/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:08:55 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/15 16:08:59 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_str.h"

void	str_lstdelone(t_str *elem)
{
	if (elem)
	{
		free(elem->str);
		free(elem);
	}
}

t_str	*str_lstnew(char *str, int len)
{
	t_str	*new;

	new = malloc(sizeof (*new));
	if (new)
	{
		new->len = len;
		new->str = str;
		new->next = 0;
	}
	return (new);
}

t_str	*str_lstlast(t_str *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	str_lstadd_back(t_str **lst, t_str *new)
{
	t_str	*elem;

	if (lst)
	{
		if (*lst)
		{
			elem = str_lstlast(*lst);
			elem->next = new;
		}
		else
			*lst = new;
	}
}

void	str_lstclear(t_str **lst)
{
	t_str	*elem;

	if (lst)
	{
		while (*lst)
		{
			elem = (*lst)->next;
			str_lstdelone(*lst);
			*lst = elem;
		}
	}
}

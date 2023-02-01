/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:25:54 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 15:25:56 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_alloc.h"

static t_list	*alloc_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof (*new));
	if (new)
	{
		new->content = content;
		new->next = NULL;
	}
	return (new);
}

static void	*sub_alloc(t_list **garbage_collector, size_t count, size_t size)
{
	unsigned long	total;
	t_list			*new_alloc;
	void			*ptr;
	size_t			i;

	total = count * size;
	if (total > UINT_MAX)
		return (NULL);
	i = 0;
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	while (i < total)
		*(unsigned char *)(ptr + i++) = 0;
	new_alloc = alloc_lstnew(ptr);
	if (!new_alloc)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(garbage_collector, new_alloc);
	return (ptr);
}

static void	alloc_free(t_list **garbage_collector, void *ptr)
{
	t_list	*current;
	t_list	*tmp;

	current = *garbage_collector;
	if (current->content == ptr)
	{
		*garbage_collector = current->next;
		free(current->content);
		free(current);
		return ;
	}
	while (current->next)
	{
		if (current->next->content == ptr)
		{
			tmp = current->next;
			current->next = tmp->next;
			free(tmp->content);
			free(tmp);
			return ;
		}
		current = current->next;
	}
}

static void	alloc_flush(t_list **garbage_collector)
{
	t_list	*elem;

	if (garbage_collector)
	{
		while (*garbage_collector)
		{
			elem = (*garbage_collector)->next;
			free((*garbage_collector)->content);
			free(*garbage_collector);
			*garbage_collector = elem;
		}
	}
}

void	*ft_alloc(size_t count, size_t size, void *ptr, char mode)
{
	static t_list	*garbage_collector;

	if (mode == ALLOC)
		return (sub_alloc(&garbage_collector, count, size));
	else if (mode == FREE)
		alloc_free(&garbage_collector, ptr);
	else if (mode == FLUSH)
		alloc_flush(&garbage_collector);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:10:00 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 14:18:24 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_STR_H
# define T_STR_H

# include "libft.h"

/// @brief Linked list of strings with theirs length
/// @param len length of str
/// @param str pointer to a string
/// @param next pointer to the next element in the list
typedef struct s_str
{
	int				len;
	char			*str;
	struct s_str	*next;
}	t_str;

/// @brief Delete and free elem only (one element)
void	str_lstdelone(t_str *elem);

/// @brief Create a new element of t_str
/// @return its address, NULL if error
t_str	*str_lstnew(char *str, int len);

/// @brief Find the last element of lst
/// @return its address, NULL if error
t_str	*str_lstlast(t_str *lst);

/// @brief Add new at the end of *lst
void	str_lstadd_back(t_str **lst, t_str *new);

/// @brief Delete and free *lst and all following
void	str_lstclear(t_str **lst);

#endif

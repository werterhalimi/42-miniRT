/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:41:34 by ncotte            #+#    #+#             */
/*   Updated: 2023/01/30 19:41:38 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALLOC_H
# define FT_ALLOC_H

# include <limits.h>
# include <stdlib.h>
# include "libft.h"

/* Constants */

# define ALLOC	0
# define FREE	1
# define FLUSH	2

/// TODO
void	*gc_alloc(size_t count, size_t size, void *ptr, char mode);

/// TODO
void	*ft_alloc(size_t count, size_t size);

/// TODO
void	ft_free(void *ptr);

/// TODO
void	ft_flush(void);

#endif

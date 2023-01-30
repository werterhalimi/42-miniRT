/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:02:37 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 14:17:46 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft.h"
# include "malloc.h"
# include "t_str.h"

# define PRINTF_VALID_FLAGS "-.*0123456789"

/// @brief Print str on the standart output given the specified format 
/// @return the total length writen, negative if error
int		ft_printf(const char *str, ...);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:09:48 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 14:18:09 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "libft.h"
# include "utils.h"

/// @brief Convert a char into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_char(int c, int *len);

/// @brief Convert a string into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_string(char *s, int *len);

/// @brief Convert a pointer into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_pointer(void *p, int *len);

/// @brief Convert an integer into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_signed(int i, int *len);

/// @brief Convert an unsigned integer into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_unsigned(unsigned int u, int *len);

/// @brief Convert an hexdecimal integer into a string and adjust *len
/// @return its address, NULL if error
char	*malloc_hex(char format, unsigned int x, int *len);

#endif

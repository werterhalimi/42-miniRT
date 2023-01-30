/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:07:53 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 14:18:40 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define HEXADECIMAL_FORMAT "0123456789abcdef"

/// @brief Create a sting containing an unsigned int u
/// @return its address, NULL if error
char	*ft_uitoa(unsigned int u);

/// @brief Create a sting containing an unsigned int u in hexadecimal
/// @return its address, NULL if error
char	*ft_hextoa(unsigned int u);

#endif

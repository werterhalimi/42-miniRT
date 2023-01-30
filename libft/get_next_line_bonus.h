/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:59:09 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 10:00:58 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2048
# endif

typedef struct s_stat_var
{
	int		index;
	char	buffer[BUFFER_SIZE + 1];
}	t_stat_var;

# define END_OF_FILE -1
# define NEW_FILE 0
# define READING_FILE 1

/// \brief Calculate the length of s
/// \param s the string
/// \return the value
size_t	gnl_strlen(const char *s);

/// \brief Write (n + 1) 0 bytes into s
/// \param s a string
/// \param n the number of bytes to change
void	gnl_bzero(void *s, size_t n);

/// \brief Locate the first occurrence of c in s
/// \param s the string
/// \param c the char to find
/// \return its position, -1 if not found
int		gnl_strchr(const char *s, int c);

/// \brief Concatenate s2 after s1 in a new string
/// \param s1 the first string
/// \param s2 the second string
/// \return the address of the new string, NULL if error
char	*gnl_strjoin(char const *s1, char const *s2);

/// \brief Read and return a line (that end with \n, except the last) from fd
/// \n (handle multiples files at a time)
/// \param fd the file descriptor
/// \return the line, NULL if nothing to be read or error
char	*get_next_line(int fd);

#endif

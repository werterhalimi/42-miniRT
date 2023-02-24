/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncotte <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 11:03:14 by ncotte            #+#    #+#             */
/*   Updated: 2022/10/17 14:20:04 by ncotte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "ft_alloc.h"
# include "ft_printf.h"
# include "get_next_line_bonus.h"
# include <limits.h>
# include <stdlib.h>

/* Structures */

/// @brief Linked list with any content
/// @param content pointer to any content
/// @param next pointer to the next element in the list
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Functions */

/// @brief Check if the character is an alphabetical ASCII character
/// @return non-zero if it is, 0 otherwise
int		ft_isalpha(int c);

/// @brief Check if the character is a decimal ASCII character
/// @return non-zero if it is, 0 otherwise
int		ft_isdigit(int c);

/// @brief Check if the character is a decimal or alphabetical ASCII character
/// @return non-zero if it is, 0 otherwise
int		ft_isalnum(int c);

/// @brief Check if the character is an ASCII character
/// @return non-zero if it is, 0 otherwise
int		ft_isascii(int c);

/// @brief Check if the character is a printable ASCII character
/// @return non-zero if it is, 0 otherwise
int		ft_isprint(int c);

/// @brief Calculate the length of s
/// @return its length
size_t	ft_strlen(const char *s);

/// @brief Write len byte c (as unsigned char) into b
/// @return b (modified or not)
void	*ft_memset(void *b, int c, size_t len);

/// @brief Write n 0 bytes into s
void	ft_bzero(void *s, size_t n);

/// @brief Copy n bytes from src to dst
/// @return dst (modified or not)
void	*ft_memcpy(void *dst, const void *src, size_t n);

/// @brief Copy len bytes from src to dst (overlap is ok)
/// @return dst (modified or not)
void	*ft_memmove(void *dst, const void *src, size_t len);

/// @brief Copy src into dst up to n-1 char and terminating it with \0
/// @return the length of src
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/// @brief Append src at the end of dst (at most dstsize - ft_strlen(dst) - 1)
/// @return the original length of dst plus the length of src
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/// @brief Convert a lowercase letter into an uppercase
/// @return c (modified or not)
int		ft_toupper(int c);

/// @brief Convert an uppercase letter into a lowercase
/// @return c (modified or not)
int		ft_tolower(int c);

/// @brief Locate the first occurrence of c (as char) in s
/// @return its position, NULL if not found
char	*ft_strchr(const char *s, int c);

/// @brief Locate the last occurrence of c (as char) in s
/// @return its position, NULL if not found
char	*ft_strrchr(const char *s, int c);

/// @brief Calculate the difference s1 - s2 lexicographically (as unsigned char)
//	with n char at most
/// @return the difference
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/// @brief Locate the first occurrence of c (as unsigned char)
//	in the first n characters of s
/// @return its position, NULL if not found
void	*ft_memchr(const void *s, int c, size_t n);

/// @brief Calculate the difference s1 - s2 byte by byte (as unsigned char) 
//	with n char at most
/// @return the difference
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/// @brief Search the start of needle in haystack if it exist
//	(searching at most len characters)
/// @return its position, NULL if not found
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/// @brief Convert str into an int (does not handle int overflow)
/// @return the value
int		ft_atoi(const char *str);

/// @brief Allocate count * size bytes of memory and fill it with 0
/// @return its addr, NULL if error
void	*ft_calloc(size_t count, size_t size);

/// @brief Duplicate s1 into a new string
/// @return its addr, NULL if error
char	*ft_strdup(const char *s1);

/// @brief Create a new srting from s, 
//	starting at start and of length len at most,
/// @return its addr, NULL if error
char	*ft_substr(char const *s, unsigned int start, size_t len);

/// @brief Concatenate s2 after s1 in a new string
/// @return its addr, NULL if error
char	*ft_strjoin(char const *s1, char const *s2);

/// @brief Trim s1 of the characters in set at the start and end in a new string
/// @return its addr, NULL if error
char	*ft_strtrim(char const *s1, char const *set);

/// @brief Create an array of strings from the original s but splited by c
/// @return its addr, NULL if error
char	**ft_split(char const *s, char c);

/// @brief Create a sting containing an int n
/// @return its addr, NULL if error
char	*ft_itoa(int n);

/// @brief Apply f to all elements of s
/// @return the results of f(s), NULL if error
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/// @brief Apply f to all elements of s and modify it
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/// @brief Write c into fd
void	ft_putchar_fd(char c, int fd);

/// @brief Write s into fd
void	ft_putstr_fd(char *s, int fd);

/// @brief Write s into fd with a \\n at the end 
void	ft_putendl_fd(char *s, int fd);

/// @brief Write n (as a string) into fd
void	ft_putnbr_fd(int n, int fd);

/// @brief Create a new element of a linked list
/// @return its addr, NULL if error
t_list	*ft_lstnew(void *content);

/// @brief Add new at the start of *lst
void	ft_lstadd_front(t_list **lst, t_list *new);

/// @brief Calculate the size of lst
/// @return its size
int		ft_lstsize(t_list *lst);

/// @brief Find the last element of lst
/// @return its addr, NULL if error
t_list	*ft_lstlast(t_list *lst);

/// @brief Add new at the end of *lst
void	ft_lstadd_back(t_list **lst, t_list *new);

/// @brief Delete and free lst only (one element)
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/// @brief Delete and free *lst and all following
void	ft_lstclear(t_list **lst, void (*del)(void*));

/// @brief Apply f on all elements of lst and modify it
void	ft_lstiter(t_list *lst, void (*f)(void *));

/// @brief Apply f on all elements of lst
/// @return the results of f(lst), NULL if error
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif

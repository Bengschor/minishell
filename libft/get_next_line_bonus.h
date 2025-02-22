/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschor <bschor@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:09:06 by bschor            #+#    #+#             */
/*   Updated: 2024/07/24 18:53:39 by bschor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 300
# elif BUFFER_SIZE >= 2147483647
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

char	*get_next_line(int fd);
char	*ft_calloc_gnl(int count, int size);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strlen_gnl(const char *str);
char	*ft_strchr_gnl(const char *s, int c);
void	ft_free_gnl(char **ptr);

#endif

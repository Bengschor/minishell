# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bschor <bschor@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 12:42:45 by bschor            #+#    #+#              #
#    Updated: 2024/06/18 14:36:11 by bschor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =		ft_isalpha.c \
			ft_isdigit.c \
			ft_isallspace.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_strlen.c \
			ft_strslen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strcmp.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \

SRCS_PRINTF =	ft_itoa_printf.c \
				ft_printf.c \
				subfunctions.c \
				ft_printf_err.c \
				subfunctions_err.c \

# SRCS_B = 	ft_lstnew.c \
# 			ft_lstadd_front.c \
# 			ft_lstsize.c \
# 			ft_lstlast.c \
# 			ft_lstadd_back.c \
# 			ft_lstdelone.c \
# 			ft_lstclear.c \
# 			ft_lstiter.c \
# 			ft_lstmap.c \
			
SRCS_GNL =	get_next_line_bonus.c \
			get_next_line_utils_bonus.c \

CFLAGS =	

INCLUDES =	libft.h

OBJS =		${SRCS:%.c=%.o}

# OBJS_B =	${SRCS_B:%.c=%.o}

OBJS_PRINTF = ${SRCS_PRINTF:%.c=%.o}

OBJS_GNL =	${SRCS_GNL:%.c=%.o}

NAME =		libft.a

all :		${NAME}

${NAME}	:	${OBJS} 
			@ar -rcs ${NAME} ${OBJS} ${OBJS_PRINTF} ${OBJS_GNL}

${OBJS} :	
			@cc ${CFLAGS} -c ${SRCS} ${SRCS_PRINTF} ${SRCS_GNL}

clean :		
			@rm -f ${OBJS}
			@rm -f ${OBJS_PRINTF}
			@rm -f ${OBJS_GNL}

fclean :	clean
			rm -f ${NAME}

re :		fclean all

.PHONY :	all clean fclean re

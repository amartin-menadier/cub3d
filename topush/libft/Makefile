# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 12:09:26 by amartin-          #+#    #+#              #
#    Updated: 2020/07/15 14:25:55 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c \
ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c \
ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_strchr.c ft_split.c \
ft_calloc.c ft_strdup.c ft_strjoin.c \
ft_strcat.c ft_strlcat.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
ft_strcpy.c ft_strncpy.c ft_strlcpy.c ft_strnstr.c ft_strrchr.c \
ft_strtrim.c ft_tolower.c ft_toupper.c ft_substr.c \
get_next_line.c ft_strjoin_gnl.c ft_rgb_from_str.c \
ft_strcharcpy.c

OBJ = $(SRC:.c=.o)

INCLUDES=./

all : $(NAME)
$(NAME): $(SRC) libft.h
	@gcc -Wall -Wextra -Werror -I$(INCLUDES) -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : re fclean clean all

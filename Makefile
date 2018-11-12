# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/16 19:08:49 by kcosta            #+#    #+#              #
#    Updated: 2018/11/12 13:01:06 by kcosta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ========== Editable ========== #
NAME	:= ft_ssl
# ============================== #

# ========== Standard ========== #
CC		:= gcc
FLAGS	:= -Wall -Wextra -Werror -g #-fsanitize=address
# ============================== #

# =========== Files ============ #
SRCS_FILES		:=	ft_ssl.c				\
					md5.c					\
					md5_utils.c				\
					md5_digest.c			\
					md5_digest_utils.c		\
					md5_transform.c			\
					md5_transform_utils.c	\
					sha256.c				\
					sha256_utils.c			\
					sha256_digest.c			\
					sha256_digest_utils.c	\
					sha256_transform.c		\
					sha256_transform_utils.c
HEADERS_FILES	:=	ft_ssl.h				\
					md5.h					\
					sha256.h
# ============================== #

# ========== Sources =========== #
SRCS_PATH	:= sources/
SRCS		:= $(addprefix $(SRCS_PATH), $(SRCS_FILES))
# ============================== #

# ========== Objects =========== #
OBJS_PATH	:= objs/
OBJS 		:= $(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))
# ============================== #

# ========== Includes ========== #
INCLUDES_PATH	:= includes/
INCLUDES		:= -I $(INCLUDES_PATH)
HEADERS	:= $(addprefix $(INCLUDES_PATH), $(HEADERS_FILES))
# ============================== #

# ========== Libraries ========= #
LIBFT_PATH		:= libft/
LIBFT_INCLUDES	:= -I libft/includes
LIBFT			:= -L $(LIBFT_PATH) -lft
# ============================== #

.PHONY: all libft clean fclean re

all: libft $(NAME)

libft:
	@make -C $(LIBFT_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS) $(LIBFT_PATH)libft.a
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	$(CC) $(FLAGS) $(INCLUDES) $(LIBFT_INCLUDES) -o $@ -c $<

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $@

clean:
	@make -C $(LIBFT_PATH) clean &> /dev/null
	@rm -fv $(OBJS)
	@rmdir $(OBJS_PATH) 2> /dev/null || true

fclean: clean
	@make -C $(LIBFT_PATH) fclean &> /dev/null
	@rm -fv $(NAME)

re: fclean all

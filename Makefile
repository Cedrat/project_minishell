# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnoaille <lnoaille@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 18:19:38 by lnoaille          #+#    #+#              #
#    Updated: 2020/12/18 03:11:58 by lnoaille         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS_MS = srcs_minishell/
SRCS = srcs/ft_memset.c srcs/ft_bzero.c srcs/ft_memcpy.c srcs/ft_memccpy.c srcs/ft_memchr.c \
srcs/ft_memcmp.c srcs/ft_strlen.c srcs/ft_isalpha.c srcs/ft_isdigit.c srcs/ft_isalnum.c srcs/ft_isascii.c \
srcs/ft_isprint.c srcs/ft_toupper.c srcs/ft_tolower.c srcs/ft_strchr.c srcs/ft_strrchr.c srcs/ft_strncmp.c \
srcs/ft_strlcpy.c srcs/ft_strlcat.c srcs/ft_strnstr.c srcs/ft_atoi.c srcs/ft_calloc.c srcs/ft_strdup.c \
srcs/ft_substr.c srcs/ft_strjoin.c srcs/ft_strtrim.c srcs/ft_split.c srcs/ft_itoa.c srcs/ft_strmapi.c \
srcs/ft_putchar_fd.c srcs/ft_putstr_fd.c srcs/ft_putendl_fd.c srcs/ft_putnbr_fd.c srcs/ft_memmove.c \
srcs/ft_lstnew.c srcs/ft_lstadd_front.c srcs/ft_lstsize.c srcs/ft_lstlast.c \
srcs/ft_lstadd_back.c srcs/ft_lstdelone.c srcs/ft_lstclear.c srcs/ft_lstiter.c srcs/ft_lstmap.c \
\
${SRCS_MS}add_split_arg.c 			${SRCS_MS}ft_echo.c				${SRCS_MS}ft_file_to_str.c	\
${SRCS_MS}many_strjoin.c			${SRCS_MS}export_utils.c		${SRCS_MS}ft_echo_utils2.c \
${SRCS_MS}ft_str_is_number.c		${SRCS_MS}parser_utils.c		${SRCS_MS}free_all.c \
${SRCS_MS}ft_give_to_pipe.c     	${SRCS_MS}ft_str_is_present.c	${SRCS_MS}syntax.c \
${SRCS_MS}ft_beautifull_export.c	${SRCS_MS}ft_env.c 				${SRCS_MS}ft_nopipes.c \
${SRCS_MS}tab_utils.c				${SRCS_MS}ft_cd.c   			${SRCS_MS}ft_errors.c \
${SRCS_MS}ft_unset.c             	${SRCS_MS}utils_2.c \
${SRCS_MS}ft_charispresent.c      	${SRCS_MS}ft_exec.c             ${SRCS_MS}ft_parse_semicolon.c \
${SRCS_MS}ft_choose_fd.c          	${SRCS_MS}ft_exec_second_part.c ${SRCS_MS}ft_purify_args.c \
${SRCS_MS}ft_count_this_char.c    	${SRCS_MS}ft_exit.c             \
${SRCS_MS}ft_divide_to_pipe.c     	${SRCS_MS}ft_export.c           ${SRCS_MS}ft_pwd.c \
${SRCS_MS}ft_strcmp.c				${SRCS_MS}ft_get_var.c			${SRCS_MS}ft_echo_utils.c \
${SRCS_MS}ft_tri_tab_str.c			${SRCS_MS}ft_parser.c			${SRCS_MS}ft_utils.c \
${SRCS_MS}get_command.c				${SRCS_MS}get_next_line.c		 ${SRCS_MS}get_next_line_utils.c \
${SRCS_MS}main.c 					${SRCS_MS}pipes_utils.c \

DEP = minishell.h

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o : ${DEP}
		gcc ${CFLAGS} -c $< -o ${<:.c=.o}

all : 		${NAME}

${NAME}:	${OBJS}
			gcc -o ${NAME} ${SRCS}

clean :
			${RM} ${OBJS} ${BONUS}

fclean :	clean
			${RM} ${NAME}

re :		fclean all

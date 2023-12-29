# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jschott <jschott@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:31:55 by jschott           #+#    #+#              #
#    Updated: 2023/12/07 10:29:07 by jschott          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

# SOURCES
SRCS = 	main.c \
		table_init.c \
		fork_init.c \
		philo_init.c \
		philo_routine.c \
		table_routine.c \
		gettime.c \
		status_messages.c \
		ft_atol.c \
		ft_strchr.c \
		utils.c

# INCLUDES
HDRS = philo.h

# COMPILATION CMNDS
CC = cc
# FT_FLAGS = -Wall -Wextra -Werror -g -pthread
FT_FLAGS = -Wall -Wextra -Werror -g -fsanitize=thread -pthread
# FT_FLAGS = -Wall -Wextra -Werror -g -fsanitize=address -pthread

# COMPILATION FILES
OBJS = $(SRCS:.c=.o)

all: $(NAME)
	@echo "\n\nCompilation finished successfully\nHave fun breaking things\n"

$(NAME): $(OBJS)
	@echo "\n\nCompiling Executable\n"
	$(CC) $(FT_FLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)
	@echo "\nExecutable compiled\n\n"

$(OBJS): %.o : %.c $(HDRS)
#	@echo "\n\nCompiling Object Files\n"
	$(CC) $(FT_FLAGS) $(INCLUDES) -c $< -o $@
#	@echo "\nObject files compiled successfully\n\n"

clean:
	@rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

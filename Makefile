# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/16 15:11:53 by rmei              #+#    #+#              #
#    Updated: 2024/08/16 15:48:41 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
# Client info
CLIENT_SRC = main.c
CLIENT_SRC := $(addprefix src/client/, ${CLIENT_SRC})
CLIENT_OBJS =  $(CLIENT_SRC:%.c=%.o)
CLIENT = client

# Server info
SERVER_SRC = main.c
SERVER_SRC := $(addprefix src/server/, ${SERVER_SRC})
SERVER_OBJS =  $(SERVER_SRC:%.c=%.o)
SERVER = server

# External libraries
LIBFT = lib/libft

# Compiler and linker flags
CPPFLAGS = -I./include
CFLAGS = -Wall -Werror -Wextra -g
LDFLAGS = -L./$(LIBFT) -lft

#### -- RULES -- ####
all: makelib $(CLIENT) $(SERVER)

# Create external libraries #
makelib:
	make -sC $(LIBFT)

# Create executables #
$(CLIENT): $(CLIENT_OBJS)
	cc $^ $(LDFLAGS) -o $@

$(SERVER): $(SERVER_OBJS)
	cc $^ $(LDFLAGS) -o $@
	
%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@
	
# Manage executables #
clean:
	make clean -sC $(LIBFT)
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: 
	make fclean -sC $(LIBFT)
	rm -f $(CLIENT_OBJS) $(CLIENT) $(SERVER_OBJS) $(SERVER)

re: fclean all

.PHONY: all clean fclean re

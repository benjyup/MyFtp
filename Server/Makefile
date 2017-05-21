##
## Makefile for Makefile in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
## 
## Made by Benjamin
## Login   <benjamin.peixoto@epitech.eu>
## 
## Started on  Sun May 21 23:43:00 2017 Benjamin
## Last update Sun May 21 23:43:01 2017 Benjamin
##

NAME	= server

RMNAME	= ../server

CC	= gcc

CP	= cp

DIR	= ../

RM	= rm -f

SRCS	= ./server.c \
	  ./get_next_line.c \
	  ./my_ls.c \
	  ./my_help.c \
	  ./my_pwd.c \
	  ./my_user.c \
	  ./my_pass.c \
	  ./my_quit.c \
	  ./my_send.c \
	  ./init.c \
	  ./error.c \
	  ./my_noop.c \
	  ./my_cwd.c \
	  ./my_cdup.c \
	  ./my_dele.c \
	  ./my_passv.c \
	  ./my_port.c \
	  ./my_stor.c \
	  ./my_retr.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I 
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)
	 $(CP) $(NAME) $(DIR)
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(RMNAME)

re: fclean all

.PHONY: all clean fclean re

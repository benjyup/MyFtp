NAME	= server

RMNAME	= ../server

CC	= gcc

CP	= cp

DIR	= ../

RM	= rm -f

SRCS	= ./Server.c \
	  ./get_next_line.c \
	  ./My_Ls.c \
	  ./My_Help.c \
	  ./My_Pwd.c \
	  ./My_User.c \
	  ./My_Pass.c \
	  ./My_Quit.c \
	  ./My_Send.c \
	  ./Init.c \
	  ./Error.c \
	  ./My_Noop.c \
	  ./My_Cwd.c \
	  ./My_Cdup.c \
	  ./My_Dele.c \
	  ./My_Passv.c \
	  ./My_Port.c \
	  ./My_Stor.c \
	  ./My_Retr.c

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

NAME	= server

RMNAME	= ../server

CC	= gcc

CP	= cp

DIR	= ../

RM	= rm -f

SRCS	= ./Server.c \
	  ./Tools.c

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

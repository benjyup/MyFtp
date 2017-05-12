NAME		=	FTP


CLIENT		=	./Client/

SERVER		=	./Server/

all: $(NAME)

$(NAME):
	make -C $(CLIENT)
	make -C $(SERVER)
clean:
	make clean -C $(CLIENT)
	make clean -C $(SERVER)

fclean: clean
	make fclean -C $(CLIENT)
	make fclean -C $(SERVER)

re: fclean all

.PHONY: all clean fclean re

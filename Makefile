##
## Makefile for Makefile in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp
## 
## Made by Benjamin
## Login   <benjamin.peixoto@epitech.eu>
## 
## Started on  Sun May 21 23:10:07 2017 Benjamin
## Last update Sun May 21 23:10:22 2017 Benjamin
##

NAME		=	FTP

SERVER		=	./Server/

all: $(NAME)

$(NAME):
	make -C $(SERVER)
clean:
	make clean -C $(SERVER)

fclean: clean
	make fclean -C $(SERVER)

re: fclean all

.PHONY: all clean fclean re

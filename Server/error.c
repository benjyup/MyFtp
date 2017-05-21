/*
** Error.c for Error in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:12:42 2017 Benjamin
** Last update Sun May 21 23:21:26 2017 Benjamin
*/

#include "commande.h"
#include "server.h"

void	SocketError(t_Server *Serv)
{
  if (Serv->socket_service == -1)
    {
      perror("accept");
      exit(5);
    }
}

/*
** my_dele.c for my_dele in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:31:25 2017 Benjamin
** Last update Sun May 21 23:31:26 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Dele(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  if (remove(cmd->param1) == -1)
    my_Send(Serv->socket_service, FILEMISS, sizeof(FILEMISS));
  else
    my_Send(Serv->socket_service, REQUFILEACT, sizeof(REQUFILEACT));
}

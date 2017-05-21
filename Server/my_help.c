/*
** my_help.c for my_help in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:33:13 2017 Benjamin
** Last update Sun May 21 23:42:02 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

void	my_Help(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  int	i;

  (void)(cmd);
  i = 0;
  my_Send(Serv->socket_service, HELPMSG, strlen(HELPMSG));
  while (cmd_locale[i].cmdServ)
    {
      my_Send(Serv->socket_service, " ", 1);
      my_Send(Serv->socket_service, cmd_locale[i].cmdServ,
	      strlen(cmd_locale[i].cmdServ));
      i++;
    }
  my_Send(Serv->socket_service, "\n", 1);
}

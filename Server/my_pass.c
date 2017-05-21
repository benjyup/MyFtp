/*
** my_pass.c for my_pass in /home/peixot_b/Epitech/Tek2/PSU/FTP/PSU_2016_myftp/Server
** 
** Made by Benjamin
** Login   <benjamin.peixoto@epitech.eu>
** 
** Started on  Sun May 21 23:30:43 2017 Benjamin
** Last update Sun May 21 23:30:44 2017 Benjamin
*/

#include "server.h"
#include "commande.h"

int	my_Pass(t_Server *Serv, Commande *cmd)
{
  if (cmd->param1 == NULL && Serv->tmp == 1)
    {
      my_Send(Serv->socket_service, LOGGED, strlen(LOGGED));
      return (1);
    }
  else if (cmd->param1 == NULL && Serv->tmp == 0)
    {
	Serv->tmp = 0;
	my_Send(Serv->socket_service, USERFIRST, strlen(USERFIRST));
	return (0);
    }
  else
      {
	Serv->tmp = 0;
	my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
	return (0);
      }
}

void	my_PassMsg(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd_locale);
  (void)(cmd);
  my_Send(Serv->socket_service, ALREADYLOG, strlen(ALREADYLOG));
}

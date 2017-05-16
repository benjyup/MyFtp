//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Tools.h"

void	my_Help(t_Server *Serv, Commande_Locale *cmd_locale)
{
  int	i;

  i = 0;
  my_Send(Serv->socket_service, HELPMSG, strlen(HELPMSG));
  while (cmd_locale[i].cmdServ)
    {
      my_Send(Serv->socket_service, " ", 1);
      my_Send(Serv->socket_service, cmd_locale[i].cmdServ, strlen(cmd_locale[i].cmdServ));
      i++;
    }
  my_Send(Serv->socket_service, "\n", 1);
}
//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Commande.h"

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
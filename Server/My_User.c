//
// Created by peixot_b on 16/05/17.
//

#include "Server.h"
#include "Commande.h"

int	my_User(t_Server *Serv, Commande *cmd)
{
  if (cmd->param1 == NULL)
    {
      Serv->tmp = 0;
      my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
      return (0);
    }
  if (strcasecmp(cmd->param1, "anonymous") == 0)
    {
      Serv->tmp = 1;
      my_Send(Serv->socket_service, USERNAMEOK, sizeof(USERNAMEOK));
    }
  else
    {
      Serv->tmp = 0;
      my_Send(Serv->socket_service, PLSLOGIN, strlen(PLSLOGIN));
    }
  return (0);
}

void	my_UserMsg(t_Server *Serv, Commande_Locale *cmd_locale, Commande *cmd)
{
  (void)(cmd);
  (void)(cmd_locale);
  my_Send(Serv->socket_service, CHANGEUSER, strlen(CHANGEUSER));
}
